/**
 * @file sama5d3_eth.c
 * @brief SAMA5D3 Ethernet MAC controller
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
#include "sama5d3x.h"
#include "core/net.h"
#include "drivers/sama5d3_eth.h"
#include "debug.h"

//IAR EWARM compiler?
#if defined(__ICCARM__)

//TX buffer
#pragma data_alignment = 8
#pragma location = "region_dma_nocache"
static uint8_t txBuffer[SAMA5D3_ETH_TX_BUFFER_COUNT][SAMA5D3_ETH_TX_BUFFER_SIZE];
//RX buffer
#pragma data_alignment = 8
#pragma location = "region_dma_nocache"
static uint8_t rxBuffer[SAMA5D3_ETH_RX_BUFFER_COUNT][SAMA5D3_ETH_RX_BUFFER_SIZE];
//TX buffer descriptors
#pragma data_alignment = 8
#pragma location = "region_dma_nocache"
static Sama5d3TxBufferDesc txBufferDesc[SAMA5D3_ETH_TX_BUFFER_COUNT];
//RX buffer descriptors
#pragma data_alignment = 8
#pragma location = "region_dma_nocache"
static Sama5d3RxBufferDesc rxBufferDesc[SAMA5D3_ETH_RX_BUFFER_COUNT];

//Keil MDK-ARM or GCC compiler?
#else

//TX buffer
static uint8_t txBuffer[SAMA5D3_ETH_TX_BUFFER_COUNT][SAMA5D3_ETH_TX_BUFFER_SIZE]
   __attribute__((aligned(8), __section__(".region_dma_nocache")));
//RX buffer
static uint8_t rxBuffer[SAMA5D3_ETH_RX_BUFFER_COUNT][SAMA5D3_ETH_RX_BUFFER_SIZE]
   __attribute__((aligned(8), __section__(".region_dma_nocache")));
//TX buffer descriptors
static Sama5d3TxBufferDesc txBufferDesc[SAMA5D3_ETH_TX_BUFFER_COUNT]
   __attribute__((aligned(8), __section__(".region_dma_nocache")));
//RX buffer descriptors
static Sama5d3RxBufferDesc rxBufferDesc[SAMA5D3_ETH_RX_BUFFER_COUNT]
   __attribute__((aligned(8), __section__(".region_dma_nocache")));

#endif

//TX buffer index
static uint_t txBufferIndex;
//RX buffer index
static uint_t rxBufferIndex;


/**
 * @brief SAMA5D3 Ethernet MAC driver
 **/

const NicDriver sama5d3EthDriver =
{
   NIC_TYPE_ETHERNET,
   ETH_MTU,
   sama5d3EthInit,
   sama5d3EthTick,
   sama5d3EthEnableIrq,
   sama5d3EthDisableIrq,
   sama5d3EthEventHandler,
   sama5d3EthSetMacFilter,
   sama5d3EthSendPacket,
   sama5d3EthWritePhyReg,
   sama5d3EthReadPhyReg,
   TRUE,
   TRUE,
   TRUE
};


/**
 * @brief SAMA5D3 Ethernet MAC initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t sama5d3EthInit(NetInterface *interface)
{
   error_t error;
   volatile uint32_t status;

   //Debug message
   TRACE_INFO("Initializing SAMA5D3 Ethernet MAC...\r\n");

   //Enable EMAC peripheral clock
   PMC->PMC_PCER1 = (1 << (ID_EMAC - 32));
   //Enable IRQ controller peripheral clock
   PMC->PMC_PCER1 = (1 << (ID_IRQ - 32));

   //GPIO configuration
   sama5d3EthInitGpio(interface);

   //Configure MDC clock speed
   EMAC->EMAC_NCFGR = EMAC_NCFGR_CLK_MCK_64;
   //Enable management port (MDC and MDIO)
   EMAC->EMAC_NCR |= EMAC_NCR_MPE;

   //PHY transceiver initialization
   error = interface->phyDriver->init(interface);
   //Failed to initialize PHY transceiver?
   if(error) return error;

   //Set the MAC address
   EMAC->EMAC_SA[0].EMAC_SAxB = interface->macAddr.w[0] | (interface->macAddr.w[1] << 16);
   EMAC->EMAC_SA[0].EMAC_SAxT = interface->macAddr.w[2];

   //Configure the receive filter
   EMAC->EMAC_NCFGR |= EMAC_NCFGR_UNI | EMAC_NCFGR_MTI;

   //Initialize hash table
   EMAC->EMAC_HRB = 0;
   EMAC->EMAC_HRT = 0;

   //Initialize buffer descriptors
   sama5d3EthInitBufferDesc(interface);

   //Clear transmit status register
   EMAC->EMAC_TSR = EMAC_TSR_UND | EMAC_TSR_COMP | EMAC_TSR_BEX |
      EMAC_TSR_TGO | EMAC_TSR_RLES | EMAC_TSR_COL | EMAC_TSR_UBR;
   //Clear receive status register
   EMAC->EMAC_RSR = EMAC_RSR_OVR | EMAC_RSR_REC | EMAC_RSR_BNA;

   //First disable all EMAC interrupts
   EMAC->EMAC_IDR = 0xFFFFFFFF;
   //Only the desired ones are enabled
   EMAC->EMAC_IER = EMAC_IER_ROVR | EMAC_IER_TCOMP | EMAC_IER_TXERR |
      EMAC_IER_RLE | EMAC_IER_TUND | EMAC_IER_RXUBR | EMAC_IER_RCOMP;

   //Read EMAC ISR register to clear any pending interrupt
   status = EMAC->EMAC_ISR;

   //Configure interrupt controller
   AIC->AIC_SSR = ID_EMAC;
   AIC->AIC_SMR = AIC_SMR_SRCTYPE_INT_LEVEL_SENSITIVE | AIC_SMR_PRIOR(SAMA5D3_ETH_IRQ_PRIORITY);
   AIC->AIC_SVR = (uint32_t) sama5d3EthIrqHandler;

   //Enable the EMAC to transmit and receive data
   EMAC->EMAC_NCR |= EMAC_NCR_TE | EMAC_NCR_RE;

   //Force the TCP/IP stack to check the link state
   osSetEvent(&interface->nicRxEvent);
   //SAMA5D3 Ethernet MAC is now ready to send
   osSetEvent(&interface->nicTxEvent);

   //Successful initialization
   return NO_ERROR;
}


//SAMA5D3-Xplained evaluation board?
#if defined(USE_SAMA5D3_XPLAINED)

/**
 * @brief GPIO configuration
 * @param[in] interface Underlying network interface
 **/

void sama5d3EthInitGpio(NetInterface *interface)
{
   //Enable PIO peripheral clock
   PMC->PMC_PCER0 = (1 << ID_PIOC);

   //Disable pull-up resistors on RMII pins
   PIOC->PIO_PUDR = EMAC_RMII_MASK;
   //Disable interrupts-on-change
   PIOC->PIO_IDR = EMAC_RMII_MASK;
   //Assign RMII pins to peripheral A function
   PIOC->PIO_ABCDSR[0] &= ~EMAC_RMII_MASK;
   PIOC->PIO_ABCDSR[1] &= ~EMAC_RMII_MASK;
   //Disable the PIO from controlling the corresponding pins
   PIOC->PIO_PDR = EMAC_RMII_MASK;

   //Select RMII operation mode and enable transceiver clock
   EMAC->EMAC_USRIO = EMAC_USRIO_CLKEN | EMAC_USRIO_RMII;
}

#endif


/**
 * @brief Initialize buffer descriptors
 * @param[in] interface Underlying network interface
 **/

void sama5d3EthInitBufferDesc(NetInterface *interface)
{
   uint_t i;
   uint32_t address;

   //Initialize TX buffer descriptors
   for(i = 0; i < SAMA5D3_ETH_TX_BUFFER_COUNT; i++)
   {
      //Calculate the address of the current TX buffer
      address = (uint32_t) txBuffer[i];
      //Write the address to the descriptor entry
      txBufferDesc[i].address = address;
      //Initialize status field
      txBufferDesc[i].status = EMAC_TX_USED;
   }

   //Mark the last descriptor entry with the wrap flag
   txBufferDesc[i - 1].status |= EMAC_TX_WRAP;
   //Initialize TX buffer index
   txBufferIndex = 0;

   //Initialize RX buffer descriptors
   for(i = 0; i < SAMA5D3_ETH_RX_BUFFER_COUNT; i++)
   {
      //Calculate the address of the current RX buffer
      address = (uint32_t) rxBuffer[i];
      //Write the address to the descriptor entry
      rxBufferDesc[i].address = address & EMAC_RX_ADDRESS;
      //Clear status field
      rxBufferDesc[i].status = 0;
   }

   //Mark the last descriptor entry with the wrap flag
   rxBufferDesc[i - 1].address |= EMAC_RX_WRAP;
   //Initialize RX buffer index
   rxBufferIndex = 0;

   //Start location of the TX descriptor list
   EMAC->EMAC_TBQP = (uint32_t) txBufferDesc;
   //Start location of the RX descriptor list
   EMAC->EMAC_RBQP = (uint32_t) rxBufferDesc;
}


/**
 * @brief SAMA5D3 Ethernet MAC timer handler
 *
 * This routine is periodically called by the TCP/IP stack to
 * handle periodic operations such as polling the link state
 *
 * @param[in] interface Underlying network interface
 **/

void sama5d3EthTick(NetInterface *interface)
{
   //Handle periodic operations
   interface->phyDriver->tick(interface);
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void sama5d3EthEnableIrq(NetInterface *interface)
{
   //Enable Ethernet MAC interrupts
   AIC->AIC_SSR = ID_EMAC;
   AIC->AIC_IECR = AIC_IECR_INTEN;
   //Enable Ethernet PHY interrupts
   interface->phyDriver->enableIrq(interface);
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void sama5d3EthDisableIrq(NetInterface *interface)
{
   //Disable Ethernet MAC interrupts
   AIC->AIC_SSR = ID_EMAC;
   AIC->AIC_IDCR = AIC_IDCR_INTD;
   //Disable Ethernet PHY interrupts
   interface->phyDriver->disableIrq(interface);
}


/**
 * @brief SAMA5D3 Ethernet MAC interrupt service routine
 **/

void sama5d3EthIrqHandler(void)
{
   bool_t flag;
   volatile uint32_t isr;
   volatile uint32_t tsr;
   volatile uint32_t rsr;
   NetInterface *interface;

   //Enter interrupt service routine
   osEnterIsr();

   //Point to the structure describing the network interface
   interface = &netInterface[SAMA5D3_ETH_INTERFACE_ID];
   //This flag will be set if a higher priority task must be woken
   flag = FALSE;

   //Each time the software reads EMAC_ISR, it has to check the
   //contents of EMAC_TSR, EMAC_RSR and EMAC_NSR
   isr = EMAC->EMAC_ISR;
   tsr = EMAC->EMAC_TSR;
   rsr = EMAC->EMAC_RSR;

   //A packet has been transmitted?
   if(tsr & (EMAC_TSR_UND | EMAC_TSR_COMP | EMAC_TSR_BEX |
      EMAC_TSR_TGO | EMAC_TSR_RLES | EMAC_TSR_COL | EMAC_TSR_UBR))
   {
      //Only clear TSR flags that are currently set
      EMAC->EMAC_TSR = tsr;

      //Check whether the TX buffer is available for writing
      if(txBufferDesc[txBufferIndex].status & EMAC_TX_USED)
      {
         //Notify the user that the transmitter is ready to send
         flag |= osSetEventFromIsr(&interface->nicTxEvent);
      }
   }
   //A packet has been received?
   if(rsr & (EMAC_RSR_OVR | EMAC_RSR_REC | EMAC_RSR_BNA))
   {
      //Notify the user that a packet has been received
      flag |= osSetEventFromIsr(&interface->nicRxEvent);
   }

   //Write AIC_EOICR register before exiting
   AIC->AIC_EOICR = 0;

   //Leave interrupt service routine
   osExitIsr(flag);
}


/**
 * @brief SAMA5D3 Ethernet MAC event handler
 * @param[in] interface Underlying network interface
 **/

void sama5d3EthEventHandler(NetInterface *interface)
{
   uint32_t rsr;
   uint_t length;
   bool_t linkStateChange;

   //Read receive status
   rsr = EMAC->EMAC_RSR;

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
            uint32_t config = EMAC->EMAC_NCFGR;

            //10BASE-T or 100BASE-TX operation mode?
            if(interface->speed100)
               config |= EMAC_NCFGR_SPD;
            else
               config &= ~EMAC_NCFGR_SPD;

            //Half-duplex or full-duplex mode?
            if(interface->fullDuplex)
               config |= EMAC_NCFGR_FD;
            else
               config &= ~EMAC_NCFGR_FD;

            //Write configuration value back to NCFGR register
            EMAC->EMAC_NCFGR = config;
         }

         //Process link state change event
         nicNotifyLinkChange(interface);
      }
   }

   //Packet received?
   if(rsr & (EMAC_RSR_OVR | EMAC_RSR_REC | EMAC_RSR_BNA))
   {
      //Only clear RSR flags that are currently set
      EMAC->EMAC_RSR = rsr;

      //Process all the pending packets
      while(1)
      {
         //Check whether a packet has been received
         length = sama5d3EthReceivePacket(interface, interface->ethFrame, ETH_MAX_FRAME_SIZE);
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

error_t sama5d3EthSetMacFilter(NetInterface *interface)
{
   uint_t i;
   uint_t j;
   uint32_t hashTable[2];

   //Debug message
   TRACE_INFO("Updating SAMA5D3 hash table...\r\n");

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
   EMAC->EMAC_HRB = hashTable[0];
   EMAC->EMAC_HRT = hashTable[1];

   //Debug message
   TRACE_INFO("  HRB = %08" PRIX32 "\r\n", EMAC->EMAC_HRB);
   TRACE_INFO("  HRT = %08" PRIX32 "\r\n", EMAC->EMAC_HRT);

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

error_t sama5d3EthSendPacket(NetInterface *interface,
   const NetBuffer *buffer, size_t offset)
{
   //Retrieve the length of the packet
   size_t length = netBufferGetLength(buffer) - offset;

   //Check the frame length
   if(length > SAMA5D3_ETH_TX_BUFFER_SIZE)
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
      //Report an error
      return ERROR_INVALID_LENGTH;
   }

   //Make sure the current buffer is available for writing
   if(!(txBufferDesc[txBufferIndex].status & EMAC_TX_USED))
      return ERROR_FAILURE;

   //Copy user data to the transmit buffer
   netBufferRead(txBuffer[txBufferIndex], buffer, offset, length);

   //Set the necessary flags in the descriptor entry
   if(txBufferIndex < (SAMA5D3_ETH_TX_BUFFER_COUNT - 1))
   {
      //Write the status word
      txBufferDesc[txBufferIndex].status =
         EMAC_TX_LAST | (length & EMAC_TX_LENGTH);

      //Point to the next buffer
      txBufferIndex++;
   }
   else
   {
      //Write the status word
      txBufferDesc[txBufferIndex].status = EMAC_TX_WRAP |
         EMAC_TX_LAST | (length & EMAC_TX_LENGTH);

      //Wrap around
      txBufferIndex = 0;
   }

   //Set the TSTART bit to initiate transmission
   EMAC->EMAC_NCR |= EMAC_NCR_TSTART;

   //Check whether the next buffer is available for writing
   if(txBufferDesc[txBufferIndex].status & EMAC_TX_USED)
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

uint_t sama5d3EthReceivePacket(NetInterface *interface,
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
   for(i = 0; i < SAMA5D3_ETH_RX_BUFFER_COUNT; i++)
   {
      //Point to the current descriptor
      index = rxBufferIndex + i;
      //Wrap around to the beginning of the buffer if necessary
      if(index >= SAMA5D3_ETH_RX_BUFFER_COUNT)
         index -= SAMA5D3_ETH_RX_BUFFER_COUNT;

      //No more entries to process?
      if(!(rxBufferDesc[index].address & EMAC_RX_OWNERSHIP))
      {
         break;
      }
      //A valid SOF has been found?
      if(rxBufferDesc[index].status & EMAC_RX_SOF)
      {
         //Save the position of the SOF
         sofIndex = i;
      }
      //A valid EOF has been found?
      if((rxBufferDesc[index].status & EMAC_RX_EOF) && sofIndex != UINT_MAX)
      {
         //Save the position of the EOF
         eofIndex = i;
         //Retrieve the length of the frame
         n = rxBufferDesc[index].status & EMAC_RX_LENGTH;
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
         n = MIN(size, SAMA5D3_ETH_RX_BUFFER_SIZE);
         //Copy data from receive buffer
         memcpy(buffer, rxBuffer[rxBufferIndex], n);
         //Advance data pointer
         buffer += n;
         //Update byte counters
         length += n;
         size -= n;
      }

      //Mark the current buffer as free
      rxBufferDesc[rxBufferIndex].address &= ~EMAC_RX_OWNERSHIP;

      //Point to the following entry
      rxBufferIndex++;
      //Wrap around to the beginning of the buffer if necessary
      if(rxBufferIndex >= SAMA5D3_ETH_RX_BUFFER_COUNT)
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

void sama5d3EthWritePhyReg(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
   //Set up a write operation
   uint32_t value = EMAC_MAN_SOF(1) | EMAC_MAN_RW(1) | EMAC_MAN_CODE(2);
   //PHY address
   value |= EMAC_MAN_PHYA(phyAddr);
   //Register address
   value |= EMAC_MAN_REGA(regAddr);
   //Register value
   value |= EMAC_MAN_DATA(data);

   //Start a write operation
   EMAC->EMAC_MAN = value;
   //Wait for the write to complete
   while(!(EMAC->EMAC_NSR & EMAC_NSR_IDLE));
}


/**
 * @brief Read PHY register
 * @param[in] phyAddr PHY address
 * @param[in] regAddr Register address
 * @return Register value
 **/

uint16_t sama5d3EthReadPhyReg(uint8_t phyAddr, uint8_t regAddr)
{
   //Set up a read operation
   uint32_t value = EMAC_MAN_SOF(1) | EMAC_MAN_RW(2) | EMAC_MAN_CODE(2);
   //PHY address
   value |= EMAC_MAN_PHYA(phyAddr);
   //Register address
   value |= EMAC_MAN_REGA(regAddr);

   //Start a read operation
   EMAC->EMAC_MAN = value;
   //Wait for the read to complete
   while(!(EMAC->EMAC_NSR & EMAC_NSR_IDLE));

   //Return PHY register contents
   return EMAC->EMAC_MAN & EMAC_MAN_DATA_Msk;
}
