/**
 * @file ksz8851.c
 * @brief KSZ8851 Ethernet controller
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
#include "drivers/ksz8851.h"
#include "debug.h"

//Transmit buffer
static uint8_t txBuffer[1536];


/**
 * @brief KSZ8851 driver
 **/

const NicDriver ksz8851Driver =
{
   NIC_TYPE_ETHERNET,
   ETH_MTU,
   ksz8851Init,
   ksz8851Tick,
   ksz8851EnableIrq,
   ksz8851DisableIrq,
   ksz8851EventHandler,
   ksz8851SetMacFilter,
   ksz8851SendPacket,
   NULL,
   NULL,
   TRUE,
   TRUE,
   TRUE
};


/**
 * @brief KSZ8851 controller initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t ksz8851Init(NetInterface *interface)
{
   //Point to the driver context
   Ksz8851Context *context = (Ksz8851Context *) interface->nicContext;

   //Debug message
   TRACE_INFO("Initializing KSZ8851 Ethernet controller...\r\n");

   //Initialize SPI
   interface->spiDriver->init();
   //Initialize external interrupt line
   interface->extIntDriver->init();

   //Debug message
   TRACE_DEBUG("CIDER=0x%04" PRIX16 "\r\n", ksz8851ReadReg(interface, KSZ8851_REG_CIDER));
   TRACE_DEBUG("PHY1ILR=0x%04" PRIX16 "\r\n", ksz8851ReadReg(interface, KSZ8851_REG_PHY1ILR));
   TRACE_DEBUG("PHY1IHR=0x%04" PRIX16 "\r\n", ksz8851ReadReg(interface, KSZ8851_REG_PHY1IHR));

   //Check device ID and revision ID
   if(ksz8851ReadReg(interface, KSZ8851_REG_CIDER) != KSZ8851_REV_A3_ID)
      return ERROR_WRONG_IDENTIFIER;

   //Dump registers for debugging purpose
   ksz8851DumpReg(interface);

   //Initialize driver specific variables
   context->frameId = 0;

   //Initialize MAC address
   ksz8851WriteReg(interface, KSZ8851_REG_MARH, htons(interface->macAddr.w[0]));
   ksz8851WriteReg(interface, KSZ8851_REG_MARM, htons(interface->macAddr.w[1]));
   ksz8851WriteReg(interface, KSZ8851_REG_MARL, htons(interface->macAddr.w[2]));

   //Packets shorter than 64 bytes are padded and the CRC is automatically generated
   ksz8851WriteReg(interface, KSZ8851_REG_TXCR, TXCR_TXFCE | TXCR_TXPE | TXCR_TXCE);
   //Automatically increment TX data pointer
   ksz8851WriteReg(interface, KSZ8851_REG_TXFDPR, TXFDPR_TXFPAI);

   //Configure address filtering
   ksz8851WriteReg(interface, KSZ8851_REG_RXCR1,
      RXCR1_RXPAFMA | RXCR1_RXFCE | RXCR1_RXBE | RXCR1_RXME | RXCR1_RXUE);

   //No checksum verification
   ksz8851WriteReg(interface, KSZ8851_REG_RXCR2,
      RXCR2_SRDBL2 | RXCR2_IUFFP | RXCR2_RXIUFCEZ);

   //Enable automatic RXQ frame buffer dequeue
   ksz8851WriteReg(interface, KSZ8851_REG_RXQCR, RXQCR_RXFCTE | RXQCR_ADRFE);
   //Automatically increment RX data pointer
   ksz8851WriteReg(interface, KSZ8851_REG_RXFDPR, RXFDPR_RXFPAI);
   //Configure receive frame count threshold
   ksz8851WriteReg(interface, KSZ8851_REG_RXFCTR, 1);

   //Force link in half-duplex if auto-negotiation failed
   ksz8851ClearBit(interface, KSZ8851_REG_P1CR, P1CR_FORCE_DUPLEX);
   //Restart auto-negotiation
   ksz8851SetBit(interface, KSZ8851_REG_P1CR, P1CR_RESTART_AN);

   //Clear interrupt flags
   ksz8851SetBit(interface, KSZ8851_REG_ISR, ISR_LCIS | ISR_TXIS |
      ISR_RXIS | ISR_RXOIS | ISR_TXPSIS | ISR_RXPSIS | ISR_TXSAIS |
      ISR_RXWFDIS | ISR_RXMPDIS | ISR_LDIS | ISR_EDIS | ISR_SPIBEIS);

   //Configure interrupts as desired
   ksz8851SetBit(interface, KSZ8851_REG_IER, IER_LCIE | IER_TXIE | IER_RXIE);

   //Enable TX operation
   ksz8851SetBit(interface, KSZ8851_REG_TXCR, TXCR_TXE);
   //Enable RX operation
   ksz8851SetBit(interface, KSZ8851_REG_RXCR1, RXCR1_RXE);

   //Force the TCP/IP stack to check the link state
   osSetEvent(&interface->nicRxEvent);
   //KSZ8851 transmitter is now ready to send
   osSetEvent(&interface->nicTxEvent);

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief KSZ8851 timer handler
 * @param[in] interface Underlying network interface
 **/

void ksz8851Tick(NetInterface *interface)
{
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void ksz8851EnableIrq(NetInterface *interface)
{
   //Enable interrupts
   interface->extIntDriver->enableIrq();
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void ksz8851DisableIrq(NetInterface *interface)
{
   //Disable interrupts
   interface->extIntDriver->disableIrq();
}


/**
 * @brief KSZ8851 interrupt service routine
 * @param[in] interface Underlying network interface
 * @return TRUE if a higher priority task must be woken. Else FALSE is returned
 **/

bool_t ksz8851IrqHandler(NetInterface *interface)
{
   bool_t flag;
   uint16_t status;

   //This flag will be set if a higher priority task must be woken
   flag = FALSE;

   //Read interrupt status register
   status = ksz8851ReadReg(interface, KSZ8851_REG_ISR);

   //Link status change?
   if(status & ISR_LCIS)
   {
      //Disable LCIE interrupt
      ksz8851ClearBit(interface, KSZ8851_REG_IER, IER_LCIE);
      //Notify the user that the link state has changed
      flag |= osSetEventFromIsr(&interface->nicRxEvent);
   }
   //Packet transmission complete?
   if(status & ISR_TXIS)
   {
      //Notify the user that the transmitter is ready to send
      flag |= osSetEventFromIsr(&interface->nicTxEvent);
      //Clear interrupt flag
      ksz8851WriteReg(interface, KSZ8851_REG_ISR, ISR_TXIS);
   }
   //Packet received?
   if(status & ISR_RXIS)
   {
      //Disable RXIE interrupt
      ksz8851ClearBit(interface, KSZ8851_REG_IER, IER_RXIE);
      //Notify the user that a packet has been received
      flag |= osSetEventFromIsr(&interface->nicRxEvent);
   }

   //A higher priority task must be woken?
   return flag;
}


/**
 * @brief KSZ8851 event handler
 * @param[in] interface Underlying network interface
 **/

void ksz8851EventHandler(NetInterface *interface)
{
   error_t error;
   uint16_t status;
   uint_t frameCount;
   uint_t length;

   //Read interrupt status register
   status = ksz8851ReadReg(interface, KSZ8851_REG_ISR);

   //Check whether the link status has changed?
   if(status & ISR_LCIS)
   {
      //Clear interrupt flag
      ksz8851WriteReg(interface, KSZ8851_REG_ISR, ISR_LCIS);
      //Read PHY status register
      status = ksz8851ReadReg(interface, KSZ8851_REG_P1SR);

      //Check link state
      if(status & P1SR_LINK_GOOD)
      {
         //Link is up
         interface->linkState = TRUE;
         //Get current speed
         interface->speed100 = (status & P1SR_OPERATION_SPEED) ? TRUE : FALSE;
         //Determine the new duplex mode
         interface->fullDuplex = (status & P1SR_OPERATION_DUPLEX) ? TRUE : FALSE;

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
   if(status & ISR_RXIS)
   {
      //Clear interrupt flag
      ksz8851WriteReg(interface, KSZ8851_REG_ISR, ISR_RXIS);
      //Get the total number of frames that are pending in the buffer
      frameCount = MSB(ksz8851ReadReg(interface, KSZ8851_REG_RXFCTR));

      //Process all pending packets
      while(frameCount > 0)
      {
         //Read incoming packet
         error = ksz8851ReceivePacket(interface,
            interface->ethFrame, ETH_MAX_FRAME_SIZE, &length);

         //Check whether a valid packet has been received
         if(!error)
         {
            //Pass the packet to the upper layer
            nicProcessPacket(interface, interface->ethFrame, length);
         }

         //Decrement frame counter
         frameCount--;
      }
   }

   //Re-enable LCIE and RXIE interrupts
   ksz8851SetBit(interface, KSZ8851_REG_IER, IER_LCIE | IER_RXIE);
}


/**
 * @brief Configure multicast MAC address filtering
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t ksz8851SetMacFilter(NetInterface *interface)
{
   uint_t i;
   uint_t k;
   uint32_t crc;
   uint16_t hashTable[4];

   //Debug message
   TRACE_INFO("Updating KSZ8851 hash table...\r\n");

   //Clear hash table
   memset(hashTable, 0, sizeof(hashTable));

   //The MAC filter table contains the multicast MAC addresses
   //to accept when receiving an Ethernet frame
   for(i = 0; i < interface->macFilterSize; i++)
   {
      //Compute CRC over the current MAC address
      crc = ksz8851CalcCrc(&interface->macFilter[i].addr, sizeof(MacAddr));
      //Calculate the corresponding index in the table
      k = (crc >> 26) & 0x3F;
      //Update hash table contents
      hashTable[k / 16] |= (1 << (k % 16));
   }

   //Write the hash table to the KSZ8851 controller
   ksz8851WriteReg(interface, KSZ8851_REG_MAHTR0, hashTable[0]);
   ksz8851WriteReg(interface, KSZ8851_REG_MAHTR1, hashTable[1]);
   ksz8851WriteReg(interface, KSZ8851_REG_MAHTR2, hashTable[2]);
   ksz8851WriteReg(interface, KSZ8851_REG_MAHTR3, hashTable[3]);

   //Debug message
   TRACE_INFO("  MAHTR0 = %04" PRIX16 "\r\n", ksz8851ReadReg(interface, KSZ8851_REG_MAHTR0));
   TRACE_INFO("  MAHTR1 = %04" PRIX16 "\r\n", ksz8851ReadReg(interface, KSZ8851_REG_MAHTR1));
   TRACE_INFO("  MAHTR2 = %04" PRIX16 "\r\n", ksz8851ReadReg(interface, KSZ8851_REG_MAHTR2));
   TRACE_INFO("  MAHTR3 = %04" PRIX16 "\r\n", ksz8851ReadReg(interface, KSZ8851_REG_MAHTR3));

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Send a packet
 * @param[in] interface Underlying network interface
 * @param[in] buffer Multi-part buffer containing the data to send
 * @param[in] offset Offset to the first data byte
 * @return Error code
 **/

error_t ksz8851SendPacket(NetInterface *interface,
   const NetBuffer *buffer, size_t offset)
{
   size_t n;
   size_t length;
   Ksz8851TxHeader header;
   Ksz8851Context *context;

   //Point to the driver context
   context = (Ksz8851Context *) interface->nicContext;

   //Retrieve the length of the packet
   length = netBufferGetLength(buffer) - offset;

   //Check the frame length
   if(length > 1536)
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
      //Report an error
      return ERROR_INVALID_LENGTH;
   }

   //Get the amount of free memory available in the TX FIFO
   n = ksz8851ReadReg(interface, KSZ8851_REG_TXMIR) & TXMIR_TXMA_MASK;

   //Make sure enough memory is available
   if((length + 8) > n)
      return ERROR_FAILURE;

   //Copy user data
   netBufferRead(txBuffer, buffer, offset, length);

   //Format control word
   header.controlWord = TX_CTRL_TXIC | (context->frameId++ & TX_CTRL_TXFID);
   //Total number of bytes to be transmitted
   header.byteCount = length;

   //Enable TXQ write access
   ksz8851SetBit(interface, KSZ8851_REG_RXQCR, RXQCR_SDA);
   //Write TX packet header
   ksz8851WriteFifo(interface, (uint8_t *) &header, sizeof(Ksz8851TxHeader));
   //Write data
   ksz8851WriteFifo(interface, txBuffer, length);
   //End TXQ write access
   ksz8851ClearBit(interface, KSZ8851_REG_RXQCR, RXQCR_SDA);

   //Start transmission
   ksz8851SetBit(interface, KSZ8851_REG_TXQCR, TXQCR_METFE);

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Receive a packet
 * @param[in] interface Underlying network interface
 * @param[out] buffer Buffer where to store the incoming data
 * @param[in] size Maximum number of bytes that can be received
 * @param[out] length Number of bytes that have been received
 * @return Error code
 **/

error_t ksz8851ReceivePacket(NetInterface *interface,
   uint8_t *buffer, size_t size, size_t *length)
{
   size_t n;
   uint16_t status;

   //Read received frame status from RXFHSR
   status = ksz8851ReadReg(interface, KSZ8851_REG_RXFHSR);

   //Make sure the frame is valid
   if(status & RXFHSR_RXFV)
   {
      //Check error flags
      if(!(status & (RXFHSR_RXMR | RXFHSR_RXFTL | RXFHSR_RXRF | RXFHSR_RXCE)))
      {
         //Read received frame byte size from RXFHBCR
         n = ksz8851ReadReg(interface, KSZ8851_REG_RXFHBCR) & RXFHBCR_RXBC_MASK;

         //Ensure the frame size is acceptable
         if(n > 0)
         {
            //Reset QMU RXQ frame pointer to zero
            ksz8851WriteReg(interface, KSZ8851_REG_RXFDPR, RXFDPR_RXFPAI);
            //Enable RXQ read access
            ksz8851SetBit(interface, KSZ8851_REG_RXQCR, RXQCR_SDA);
            //Read data
            ksz8851ReadFifo(interface, buffer, n);
            //End RXQ read access
            ksz8851ClearBit(interface, KSZ8851_REG_RXQCR, RXQCR_SDA);

            //Total number of bytes that have been received
            *length = n;
            //Packet successfully received
            return NO_ERROR;
         }
      }
   }

   //Release the current error frame from RXQ
   ksz8851SetBit(interface, KSZ8851_REG_RXQCR, RXQCR_RRXEF);
   //Report an error
   return ERROR_INVALID_PACKET;
}


/**
 * @brief Write KSZ8851 register
 * @param[in] interface Underlying network interface
 * @param[in] address Register address
 * @param[in] data Register value
 **/

void ksz8851WriteReg(NetInterface *interface, uint8_t address, uint16_t data)
{
   uint8_t command;

   //Form the write command
   if(address & 0x02)
      command = KSZ8851_CMD_WR_REG | KSZ8851_CMD_B3 | KSZ8851_CMD_B2;
   else
      command = KSZ8851_CMD_WR_REG | KSZ8851_CMD_B1 | KSZ8851_CMD_B0;

   //Pull the CS pin low
   interface->spiDriver->assertCs();

   //Command phase
   interface->spiDriver->transfer(command | (address >> 6));
   interface->spiDriver->transfer(address << 2);

   //Data phase
   interface->spiDriver->transfer(LSB(data));
   interface->spiDriver->transfer(MSB(data));

   //Terminate the operation by raising the CS pin
   interface->spiDriver->deassertCs();
}


/**
 * @brief Read KSZ8851 register
 * @param[in] interface Underlying network interface
 * @param[in] address Register address
 * @return Register value
 **/

uint16_t ksz8851ReadReg(NetInterface *interface, uint8_t address)
{
   uint8_t command;
   uint16_t data;

   //Form the read command
   if(address & 0x02)
      command = KSZ8851_CMD_RD_REG | KSZ8851_CMD_B3 | KSZ8851_CMD_B2;
   else
      command = KSZ8851_CMD_RD_REG | KSZ8851_CMD_B1 | KSZ8851_CMD_B0;

   //Pull the CS pin low
   interface->spiDriver->assertCs();

   //Command phase
   interface->spiDriver->transfer(command | (address >> 6));
   interface->spiDriver->transfer(address << 2);

   //Data phase (lower 8 bits)
   data = interface->spiDriver->transfer(0x00);
   //Data phase (upper 8 bits)
   data |= interface->spiDriver->transfer(0x00) << 8;

   //Terminate the operation by raising the CS pin
   interface->spiDriver->deassertCs();

   //Return register value
   return data;
}


/**
 * @brief Write TX FIFO
 * @param[in] interface Underlying network interface
 * @param[in] data Pointer to the data being written
 * @param[in] length Number of data to write
 **/

void ksz8851WriteFifo(NetInterface *interface, const uint8_t *data, size_t length)
{
   uint_t i;

   //Pull the CS pin low
   interface->spiDriver->assertCs();

   //Command phase
   interface->spiDriver->transfer(KSZ8851_CMD_WR_FIFO);

   //Data phase
   for(i = 0; i < length; i++)
      interface->spiDriver->transfer(data[i]);

   //Maintain alignment to 4-byte boundaries
   for(; i % 4; i++)
      interface->spiDriver->transfer(0x00);

   //Terminate the operation by raising the CS pin
   interface->spiDriver->deassertCs();
}


/**
 * @brief Read RX FIFO
 * @param[in] interface Underlying network interface
 * @param[in] data Buffer where to store the incoming data
 * @param[in] length Number of data to read
 **/

void ksz8851ReadFifo(NetInterface *interface, uint8_t *data, size_t length)
{
   uint_t i;

   //Pull the CS pin low
   interface->spiDriver->assertCs();

   //Command phase
   interface->spiDriver->transfer(KSZ8851_CMD_RD_FIFO);

   //The first 4 bytes are dummy data and must be discarded
   for(i = 0; i < 4; i++)
      interface->spiDriver->transfer(0x00);

   //Ignore RX packet header
   for(i = 0; i < 4; i++)
      interface->spiDriver->transfer(0x00);

   //Data phase
   for(i = 0; i < length; i++)
      data[i] = interface->spiDriver->transfer(0x00);

   //Maintain alignment to 4-byte boundaries
   for(; i % 4; i++)
      interface->spiDriver->transfer(0x00);

   //Terminate the operation by raising the CS pin
   interface->spiDriver->deassertCs();
}


/**
 * @brief Set bit field
 * @param[in] interface Underlying network interface
 * @param[in] address Register address
 * @param[in] mask Bits to set in the target register
 **/

void ksz8851SetBit(NetInterface *interface, uint8_t address, uint16_t mask)
{
   //Read current register value
   uint16_t value = ksz8851ReadReg(interface, address);
   //Set specified bits
   ksz8851WriteReg(interface, address, value | mask);
}


/**
 * @brief Clear bit field
 * @param[in] interface Underlying network interface
 * @param[in] address Register address
 * @param[in] mask Bits to clear in the target register
 **/

void ksz8851ClearBit(NetInterface *interface, uint8_t address, uint16_t mask)
{
   //Read current register value
   uint16_t value = ksz8851ReadReg(interface, address);
   //Clear specified bits
   ksz8851WriteReg(interface, address, value & ~mask);
}


/**
 * @brief CRC calculation
 * @param[in] data Pointer to the data over which to calculate the CRC
 * @param[in] length Number of bytes to process
 * @return Resulting CRC value
 **/

uint32_t ksz8851CalcCrc(const void *data, size_t length)
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
      //The message is processed bit by bit
      for(j = 0; j < 8; j++)
      {
         //Update CRC value
         if(((crc >> 31) ^ (p[i] >> j)) & 0x01)
            crc = (crc << 1) ^ 0x04C11DB7;
         else
            crc = crc << 1;
      }
   }

   //Return CRC value
   return crc;
}


/**
 * @brief Dump registers for debugging purpose
 * @param[in] interface Underlying network interface
 **/

void ksz8851DumpReg(NetInterface *interface)
{
#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
   uint_t i;
   uint_t j;
   uint_t address;

   //Loop through register addresses
   for(i = 0; i < 256; i += 16)
   {
      //Display register address
      TRACE_DEBUG("%02" PRIu8 ": ", i);

      //Display 8 registers at a time
      for(j = 0; j < 16; j += 2)
      {
         //Format register address
         address = i + j;
         //Display register contents
         TRACE_DEBUG("0x%04" PRIX16 "  ", ksz8851ReadReg(interface, address));
      }

      //Jump to the following line
      TRACE_DEBUG("\r\n");
   }

   //Terminate with a line feed
   TRACE_DEBUG("\r\n");
#endif
}
