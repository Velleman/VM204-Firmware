/**
 * @file avr32_eth.c
 * @brief AVR32 Ethernet MAC controller
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
#include <limits.h>
#include <avr32/io.h>
#include "interrupt.h"
#include "intc.h"
#include "core/net.h"
#include "drivers/avr32_eth.h"
#include "debug.h"

//TX buffer
static uint8_t txBuffer[AVR32_ETH_TX_BUFFER_COUNT][AVR32_ETH_TX_BUFFER_SIZE]
   __attribute__((aligned(4)));
//RX buffer
static uint8_t rxBuffer[AVR32_ETH_RX_BUFFER_COUNT][AVR32_ETH_RX_BUFFER_SIZE]
   __attribute__((aligned(4)));
//TX buffer descriptors
static Avr32TxBufferDesc txBufferDesc[AVR32_ETH_TX_BUFFER_COUNT]
   __attribute__((aligned(8)));
//RX buffer descriptors
static Avr32RxBufferDesc rxBufferDesc[AVR32_ETH_RX_BUFFER_COUNT]
   __attribute__((aligned(8)));

//TX buffer index
static uint_t txBufferIndex;
//RX buffer index
static uint_t rxBufferIndex;


/**
 * @brief AVR32 Ethernet MAC driver
 **/

const NicDriver avr32EthDriver =
{
   NIC_TYPE_ETHERNET,
   ETH_MTU,
   avr32EthInit,
   avr32EthTick,
   avr32EthEnableIrq,
   avr32EthDisableIrq,
   avr32EthEventHandler,
   avr32EthSetMacFilter,
   avr32EthSendPacket,
   avr32EthWritePhyReg,
   avr32EthReadPhyReg,
   TRUE,
   TRUE,
   TRUE
};


/**
 * @brief AVR32 Ethernet MAC initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t avr32EthInit(NetInterface *interface)
{
   error_t error;
   volatile uint32_t status;

   //Debug message
   TRACE_INFO("Initializing AVR32 Ethernet MAC...\r\n");

   //GPIO configuration
   avr32EthInitGpio(interface);

   //Configure MDC clock speed
   AVR32_MACB.ncfgr = AVR32_MACB_NCFGR_CLK_DIV64;
   //Enable management port (MDC and MDIO)
   AVR32_MACB.ncr |= AVR32_MACB_NCR_MPE_MASK;

   //PHY transceiver initialization
   error = interface->phyDriver->init(interface);
   //Failed to initialize PHY transceiver?
   if(error) return error;

   //Set the MAC address
   AVR32_MACB.sa1b = interface->macAddr.b[0] |
      (interface->macAddr.b[1] << 8) |
      (interface->macAddr.b[2] << 16) |
	  (interface->macAddr.b[3] << 24);

   AVR32_MACB.sa1t = interface->macAddr.b[4] |
      (interface->macAddr.b[5] << 8);

   //Configure the receive filter
   AVR32_MACB.ncfgr |= AVR32_MACB_NCFGR_UNI_MASK | AVR32_MACB_NCFGR_MTI_MASK;

   //Initialize hash table
   AVR32_MACB.hrb = 0;
   AVR32_MACB.hrt = 0;

   //Initialize buffer descriptors
   avr32EthInitBufferDesc(interface);

   //Clear transmit status register
   AVR32_MACB.tsr = AVR32_MACB_TSR_UND_MASK | AVR32_MACB_TSR_COMP_MASK | AVR32_MACB_TSR_BEX_MASK |
      AVR32_MACB_TSR_TGO_MASK | AVR32_MACB_TSR_RLE_MASK | AVR32_MACB_TSR_COL_MASK | AVR32_MACB_TSR_UBR_MASK;
   //Clear receive status register
   AVR32_MACB.rsr = AVR32_MACB_RSR_OVR_MASK | AVR32_MACB_RSR_REC_MASK | AVR32_MACB_RSR_BNA_MASK;

   //First disable all EMAC interrupts
   AVR32_MACB.idr = 0xFFFFFFFF;
   //Only the desired ones are enabled
   AVR32_MACB.ier = AVR32_MACB_IER_ROVR_MASK | AVR32_MACB_IER_TCOMP_MASK | AVR32_MACB_IER_TXERR_MASK |
      AVR32_MACB_IER_RLE_MASK | AVR32_MACB_IER_TUND_MASK | AVR32_MACB_IER_RXUBR_MASK | AVR32_MACB_IER_RCOMP_MASK;

   //Read EMAC ISR register to clear any pending interrupt
   status = AVR32_MACB.isr;

   //Register interrupt handler
   INTC_register_interrupt(avr32EthIrqWrapper, AVR32_MACB_IRQ, AVR32_ETH_IRQ_PRIORITY);

   //Enable the EMAC to transmit and receive data
   AVR32_MACB.ncr |= AVR32_MACB_NCR_TE_MASK | AVR32_MACB_NCR_RE_MASK;

   //Force the TCP/IP stack to check the link state
   osSetEvent(&interface->nicRxEvent);
   //AVR32 Ethernet MAC is now ready to send
   osSetEvent(&interface->nicTxEvent);

   //Successful initialization
   return NO_ERROR;
}


//EVK1105 evaluation board?
#if defined(USE_EVK1105)

/**
 * @brief GPIO configuration
 * @param[in] interface Underlying network interface
 **/

void avr32EthInitGpio(NetInterface *interface)
{
	//Assign RMII pins to peripheral A function
   AVR32_GPIO.port[1].pmr0c = MACB_RMII_MASK;
   AVR32_GPIO.port[1].pmr1c =MACB_RMII_MASK;

   //Disable the PIO from controlling the corresponding pins
   AVR32_GPIO.port[1].gperc = MACB_RMII_MASK;

   //Select RMII operation mode
   AVR32_MACB.usrio &= ~AVR32_MACB_USRIO_RMII_MASK;
}

#endif


/**
 * @brief Initialize buffer descriptors
 * @param[in] interface Underlying network interface
 **/

void avr32EthInitBufferDesc(NetInterface *interface)
{
   uint_t i;
   uint32_t address;

   //Initialize TX buffer descriptors
   for(i = 0; i < AVR32_ETH_TX_BUFFER_COUNT; i++)
   {
      //Calculate the address of the current TX buffer
      address = (uint32_t) txBuffer[i];
      //Write the address to the descriptor entry
      txBufferDesc[i].address = address;
      //Initialize status field
      txBufferDesc[i].status = MACB_TX_USED;
   }

   //Mark the last descriptor entry with the wrap flag
   txBufferDesc[i - 1].status |= MACB_TX_WRAP;
   //Initialize TX buffer index
   txBufferIndex = 0;

   //Initialize RX buffer descriptors
   for(i = 0; i < AVR32_ETH_RX_BUFFER_COUNT; i++)
   {
      //Calculate the address of the current RX buffer
      address = (uint32_t) rxBuffer[i];
      //Write the address to the descriptor entry
      rxBufferDesc[i].address = address & MACB_RX_ADDRESS;
      //Clear status field
      rxBufferDesc[i].status = 0;
   }

   //Mark the last descriptor entry with the wrap flag
   rxBufferDesc[i - 1].address |= MACB_RX_WRAP;
   //Initialize RX buffer index
   rxBufferIndex = 0;

   //Start location of the TX descriptor list
   AVR32_MACB.tbqp = (uint32_t) txBufferDesc;
   //Start location of the RX descriptor list
   AVR32_MACB.rbqp = (uint32_t) rxBufferDesc;
}


/**
 * @brief AVR32 Ethernet MAC timer handler
 *
 * This routine is periodically called by the TCP/IP stack to
 * handle periodic operations such as polling the link state
 *
 * @param[in] interface Underlying network interface
 **/

void avr32EthTick(NetInterface *interface)
{
   //Handle periodic operations
   interface->phyDriver->tick(interface);
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void avr32EthEnableIrq(NetInterface *interface)
{
   //Enable Ethernet MAC interrupts
   Enable_global_interrupt();
   //Enable Ethernet PHY interrupts
   interface->phyDriver->enableIrq(interface);
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void avr32EthDisableIrq(NetInterface *interface)
{
   //Disable Ethernet MAC interrupts
   Disable_global_interrupt();
   //Disable Ethernet PHY interrupts
   interface->phyDriver->disableIrq(interface);
}


/**
 * @brief AVR32 Ethernet MAC interrupt wrapper
 **/

__attribute__((naked)) void avr32EthIrqWrapper(void)
{
   //Enter interrupt service routine
   osEnterIsr();

   //Call Ethernet MAC interrupt handler
   avr32EthIrqHandler();

   //Leave interrupt service routine
   osExitIsr(flag);
}


/**
 * @brief AVR32 Ethernet MAC interrupt service routine
 * @return TRUE if a higher priority task must be woken. Else FALSE is returned
 **/

bool_t avr32EthIrqHandler(void)
{
   bool_t flag;
   volatile uint32_t isr;
   volatile uint32_t tsr;
   volatile uint32_t rsr;
   NetInterface *interface;

   //Point to the structure describing the network interface
   interface = &netInterface[0];
   //This flag will be set if a higher priority task must be woken
   flag = FALSE;

   //Each time the software reads EMAC_ISR, it has to check the
   //contents of EMAC_TSR, EMAC_RSR and EMAC_NSR
   isr = AVR32_MACB.isr;
   tsr = AVR32_MACB.tsr;
   rsr = AVR32_MACB.rsr;

   //A packet has been transmitted?
   if(tsr & (AVR32_MACB_TSR_UND_MASK | AVR32_MACB_TSR_COMP_MASK | AVR32_MACB_TSR_BEX_MASK |
      AVR32_MACB_TSR_TGO_MASK | AVR32_MACB_TSR_RLE_MASK | AVR32_MACB_TSR_COL_MASK | AVR32_MACB_TSR_UBR_MASK))
   {
      //Only clear TSR flags that are currently set
      AVR32_MACB.tsr = tsr;

      //Check whether the TX buffer is available for writing
      if(txBufferDesc[txBufferIndex].status & MACB_TX_USED)
      {
         //Notify the user that the transmitter is ready to send
         flag |= osSetEventFromIsr(&interface->nicTxEvent);
      }
   }
   //A packet has been received?
   if(rsr & (AVR32_MACB_RSR_OVR_MASK | AVR32_MACB_RSR_REC_MASK | AVR32_MACB_RSR_BNA_MASK))
   {
      //Notify the user that a packet has been received
      flag |= osSetEventFromIsr(&interface->nicRxEvent);
   }

   //A higher priority task must be woken?
   return flag;
}


/**
 * @brief AVR32 Ethernet MAC event handler
 * @param[in] interface Underlying network interface
 **/

void avr32EthEventHandler(NetInterface *interface)
{
   uint32_t rsr;
   uint_t length;
   bool_t linkStateChange;

   //Read receive status
   rsr = AVR32_MACB.rsr;

   //PHY event is pending?
   if(interface->phyEvent)
   {
      //Acknowledge the event by clearing the flag
      interface->phyEvent = FALSE;
      //Handle PHY specific events
      linkStateChange = interface->phyDriver->eventHandler(interface);

      //Check whether the link state has changed?
      if(linkStateChange)
      {
         //Set speed and duplex mode for proper operation
         if(interface->linkState)
         {
            //Read network configuration register
            uint32_t config = AVR32_MACB.ncfgr;

            //10BASE-T or 100BASE-TX operation mode?
            if(interface->speed100)
               config |= AVR32_MACB_NCFGR_SPD_MASK;
            else
               config &= ~AVR32_MACB_NCFGR_SPD_MASK;

            //Half-duplex or full-duplex mode?
            if(interface->fullDuplex)
               config |= AVR32_MACB_NCFGR_FD_MASK;
            else
               config &= ~AVR32_MACB_NCFGR_FD_MASK;

            //Write configuration value back to NCFGR register
            AVR32_MACB.ncfgr = config;
         }

         //Process link state change event
         nicNotifyLinkChange(interface);
      }
   }

   //Packet received?
   if(rsr & (AVR32_MACB_RSR_OVR_MASK | AVR32_MACB_RSR_REC_MASK | AVR32_MACB_RSR_BNA_MASK))
   {
      //Only clear RSR flags that are currently set
      AVR32_MACB.rsr = rsr;

      //Process all the pending packets
      while(1)
      {
         //Check whether a packet has been received
         length = avr32EthReceivePacket(interface, interface->ethFrame, ETH_MAX_FRAME_SIZE);
         //No packet is pending in the receive buffer?
         if(!length) break;
         //Pass the packet to the upper layer
         nicProcessPacket(interface, interface->ethFrame, length);
      }
   }
}


/**
 * @brief Configure multicast MAC address filtering
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t avr32EthSetMacFilter(NetInterface *interface)
{
   uint_t i;
   uint_t j;
   uint32_t hashTable[2];

   //Debug message
   TRACE_INFO("Updating AVR32 hash table...\r\n");

   //Clear hash table
   hashTable[0] = 0;
   hashTable[1] = 0;

   //The MAC filter table contains the multicast MAC addresses
   //to accept when receiving an Ethernet frame
   for(i = 0; i < interface->macFilterSize; i++)
   {
      //Point to the current address
      MacAddr *addr = &interface->macFilter[i].addr;
      //Reset hash value
      uint_t hashIndex = 0;

      //Apply the hash function
      for(j = 0; j < 48; j += 6)
      {
         //Calculate the shift count
         uint_t n = j / 8;
         uint_t m = j % 8;

         //Update hash value
         if(!m)
            hashIndex ^= addr->b[n];
         else
            hashIndex ^= (addr->b[n] >> m) | (addr->b[n + 1] << (8 - m));
      }

      //The hash value is reduced to a 6-bit index
      hashIndex &= 0x3F;
      //Update hash table contents
      hashTable[hashIndex / 32] |= (1 << (hashIndex % 32));
   }

   //Write the hash table
   AVR32_MACB.hrb = hashTable[0];
   AVR32_MACB.hrt = hashTable[1];

   //Debug message
   TRACE_INFO("  HRB = %08" PRIX32 "\r\n", AVR32_MACB.hrb);
   TRACE_INFO("  HRT = %08" PRIX32 "\r\n", AVR32_MACB.hrt);

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

error_t avr32EthSendPacket(NetInterface *interface,
   const NetBuffer *buffer, size_t offset)
{
   //Retrieve the length of the packet
   size_t length = netBufferGetLength(buffer) - offset;

   //Check the frame length
   if(length > AVR32_ETH_TX_BUFFER_SIZE)
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
      //Report an error
      return ERROR_INVALID_LENGTH;
   }

   //Make sure the current buffer is available for writing
   if(!(txBufferDesc[txBufferIndex].status & MACB_TX_USED))
      return ERROR_FAILURE;

   //Copy user data to the transmit buffer
   netBufferRead(txBuffer[txBufferIndex], buffer, offset, length);

   //Set the necessary flags in the descriptor entry
   if(txBufferIndex < (AVR32_ETH_TX_BUFFER_COUNT - 1))
   {
      //Write the status word
      txBufferDesc[txBufferIndex].status =
         MACB_TX_LAST | (length & MACB_TX_LENGTH);

      //Point to the next buffer
      txBufferIndex++;
   }
   else
   {
      //Write the status word
      txBufferDesc[txBufferIndex].status = MACB_TX_WRAP |
         MACB_TX_LAST | (length & MACB_TX_LENGTH);

      //Wrap around
      txBufferIndex = 0;
   }

   //Set the TSTART bit to initiate transmission
   AVR32_MACB.ncr |= AVR32_MACB_NCR_TSTART_MASK;

   //Check whether the next buffer is available for writing
   if(txBufferDesc[txBufferIndex].status & MACB_TX_USED)
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Receive a packet
 * @param[in] interface Underlying network interface
 * @param[out] buffer Buffer where to store the incoming data
 * @param[in] size Maximum number of bytes that can be received
 * @return Number of bytes that have been received
 **/

uint_t avr32EthReceivePacket(NetInterface *interface,
   uint8_t *buffer, size_t size)
{
   uint_t i;
   uint_t j;
   uint_t n;
   uint_t index;

   //Indexes of SOF and EOF
   uint_t sofIndex = UINT_MAX;
   uint_t eofIndex = UINT_MAX;

   //Total number of bytes received
   uint_t length = 0;

   //Search for SOF and EOF flags
   for(i = 0; i < AVR32_ETH_RX_BUFFER_COUNT; i++)
   {
      //Point to the current descriptor
      index = rxBufferIndex + i;
      //Wrap around to the beginning of the buffer if necessary
      if(index >= AVR32_ETH_RX_BUFFER_COUNT)
         index -= AVR32_ETH_RX_BUFFER_COUNT;

      //No more entries to process?
      if(!(rxBufferDesc[index].address & MACB_RX_OWNERSHIP))
      {
         break;
      }
      //A valid SOF has been found?
      if(rxBufferDesc[index].status & MACB_RX_SOF)
      {
         //Save the position of the SOF
         sofIndex = i;
      }
      //A valid EOF has been found?
      if((rxBufferDesc[index].status & MACB_RX_EOF) && sofIndex != UINT_MAX)
      {
         //Save the position of the EOF
         eofIndex = i;
         //Retrieve the length of the frame
         n = rxBufferDesc[index].status & MACB_RX_LENGTH;
         //Limit the number of data to read
         size = MIN(n, size);
         //Stop processing since we have reached the end of the frame
         break;
      }
   }

   //Determine the number of entries to process
   if(eofIndex != UINT_MAX)
      j = eofIndex + 1;
   else if(sofIndex != UINT_MAX)
      j = sofIndex;
   else
      j = i;

   //Process incoming frame
   for(i = 0; i < j; i++)
   {
      //Any data to copy from current buffer?
      if(eofIndex != UINT_MAX && i >= sofIndex && i <= eofIndex)
      {
         //Calculate the number of bytes to read at a time
         n = MIN(size, AVR32_ETH_RX_BUFFER_SIZE);
         //Copy data from receive buffer
         memcpy(buffer, rxBuffer[rxBufferIndex], n);
         //Advance data pointer
         buffer += n;
         //Update byte counters
         length += n;
         size -= n;
      }

      //Mark the current buffer as free
      rxBufferDesc[rxBufferIndex].address &= ~MACB_RX_OWNERSHIP;

      //Point to the following entry
      rxBufferIndex++;
      //Wrap around to the beginning of the buffer if necessary
      if(rxBufferIndex >= AVR32_ETH_RX_BUFFER_COUNT)
         rxBufferIndex = 0;
   }

   //Return the number of bytes that have been received
   return length;
}


/**
 * @brief Write PHY register
 * @param[in] phyAddr PHY address
 * @param[in] regAddr Register address
 * @param[in] data Register value
 **/

void avr32EthWritePhyReg(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
   //Set up a write operation
   uint32_t value = MACB_MAN_SOF_01 | MACB_MAN_RW_01 | MACB_MAN_CODE_10;
   //PHY address
   value |= (phyAddr << AVR32_MACB_MAN_PHYA_OFFSET) & AVR32_MACB_MAN_PHYA_MASK;
   //Register address
   value |= (regAddr << AVR32_MACB_MAN_REGA_OFFSET) & AVR32_MACB_MAN_REGA_MASK;
   //Register value
   value |= data & AVR32_MACB_MAN_DATA_MASK;

   //Start a write operation
   AVR32_MACB.man = value;
   //Wait for the write to complete
   while(!(AVR32_MACB.nsr & AVR32_MACB_NSR_IDLE_MASK));
}


/**
 * @brief Read PHY register
 * @param[in] phyAddr PHY address
 * @param[in] regAddr Register address
 * @return Register value
 **/

uint16_t avr32EthReadPhyReg(uint8_t phyAddr, uint8_t regAddr)
{
   //Set up a read operation
   uint32_t value = MACB_MAN_SOF_01 | MACB_MAN_RW_10 | MACB_MAN_CODE_10;
   //PHY address
   value |= (phyAddr << AVR32_MACB_MAN_PHYA_OFFSET) & AVR32_MACB_MAN_PHYA_MASK;
   //Register address
   value |= (regAddr << AVR32_MACB_MAN_REGA_OFFSET) & AVR32_MACB_MAN_REGA_MASK;

   //Start a read operation
   AVR32_MACB.man = value;
   //Wait for the read to complete
   while(!(AVR32_MACB.nsr & AVR32_MACB_NSR_IDLE_MASK));

   //Return PHY register contents
   return AVR32_MACB.man & AVR32_MACB_MAN_DATA_MASK;
}
