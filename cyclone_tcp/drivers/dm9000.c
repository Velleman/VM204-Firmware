/**
 * @file dm9000.c
 * @brief DM9000A/B Ethernet controller
 *
 * @section License
 *
 * Copyright (C) 2010-2015 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneTCP Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.6.0
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL NIC_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "core/ethernet.h"
#include "drivers/dm9000.h"
#include "debug.h"

//Transmit buffer
static uint8_t txBuffer[1536] __attribute__((aligned(2)));


/**
 * @brief DM9000 driver
 **/

const NicDriver dm9000Driver =
{
   NIC_TYPE_ETHERNET,
   ETH_MTU,
   dm9000Init,
   dm9000Tick,
   dm9000EnableIrq,
   dm9000DisableIrq,
   dm9000EventHandler,
   dm9000SetMacFilter,
   dm9000SendPacket,
   NULL,
   NULL,
   TRUE,
   TRUE,
   TRUE
};


/**
 * @brief DM9000 controller initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t dm9000Init(NetInterface *interface)
{
   uint_t i;
   uint16_t vendorId;
   uint16_t productId;
   uint8_t chipRevision;
   Dm9000Context *context;

   //Debug message
   TRACE_INFO("Initializing DM9000 Ethernet controller...\r\n");

   //Initialize external interrupt line
   interface->extIntDriver->init();

   //Point to the driver context
   context = (Dm9000Context *) interface->nicContext;
   //Initialize driver specific variables
   context->queuedPackets = 0;

   //Retrieve vendorID, product ID and chip revision
   vendorId = (dm9000ReadReg(DM9000_REG_VIDH) << 8) | dm9000ReadReg(DM9000_REG_VIDL);
   productId = (dm9000ReadReg(DM9000_REG_PIDH) << 8) | dm9000ReadReg(DM9000_REG_PIDL);
   chipRevision = dm9000ReadReg(DM9000_REG_CHIPR);

   //Check vendor ID and product ID
   if(vendorId != DM9000_VID || productId != DM9000_PID)
      return ERROR_WRONG_IDENTIFIER;
   //Check chip revision
   if(chipRevision != DM9000A_CHIP_REV && chipRevision != DM9000B_CHIP_REV)
      return ERROR_WRONG_IDENTIFIER;

   //Power up the internal PHY by clearing PHYPD
   dm9000WriteReg(DM9000_REG_GPR, 0x00);
   //Wait for the PHY to be ready
   sleep(10);

   //Software reset
   dm9000WriteReg(DM9000_REG_NCR, NCR_RST);
   //Wait for the reset to complete
   while(dm9000ReadReg(DM9000_REG_NCR) & NCR_RST);

   //PHY software reset
   dm9000WritePhyReg(DM9000_PHY_REG_BMCR, BMCR_RST);
   //Wait for the PHY reset to complete
   while(dm9000ReadPhyReg(DM9000_PHY_REG_BMCR) & BMCR_RST);

   //Debug message
   TRACE_INFO("  VID = 0x%04" PRIX16 "\r\n", vendorId);
   TRACE_INFO("  PID = 0x%04" PRIX16 "\r\n", productId);
   TRACE_INFO("  CHIPR = 0x%02" PRIX8 "\r\n", chipRevision);
   TRACE_INFO("  PHYIDR1 = 0x%04" PRIX16 "\r\n", dm9000ReadPhyReg(DM9000_PHY_REG_PHYIDR1));
   TRACE_INFO("  PHYIDR2 = 0x%04" PRIX16 "\r\n", dm9000ReadPhyReg(DM9000_PHY_REG_PHYIDR2));

   //Enable loopback mode?
#if (DM9000_LOOPBACK_MODE == ENABLED)
   dm9000WriteReg(DM9000_REG_NCR, DM9000_LBK_PHY);
   dm9000WritePhyReg(DM9000_PHY_REG_BMCR, BMCR_LOOPBACK | BMCR_SPEED_SEL | BMCR_AN_EN | BMCR_DUPLEX_MODE);
#endif

   //Set host MAC address
   for(i = 0; i < 6; i++)
      dm9000WriteReg(DM9000_REG_PAR0 + i, interface->macAddr.b[i]);

   //Initialize hash table
   for(i = 0; i < 8; i++)
      dm9000WriteReg(DM9000_REG_MAR0 + i, 0x00);

   //Always accept broadcast packets
   dm9000WriteReg(DM9000_REG_MAR7, 0x80);

   //Enable the Pointer Auto Return function
   dm9000WriteReg(DM9000_REG_IMR, IMR_PAR);
   //Clear NSR status bits
   dm9000WriteReg(DM9000_REG_NSR, NSR_WAKEST | NSR_TX2END | NSR_TX1END);
   //Clear interrupt flags
   dm9000WriteReg(DM9000_REG_ISR, ISR_LNKCHG | ISR_UDRUN | ISR_ROO | ISR_ROS | ISR_PT | ISR_PR);
   //Enable interrupts
   dm9000WriteReg(DM9000_REG_IMR, IMR_PAR | IMR_LNKCHGI | IMR_PTI | IMR_PRI);
   //Enable the receiver by setting RXEN
   dm9000WriteReg(DM9000_REG_RCR, RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN);

   //DM9000 transmitter is now ready to send
   osSetEvent(&interface->nicTxEvent);

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief DM9000 timer handler
 * @param[in] interface Underlying network interface
 **/

void dm9000Tick(NetInterface *interface)
{
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void dm9000EnableIrq(NetInterface *interface)
{
   //Enable interrupts
   interface->extIntDriver->enableIrq();
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void dm9000DisableIrq(NetInterface *interface)
{
   //Disable interrupts
   interface->extIntDriver->disableIrq();
}


/**
 * @brief DM9000 interrupt service routine
 * @param[in] interface Underlying network interface
 * @return TRUE if a higher priority task must be woken. Else FALSE is returned
 **/

bool_t dm9000IrqHandler(NetInterface *interface)
{
   bool_t flag;
   uint8_t status;
   uint8_t mask;
   Dm9000Context *context;

   //This flag will be set if a higher priority task must be woken
   flag = FALSE;

   //Point to the driver context
   context = (Dm9000Context *) interface->nicContext;

   //Read interrupt status register
   status = dm9000ReadReg(DM9000_REG_ISR);

   //Link status change?
   if(status & ISR_LNKCHG)
   {
      //Read interrupt mask register
      mask = dm9000ReadReg(DM9000_REG_IMR);
      //Disable LNKCHGI interrupt
      dm9000WriteReg(DM9000_REG_IMR, mask & ~IMR_LNKCHGI);
      //Notify the user that the link state has changed
      flag |= osSetEventFromIsr(&interface->nicRxEvent);
   }
   //Packet transmission complete?
   if(status & ISR_PT)
   {
      //Check TX complete status bits
      if(dm9000ReadReg(DM9000_REG_NSR) & (NSR_TX2END | NSR_TX1END))
      {
         //The transmission of the current packet is complete
         if(context->queuedPackets > 0)
            context->queuedPackets--;
         //Notify the user that the transmitter is ready to send
         flag |= osSetEventFromIsr(&interface->nicTxEvent);
      }
      //Clear interrupt flag
      dm9000WriteReg(DM9000_REG_ISR, ISR_PT);
   }
   //Packet received?
   if(status & ISR_PR)
   {
      //Read interrupt mask register
      mask = dm9000ReadReg(DM9000_REG_IMR);
      //Disable PRI interrupt
      dm9000WriteReg(DM9000_REG_IMR, mask & ~IMR_PRI);
      //Notify the user that a packet has been received
      flag |= osSetEventFromIsr(&interface->nicRxEvent);
   }

   //A higher priority task must be woken?
   return flag;
}


/**
 * @brief DM9000 event handler
 * @param[in] interface Underlying network interface
 **/

void dm9000EventHandler(NetInterface *interface)
{
   error_t error;
   uint8_t status;
   size_t length;

   //Read interrupt status register
   status = dm9000ReadReg(DM9000_REG_ISR);

   //Check whether the link status has changed?
   if(status & ISR_LNKCHG)
   {
      //Clear interrupt flag
      dm9000WriteReg(DM9000_REG_ISR, ISR_LNKCHG);
      //Read network status register
      status = dm9000ReadReg(DM9000_REG_NSR);

      //Check link state
      if(status & NSR_LINKST)
      {
         //Link is up
         interface->linkState = TRUE;
         //Get current speed
         interface->speed100 = (status & NSR_SPEED) ? FALSE : TRUE;

         //Read network control register
         status = dm9000ReadReg(DM9000_REG_NCR);
         //Determine the new duplex mode
         interface->fullDuplex = (status & NCR_FDX) ? TRUE : FALSE;

         //Display link state
         TRACE_INFO("Link is up (%s)...\r\n", interface->name);

         //Display actual speed and duplex mode
         TRACE_INFO("%s %s\r\n",
            interface->speed100 ? "100BASE-TX" : "10BASE-T",
            interface->fullDuplex ? "Full-Duplex" : "Half-Duplex");
      }
      else
      {
         //Link is down
         interface->linkState = FALSE;
         //Display link state
         TRACE_INFO("Link is down (%s)...\r\n", interface->name);
      }

      //Process link state change event
      nicNotifyLinkChange(interface);
   }
   //Check whether a packet has been received?
   if(status & ISR_PR)
   {
      //Clear interrupt flag
      dm9000WriteReg(DM9000_REG_ISR, ISR_PR);

      //Process all pending packets
      do
      {
         //Read incoming packet
         error = dm9000ReceivePacket(interface,
            interface->ethFrame, ETH_MAX_FRAME_SIZE, &length);

         //Check whether a valid packet has been received
         if(!error)
         {
            //Pass the packet to the upper layer
            nicProcessPacket(interface, interface->ethFrame, length);
         }

         //No more data in the receive buffer?
      } while(error != ERROR_BUFFER_EMPTY);
   }

   //Re-enable LNKCHGI and PRI interrupts
   dm9000WriteReg(DM9000_REG_IMR, IMR_PAR | IMR_LNKCHGI | IMR_PTI | IMR_PRI);
}


/**
 * @brief Configure multicast MAC address filtering
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t dm9000SetMacFilter(NetInterface *interface)
{
   uint_t i;
   uint_t k;
   uint32_t crc;
   uint8_t hashTable[8];

   //Debug message
   TRACE_INFO("Updating DM9000 hash table...\r\n");

   //Clear hash table
   memset(hashTable, 0, sizeof(hashTable));
   //Always accept broadcast packets regardless of the MAC filter table
   hashTable[7] = 0x80;

   //The MAC filter table contains the multicast MAC addresses
   //to accept when receiving an Ethernet frame
   for(i = 0; i < interface->macFilterSize; i++)
   {
      //Compute CRC over the current MAC address
      crc = dm9000CalcCrc(&interface->macFilter[i].addr, sizeof(MacAddr));
      //Calculate the corresponding index in the table
      k = crc & 0x3F;
      //Update hash table contents
      hashTable[k / 8] |= (1 << (k % 8));
   }

   //Write the hash table to the DM9000 controller
   for(i = 0; i < 8; i++)
      dm9000WriteReg(DM9000_REG_MAR0 + i, hashTable[i]);

   //Debug message
   TRACE_INFO("  MAR = %02" PRIX8 " %02" PRIX8 " %02" PRIX8 " %02" PRIX8 " "
      "%02" PRIX8 " %02" PRIX8 " %02" PRIX8 " %02" PRIX8 "\r\n",
      dm9000ReadReg(DM9000_REG_MAR0), dm9000ReadReg(DM9000_REG_MAR1),
      dm9000ReadReg(DM9000_REG_MAR2), dm9000ReadReg(DM9000_REG_MAR3),
      dm9000ReadReg(DM9000_REG_MAR4), dm9000ReadReg(DM9000_REG_MAR5),
      dm9000ReadReg(DM9000_REG_MAR6), dm9000ReadReg(DM9000_REG_MAR7));

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Send a packet to DM9000
 * @param[in] interface Underlying network interface
 * @param[in] buffer Multi-part buffer containing the data to send
 * @param[in] offset Offset to the first data byte
 * @return Error code
 **/

error_t dm9000SendPacket(NetInterface *interface,
   const NetBuffer *buffer, size_t offset)
{
   size_t i;
   uint16_t *p;

   //Point to the driver context
   Dm9000Context *context = (Dm9000Context *) interface->nicContext;

   //Retrieve the length of the packet
   size_t length = netBufferGetLength(buffer) - offset;

   //Check the frame length
   if(length > 1536)
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
      //Report an error
      return ERROR_INVALID_LENGTH;
   }

   //Copy user data
   netBufferRead(txBuffer, buffer, offset, length);

   //A dummy write is required before accessing FIFO
   dm9000WriteReg(DM9000_REG_MWCMDX, 0);
   //Select MWCMD register
   *DM9000_INDEX_REG = DM9000_REG_MWCMD;

   //Point to the beginning of the buffer
   p = (uint16_t *) txBuffer;

   //Write data to the FIFO using 16-bit mode
   for(i = length; i > 1; i -= 2)
      *DM9000_DATA_REG = *(p++);

   //Odd number of bytes?
   if(i > 0)
      *DM9000_DATA_REG = *((uint8_t *) p);

   //Write the number of bytes to send
   dm9000WriteReg(DM9000_REG_TXPLL, LSB(length));
   dm9000WriteReg(DM9000_REG_TXPLH, MSB(length));

   //Clear interrupt flag
   dm9000WriteReg(DM9000_REG_ISR, ISR_PT);
   //Start data transfer
   dm9000WriteReg(DM9000_REG_TCR, TCR_TXREQ);

   //The packet was successfully written to FIFO
   context->queuedPackets++;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Receive a packet from DM9000
 * @param[in] interface Underlying network interface
 * @param[out] buffer Buffer where to store the incoming data
 * @param[in] size Maximum number of bytes that can be received
 * @param[out] length Number of bytes that have been received
 * @return Error code
 **/

error_t dm9000ReceivePacket(NetInterface *interface,
   uint8_t *buffer, size_t size, size_t *length)
{
   error_t error;
   size_t i;
   size_t n;
   volatile uint8_t status;
   volatile uint16_t data;

   //A dummy read is required before accessing the 4-byte header
   data = dm9000ReadReg(DM9000_REG_MRCMDX);

   //Select MRCMDX1 register
   *DM9000_INDEX_REG = DM9000_REG_MRCMDX1;
   //Read the first byte of the header
   status = LSB(*DM9000_DATA_REG);

   //The first byte indicates if a packet has been received
   if(status == 0x01)
   {
      //Select MRCMD register
      *DM9000_INDEX_REG = DM9000_REG_MRCMD;
      //The second byte is the RX status byte
      status = MSB(*DM9000_DATA_REG);

      //Retrieve packet length
      n = *DM9000_DATA_REG;
      //Limit the number of data to read
      size = MIN(size, n);

      //Point to the beginning of the buffer
      i = 0;

      //Make sure no error occurred
      if(!(status & (RSR_LCS | RSR_RWTO | RSR_PLE | RSR_AE | RSR_CE | RSR_FOE)))
      {
         //Read data from FIFO using 16-bit mode
         while((i + 1) < size)
         {
            data = *DM9000_DATA_REG;
            buffer[i++] = LSB(data);
            buffer[i++] = MSB(data);
         }

         //Odd number of bytes to read?
         if((i + 1) == size)
         {
            data = *DM9000_DATA_REG;
            buffer[i] = LSB(data);
            i += 2;
         }

         //Total number of bytes that have been received
         *length = size;
         //Packet successfully received
         error = NO_ERROR;
      }
      else
      {
         //The received packet contains an error
         error = ERROR_INVALID_PACKET;
      }

      //Flush remaining bytes
      while(i < n)
      {
         data = *DM9000_DATA_REG;
         i += 2;
      }
   }
   else
   {
      //No more data in the receive buffer
      error = ERROR_BUFFER_EMPTY;
   }

   //Return status code
   return error;
}


/**
 * @brief Write DM9000 register
 * @param[in] address Register address
 * @param[in] data Register value
 **/

void dm9000WriteReg(uint8_t address, uint8_t data)
{
   //Write register address to INDEX register
   *DM9000_INDEX_REG = address;
   //Write register value to DATA register
   *DM9000_DATA_REG = data;
}


/**
 * @brief Read DM9000 register
 * @param[in] address Register address
 * @return Register value
 **/

uint8_t dm9000ReadReg(uint8_t address)
{
   //Write register address to INDEX register
   *DM9000_INDEX_REG = address;
   //Read register value from DATA register
   return *DM9000_DATA_REG;
}


/**
 * @brief Write DM9000 PHY register
 * @param[in] address PHY register address
 * @param[in] data Register value
 **/

void dm9000WritePhyReg(uint8_t address, uint16_t data)
{
   //Write PHY register address
   dm9000WriteReg(DM9000_REG_EPAR, 0x40 | address);
   //Write register value
   dm9000WriteReg(DM9000_REG_EPDRL, LSB(data));
   dm9000WriteReg(DM9000_REG_EPDRH, MSB(data));

   //Start the write operation
   dm9000WriteReg(DM9000_REG_EPCR, EPCR_EPOS | EPCR_ERPRW);
   //PHY access is still in progress?
   while(dm9000ReadReg(DM9000_REG_EPCR) & EPCR_ERRE);

   //Wait 5us minimum
   usleep(5);
   //Clear command register
   dm9000WriteReg(DM9000_REG_EPCR, EPCR_EPOS);
}


/**
 * @brief Read DM9000 PHY register
 * @param[in] address PHY register address
 * @return Register value
 **/

uint16_t dm9000ReadPhyReg(uint8_t address)
{
   //Write PHY register address
   dm9000WriteReg(DM9000_REG_EPAR, 0x40 | address);

   //Start the read operation
   dm9000WriteReg(DM9000_REG_EPCR, EPCR_EPOS | EPCR_ERPRR);
   //PHY access is still in progress?
   while(dm9000ReadReg(DM9000_REG_EPCR) & EPCR_ERRE);

   //Clear command register
   dm9000WriteReg(DM9000_REG_EPCR, EPCR_EPOS);
   //Wait 5us minimum
   usleep(5);

   //Return register value
   return (dm9000ReadReg(DM9000_REG_EPDRH) << 8) | dm9000ReadReg(DM9000_REG_EPDRL);
}


/**
 * @brief CRC calculation
 * @param[in] data Pointer to the data over which to calculate the CRC
 * @param[in] length Number of bytes to process
 * @return Resulting CRC value
 **/

uint32_t dm9000CalcCrc(const void *data, size_t length)
{
   uint_t i;
   uint_t j;

   //Point to the data over which to calculate the CRC
   const uint8_t *p = (uint8_t *) data;
   //CRC preset value
   uint32_t crc = 0xFFFFFFFF;

   //Loop through data
   for(i = 0; i < length; i++)
   {
      //Update CRC value
      crc ^= p[i];
      //The message is processed bit by bit
      for(j = 0; j < 8; j++)
      {
         if(crc & 0x00000001)
            crc = (crc >> 1) ^ 0xEDB88320;
         else
            crc = crc >> 1;
      }
   }

   //Return CRC value
   return crc;
}
