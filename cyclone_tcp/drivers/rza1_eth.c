/**
 * @file rza1_eth.c
 * @brief Renesas RZ/A1 Ethernet MAC controller
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
#include "iodefine.h"
#include "cpg_iobitmask.h"
#include "intc.h"
#include "core/net.h"
#include "drivers/rza1_eth.h"
#include "debug.h"

//IAR EWARM compiler?
#if defined(__ICCARM__)

//Transmit buffer
#pragma data_alignment = 32
static uint8_t txBuffer[RZA1_ETH_TX_BUFFER_COUNT][RZA1_ETH_TX_BUFFER_SIZE];
//Receive buffer
#pragma data_alignment = 32
static uint8_t rxBuffer[RZA1_ETH_RX_BUFFER_COUNT][RZA1_ETH_RX_BUFFER_SIZE];
//Transmit DMA descriptors
#pragma data_alignment = 32
static Rza1TxDmaDesc txDmaDesc[RZA1_ETH_TX_BUFFER_COUNT];
//Receive DMA descriptors
#pragma data_alignment = 32
static Rza1RxDmaDesc rxDmaDesc[RZA1_ETH_RX_BUFFER_COUNT];

//ARM or GCC compiler?
#else

//Transmit buffer
static uint8_t txBuffer[RZA1_ETH_TX_BUFFER_COUNT][RZA1_ETH_TX_BUFFER_SIZE]
   __attribute__((section(".BSS_DMAC_SAMPLE_INTERNAL_RAM"), aligned(32)));
//Receive buffer
static uint8_t rxBuffer[RZA1_ETH_RX_BUFFER_COUNT][RZA1_ETH_RX_BUFFER_SIZE]
   __attribute__((section(".BSS_DMAC_SAMPLE_INTERNAL_RAM"), aligned(32)));
//Transmit DMA descriptors
static Rza1TxDmaDesc txDmaDesc[RZA1_ETH_TX_BUFFER_COUNT]
   __attribute__((section(".BSS_DMAC_SAMPLE_INTERNAL_RAM"), aligned(32)));
//Receive DMA descriptors
static Rza1RxDmaDesc rxDmaDesc[RZA1_ETH_RX_BUFFER_COUNT]
   __attribute__((section(".BSS_DMAC_SAMPLE_INTERNAL_RAM"), aligned(32)));

#endif

//Current transmit descriptor
static uint_t txIndex;
//Current receive descriptor
static uint_t rxIndex;


/**
 * @brief RZ/A1 Ethernet MAC driver
 **/

const NicDriver rza1EthDriver =
{
   NIC_TYPE_ETHERNET,
   ETH_MTU,
   rza1EthInit,
   rza1EthTick,
   rza1EthEnableIrq,
   rza1EthDisableIrq,
   rza1EthEventHandler,
   rza1EthSetMacFilter,
   rza1EthSendPacket,
   rza1EthWritePhyReg,
   rza1EthReadPhyReg,
   TRUE,
   TRUE,
   TRUE
};


/**
 * @brief RZ/A1 Ethernet MAC initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t rza1EthInit(NetInterface *interface)
{
   error_t error;

   //Debug message
   TRACE_INFO("Initializing RZ/A1 Ethernet MAC...\r\n");

   //Enable Ethernet peripheral clock
   CPG.STBCR7 &= ~CPG_STBCR7_MSTP74;

   //GPIO configuration
   rza1EthInitGpio(interface);

   //Perform software reset
   ETHER.ARSTR = ETHER_ARSTR_ARST;
   //Wait for the reset to complete
   sleep(10);

   //Start EDMAC transmitting and receiving units
   ETHER.EDSR0 = ETHER_EDSR0_ENT | ETHER_EDSR0_ENR;

   //To execute a software reset with this register, 1 must be
   //written to both the SWRT and SWRR bits simultaneously
   ETHER.EDMR0 = ETHER_EDMR0_SWRT | ETHER_EDMR0_SWRR;
   //Wait for the reset to complete
   while(ETHER.EDMR0 & (ETHER_EDMR0_SWRT | ETHER_EDMR0_SWRR));

   //PHY transceiver initialization
   error = interface->phyDriver->init(interface);
   //Failed to initialize PHY transceiver?
   if(error) return error;

   //Initialize DMA descriptor lists
   rza1EthInitDmaDesc(interface);

   //Select little endian mode and set descriptor length (16 bytes)
   ETHER.EDMR0 = ETHER_EDMR0_DE | ETHER_EDMR0_DL_16;

   //Error masks
   ETHER.TRSCER0 = 0;
   //Use store and forward mode
   ETHER.TFTR0 = 0;

   //Set transmit FIFO size and receive FIFO size (2048 bytes)
   ETHER.FDR0 = ETHER_FDR0_TFD_2048 | ETHER_FDR0_RFD_2048;

   //Enable continuous reception of multiple frames
   ETHER.RMCR0 = ETHER_RMCR0_RNC;
   //No padding insertion into receive data
   ETHER.RPADIR0 = 0;

   //Receive FIFO threshold (8 frames or 2048-64 bytes)
   ETHER.FCFTR0 = ETHER_FCFTR0_RFF_8 | ETHER_FCFTR0_RFD_2048;

   //Intelligent checksum operation mode
   ETHER.CSMR = 0;

   //Enable multicast address filtering
   ETHER.ECMR0 |= ETH_ECMR0_MCT;

   //Set the upper 32 bits of the MAC address
   ETHER.MAHR0 = (interface->macAddr.b[0] << 24) | (interface->macAddr.b[1] << 16) |
      (interface->macAddr.b[2] << 8) | interface->macAddr.b[3];

   //Set the lower 16 bits of the MAC address
   ETHER.MALR0 = (interface->macAddr.b[4] << 8) | interface->macAddr.b[5];

   //Maximum frame length that can be accepted
   ETHER.RFLR0 = 1518;
   //Automatic pause frame
   ETHER.APR0 = 0;
   //Manual pause frame
   ETHER.MPR0 = 0;
   //Automatic pause frame retransmit count
   ETHER.TPAUSER0 = 0;

   //Disable all EMAC interrupts
   ETHER.ECSIPR0 = 0;

   //Enable the desired EDMAC interrupts
   ETHER.EESIPR0 =  ETHER_EESIPR0_TWBIP | ETHER_EESIPR0_FRIP;

   //Register interrupt handler
   R_INTC_Regist_Int_Func(INTC_ID_ETHERI, rza1EthIrqHandler);
   //Configure interrupt priority
   R_INTC_Set_Priority(INTC_ID_ETHERI, RZA1_ETH_IRQ_PRIORITY);

   //Enable EDMAC transmission and reception
   ETHER.ECMR0 |= ETH_ECMR0_RE | ETH_ECMR0_TE;

   //Instruct the DMA to poll the receive descriptor list
   ETHER.EDRRR0 = ETHER_EDRRR0_RR;

   //Force the TCP/IP stack to check the link state
   osSetEvent(&interface->nicRxEvent);
   //RZ/A1 Ethernet MAC is now ready to send
   osSetEvent(&interface->nicTxEvent);

   //Successful initialization
   return NO_ERROR;
}


//RSK RZ/A1H, Hachiko or Pekoe evaluation board?
#if defined(USE_RSK_RZA1H) || defined(USE_HACHIKO) || defined(USE_PEKOE)

/**
 * @brief GPIO configuration
 * @param[in] interface Underlying network interface
 **/

void rza1EthInitGpio(NetInterface *interface)
{
//RSK RZ/A1H or Hachiko evaluation board?
#if defined(USE_RSK_RZA1H) || defined(USE_HACHIKO)
   //Configure ET_COL (P1_14)
   PORT1.PMCn.BIT.PMCn14 = 1;
   PORT1.PFCn.BIT.PFCn14 = 1;
   PORT1.PFCEn.BIT.PFCEn14 = 1;
   PORT1.PFCAEn.BIT.PFCAEn14 = 0;
   PORT1.PIPCn.BIT.PIPCn14 = 1;

   //Configure ET_TXCLK (P2_0)
   PORT2.PMCn.BIT.PMCn0 = 1;
   PORT2.PFCn.BIT.PFCn0 = 1;
   PORT2.PFCEn.BIT.PFCEn0 = 0;
   PORT2.PFCAEn.BIT.PFCAEn0 = 0;
   PORT2.PIPCn.BIT.PIPCn0 = 1;

   //Configure ET_TXER (P2_1)
   PORT2.PMCn.BIT.PMCn1 = 1;
   PORT2.PFCn.BIT.PFCn1 = 1;
   PORT2.PFCEn.BIT.PFCEn1 = 0;
   PORT2.PFCAEn.BIT.PFCAEn1 = 0;
   PORT2.PIPCn.BIT.PIPCn1 = 1;

   //Configure ET_TXEN (P2_2)
   PORT2.PMCn.BIT.PMCn2 = 1;
   PORT2.PFCn.BIT.PFCn2 = 1;
   PORT2.PFCEn.BIT.PFCEn2 = 0;
   PORT2.PFCAEn.BIT.PFCAEn2 = 0;
   PORT2.PIPCn.BIT.PIPCn2 = 1;

   //Configure ET_CRS (P2_3)
   PORT2.PMCn.BIT.PMCn3 = 1;
   PORT2.PFCn.BIT.PFCn3 = 1;
   PORT2.PFCEn.BIT.PFCEn3 = 0;
   PORT2.PFCAEn.BIT.PFCAEn3 = 0;
   PORT2.PIPCn.BIT.PIPCn3 = 1;

   //Configure ET_TXD0 (P2_4)
   PORT2.PMCn.BIT.PMCn4 = 1;
   PORT2.PFCn.BIT.PFCn4 = 1;
   PORT2.PFCEn.BIT.PFCEn4 = 0;
   PORT2.PFCAEn.BIT.PFCAEn4 = 0;
   PORT2.PIPCn.BIT.PIPCn4 = 1;

   //Configure ET_TXD1 (P2_5)
   PORT2.PMCn.BIT.PMCn5 = 1;
   PORT2.PFCn.BIT.PFCn5 = 1;
   PORT2.PFCEn.BIT.PFCEn5 = 0;
   PORT2.PFCAEn.BIT.PFCAEn5 = 0;
   PORT2.PIPCn.BIT.PIPCn5 = 1;

   //Configure ET_TXD2 (P2_6)
   PORT2.PMCn.BIT.PMCn6 = 1;
   PORT2.PFCn.BIT.PFCn6 = 1;
   PORT2.PFCEn.BIT.PFCEn6 = 0;
   PORT2.PFCAEn.BIT.PFCAEn6 = 0;
   PORT2.PIPCn.BIT.PIPCn6 = 1;

   //Configure ET_TXD3 (P2_7)
   PORT2.PMCn.BIT.PMCn7 = 1;
   PORT2.PFCn.BIT.PFCn7 = 1;
   PORT2.PFCEn.BIT.PFCEn7 = 0;
   PORT2.PFCAEn.BIT.PFCAEn7 = 0;
   PORT2.PIPCn.BIT.PIPCn7 = 1;

   //Configure ET_RXD0 (P2_8)
   PORT2.PMCn.BIT.PMCn8 = 1;
   PORT2.PFCn.BIT.PFCn8 = 1;
   PORT2.PFCEn.BIT.PFCEn8 = 0;
   PORT2.PFCAEn.BIT.PFCAEn8 = 0;
   PORT2.PIPCn.BIT.PIPCn8 = 1;

   //Configure ET_RXD1 (P2_9)
   PORT2.PMCn.BIT.PMCn9 = 1;
   PORT2.PFCn.BIT.PFCn9 = 1;
   PORT2.PFCEn.BIT.PFCEn9 = 0;
   PORT2.PFCAEn.BIT.PFCAEn9 = 0;
   PORT2.PIPCn.BIT.PIPCn9 = 1;

   //Configure ET_RXD2 (P2_10)
   PORT2.PMCn.BIT.PMCn10 = 1;
   PORT2.PFCn.BIT.PFCn10 = 1;
   PORT2.PFCEn.BIT.PFCEn10 = 0;
   PORT2.PFCAEn.BIT.PFCAEn10 = 0;
   PORT2.PIPCn.BIT.PIPCn10 = 1;

   //Configure ET_RXD3 (P2_11)
   PORT2.PMCn.BIT.PMCn11 = 1;
   PORT2.PFCn.BIT.PFCn11 = 1;
   PORT2.PFCEn.BIT.PFCEn11 = 0;
   PORT2.PFCAEn.BIT.PFCAEn11 = 0;
   PORT2.PIPCn.BIT.PIPCn11 = 1;

   //Configure ET_MDIO (P3_3)
   PORT3.PMCn.BIT.PMCn3 = 1;
   PORT3.PFCn.BIT.PFCn3 = 1;
   PORT3.PFCEn.BIT.PFCEn3 = 0;
   PORT3.PFCAEn.BIT.PFCAEn3 = 0;
   PORT3.PIPCn.BIT.PIPCn3 = 1;

   //Configure ET_RXCLK (P3_4)
   PORT3.PMCn.BIT.PMCn4 = 1;
   PORT3.PFCn.BIT.PFCn4 = 1;
   PORT3.PFCEn.BIT.PFCEn4 = 0;
   PORT3.PFCAEn.BIT.PFCAEn4 = 0;
   PORT3.PIPCn.BIT.PIPCn4 = 1;

   //Configure ET_RXER (P3_5)
   PORT3.PMCn.BIT.PMCn5 = 1;
   PORT3.PFCn.BIT.PFCn5 = 1;
   PORT3.PFCEn.BIT.PFCEn5 = 0;
   PORT3.PFCAEn.BIT.PFCAEn5 = 0;
   PORT3.PIPCn.BIT.PIPCn5 = 1;

   //Configure ET_RXDV (P3_6)
   PORT3.PMCn.BIT.PMCn6 = 1;
   PORT3.PFCn.BIT.PFCn6 = 1;
   PORT3.PFCEn.BIT.PFCEn6 = 0;
   PORT3.PFCAEn.BIT.PFCAEn6 = 0;
   PORT3.PIPCn.BIT.PIPCn6 = 1;

   //Configure ET_MDC (P5_9)
   PORT5.PMCn.BIT.PMCn9 = 1;
   PORT5.PFCn.BIT.PFCn9 = 1;
   PORT5.PFCEn.BIT.PFCEn9 = 0;
   PORT5.PFCAEn.BIT.PFCAEn9 = 0;
   PORT5.PIPCn.BIT.PIPCn9 = 1;

//Pekoe evaluation board?
#elif defined(USE_PEKOE)
   //Configure ET_TXD0 (P8_0)
   PORT8.PMCn.BIT.PMCn0 = 1;
   PORT8.PFCn.BIT.PFCn0 = 1;
   PORT8.PFCEn.BIT.PFCEn0 = 0;
   PORT8.PFCAEn.BIT.PFCAEn0 = 0;
   PORT8.PIPCn.BIT.PIPCn0 = 1;

   //Configure ET_TXD1 (P8_1)
   PORT8.PMCn.BIT.PMCn1 = 1;
   PORT8.PFCn.BIT.PFCn1 = 1;
   PORT8.PFCEn.BIT.PFCEn1 = 0;
   PORT8.PFCAEn.BIT.PFCAEn1 = 0;
   PORT8.PIPCn.BIT.PIPCn1 = 1;

   //Configure ET_TXD2 (P8_2)
   PORT8.PMCn.BIT.PMCn2 = 1;
   PORT8.PFCn.BIT.PFCn2 = 1;
   PORT8.PFCEn.BIT.PFCEn2 = 0;
   PORT8.PFCAEn.BIT.PFCAEn2 = 0;
   PORT8.PIPCn.BIT.PIPCn2 = 1;

   //Configure ET_TXD3 (P8_3)
   PORT8.PMCn.BIT.PMCn3 = 1;
   PORT8.PFCn.BIT.PFCn3 = 1;
   PORT8.PFCEn.BIT.PFCEn3 = 0;
   PORT8.PFCAEn.BIT.PFCAEn3 = 0;
   PORT8.PIPCn.BIT.PIPCn3 = 1;

   //Configure ET_TXCLK (P8_4)
   PORT8.PMCn.BIT.PMCn4 = 1;
   PORT8.PFCn.BIT.PFCn4 = 1;
   PORT8.PFCEn.BIT.PFCEn4 = 0;
   PORT8.PFCAEn.BIT.PFCAEn4 = 0;
   PORT8.PIPCn.BIT.PIPCn4 = 1;

   //Configure ET_TXER (P8_5)
   PORT8.PMCn.BIT.PMCn5 = 1;
   PORT8.PFCn.BIT.PFCn5 = 1;
   PORT8.PFCEn.BIT.PFCEn5 = 0;
   PORT8.PFCAEn.BIT.PFCAEn5 = 0;
   PORT8.PIPCn.BIT.PIPCn5 = 1;

   //Configure ET_TXEN (P8_6)
   PORT8.PMCn.BIT.PMCn6 = 1;
   PORT8.PFCn.BIT.PFCn6 = 1;
   PORT8.PFCEn.BIT.PFCEn6 = 0;
   PORT8.PFCAEn.BIT.PFCAEn6 = 0;
   PORT8.PIPCn.BIT.PIPCn6 = 1;

   //Configure ET_RXD0 (P8_7)
   PORT8.PMCn.BIT.PMCn7 = 1;
   PORT8.PFCn.BIT.PFCn7 = 1;
   PORT8.PFCEn.BIT.PFCEn7 = 0;
   PORT8.PFCAEn.BIT.PFCAEn7 = 0;
   PORT8.PIPCn.BIT.PIPCn7 = 1;

   //Configure ET_RXD1 (P8_8)
   PORT8.PMCn.BIT.PMCn8 = 1;
   PORT8.PFCn.BIT.PFCn8 = 1;
   PORT8.PFCEn.BIT.PFCEn8 = 0;
   PORT8.PFCAEn.BIT.PFCAEn8 = 0;
   PORT8.PIPCn.BIT.PIPCn8 = 1;

   //Configure ET_RXD2 (P8_9)
   PORT8.PMCn.BIT.PMCn9 = 1;
   PORT8.PFCn.BIT.PFCn9 = 1;
   PORT8.PFCEn.BIT.PFCEn9 = 0;
   PORT8.PFCAEn.BIT.PFCAEn9 = 0;
   PORT8.PIPCn.BIT.PIPCn9 = 1;

   //Configure ET_RXD3 (P8_10)
   PORT8.PMCn.BIT.PMCn10 = 1;
   PORT8.PFCn.BIT.PFCn10 = 1;
   PORT8.PFCEn.BIT.PFCEn10 = 0;
   PORT8.PFCAEn.BIT.PFCAEn10 = 0;
   PORT8.PIPCn.BIT.PIPCn10 = 1;

   //Configure ET_COL (P8_14)
   PORT8.PMCn.BIT.PMCn14 = 1;
   PORT8.PFCn.BIT.PFCn14 = 1;
   PORT8.PFCEn.BIT.PFCEn14 = 0;
   PORT8.PFCAEn.BIT.PFCAEn14 = 0;
   PORT8.PIPCn.BIT.PIPCn14 = 1;

   //Configure ET_CRS (P8_15)
   PORT8.PMCn.BIT.PMCn15 = 1;
   PORT8.PFCn.BIT.PFCn15 = 1;
   PORT8.PFCEn.BIT.PFCEn15 = 0;
   PORT8.PFCAEn.BIT.PFCAEn15 = 0;
   PORT8.PIPCn.BIT.PIPCn15 = 1;

   //Configure ET_MDC (P9_0)
   PORT9.PMCn.BIT.PMCn0 = 1;
   PORT9.PFCn.BIT.PFCn0 = 1;
   PORT9.PFCEn.BIT.PFCEn0 = 0;
   PORT9.PFCAEn.BIT.PFCAEn0 = 0;
   PORT9.PIPCn.BIT.PIPCn0 = 1;

   //Configure ET_MDIO (P9_1)
   PORT9.PMCn.BIT.PMCn1 = 1;
   PORT9.PFCn.BIT.PFCn1 = 1;
   PORT9.PFCEn.BIT.PFCEn1 = 0;
   PORT9.PFCAEn.BIT.PFCAEn1 = 0;
   PORT9.PIPCn.BIT.PIPCn1 = 1;

   //Configure ET_RXCLK (P9_2)
   PORT9.PMCn.BIT.PMCn2 = 1;
   PORT9.PFCn.BIT.PFCn2 = 1;
   PORT9.PFCEn.BIT.PFCEn2 = 0;
   PORT9.PFCAEn.BIT.PFCAEn2 = 0;
   PORT9.PIPCn.BIT.PIPCn2 = 1;

   //Configure ET_RXER (P9_3)
   PORT9.PMCn.BIT.PMCn3 = 1;
   PORT9.PFCn.BIT.PFCn3 = 1;
   PORT9.PFCEn.BIT.PFCEn3 = 0;
   PORT9.PFCAEn.BIT.PFCAEn3 = 0;
   PORT9.PIPCn.BIT.PIPCn3 = 1;

   //Configure ET_RXDV (P9_4)
   PORT9.PMCn.BIT.PMCn4 = 1;
   PORT9.PFCn.BIT.PFCn4 = 1;
   PORT9.PFCEn.BIT.PFCEn4 = 0;
   PORT9.PFCAEn.BIT.PFCAEn4 = 0;
   PORT9.PIPCn.BIT.PIPCn4 = 1;

   //Configure PHY_RST (P2_7)
   PORT2.PMCn.BIT.PMCn7 = 0;
   PORT2.PIPCn.BIT.PIPCn7 = 0;
   PORT2.PMn.BIT.PMn7 = 0;

   //Reset the PHY transceiver
   PORT2.Pn.BIT.Pn7 = 0;
   sleep(10);

   //Take the PHY transceiver out of reset
   PORT2.Pn.BIT.Pn7 = 1;
   sleep(10);
#endif
}

#endif


/**
 * @brief Initialize DMA descriptor lists
 * @param[in] interface Underlying network interface
 **/

void rza1EthInitDmaDesc(NetInterface *interface)
{
   uint_t i;

   //Initialize TX descriptors
   for(i = 0; i < RZA1_ETH_TX_BUFFER_COUNT; i++)
   {
      //The descriptor is initially owned by the application
      txDmaDesc[i].td0 = 0;
      //Transmit buffer length
      txDmaDesc[i].td1 = 0;
      //Transmit buffer address
      txDmaDesc[i].td2 = (uint32_t) txBuffer[i];
      //Clear padding field
      txDmaDesc[i].padding = 0;
   }

   //Mark the last descriptor entry with the TDLE flag
   txDmaDesc[i - 1].td0 |= ETHER_TD0_TDLE;
   //Initialize TX descriptor index
   txIndex = 0;

   //Initialize RX descriptors
   for(i = 0; i < RZA1_ETH_RX_BUFFER_COUNT; i++)
   {
      //The descriptor is initially owned by the DMA
      rxDmaDesc[i].rd0 = ETHER_RD0_RACT;
      //Receive buffer length
      rxDmaDesc[i].rd1 = (RZA1_ETH_RX_BUFFER_SIZE << 16) & ETHER_RD1_RBL;
      //Receive buffer address
      rxDmaDesc[i].rd2 = (uint32_t) rxBuffer[i];
      //Clear padding field
      rxDmaDesc[i].padding = 0;
   }

   //Mark the last descriptor entry with the RDLE flag
   rxDmaDesc[i - 1].rd0 |= ETHER_RD0_RDLE;
   //Initialize RX descriptor index
   rxIndex = 0;

   //Address of the first TX descriptor
   ETHER.TDLAR0 = (uint32_t ) &txDmaDesc[0];
   ETHER.TDFAR0 = (uint32_t ) &txDmaDesc[0];
   //Address of the last TX descriptor
   ETHER.TDFXR0 = (uint32_t ) &txDmaDesc[RZA1_ETH_TX_BUFFER_COUNT - 1];
   //Set TDLF flag
   ETHER.TDFFR0 = ETHER_TDFFR_TDLF;

   //Address of the first RX descriptor
   ETHER.RDLAR0 = (uint32_t ) &rxDmaDesc[0];
   ETHER.RDFAR0 = (uint32_t ) &rxDmaDesc[0];
   //Address of the last RX descriptor
   ETHER.RDFXR0 = (uint32_t ) &rxDmaDesc[RZA1_ETH_RX_BUFFER_COUNT - 1];
   //Set RDLF flag
   ETHER.RDFFR0 = ETHER_RDFFR0_RDLF;
}


/**
 * @brief RZ/A1 Ethernet MAC timer handler
 *
 * This routine is periodically called by the TCP/IP stack to
 * handle periodic operations such as polling the link state
 *
 * @param[in] interface Underlying network interface
 **/

void rza1EthTick(NetInterface *interface)
{
   //Handle periodic operations
   interface->phyDriver->tick(interface);
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void rza1EthEnableIrq(NetInterface *interface)
{
   //Enable Ethernet MAC interrupts
   R_INTC_Enable(INTC_ID_ETHERI);
   //Enable Ethernet PHY interrupts
   interface->phyDriver->enableIrq(interface);
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void rza1EthDisableIrq(NetInterface *interface)
{
   //Disable Ethernet MAC interrupts
   R_INTC_Disable(INTC_ID_ETHERI);
   //Disable Ethernet PHY interrupts
   interface->phyDriver->disableIrq(interface);
}


/**
 * @brief RZ/A1 Ethernet MAC interrupt service routine
 * @param[in] intSense Unused parameter
 **/

void rza1EthIrqHandler(uint32_t intSense)
{
   bool_t flag;
   uint32_t status;
   NetInterface *interface;

   //Enter interrupt service routine
   osEnterIsr();

   //Point to the structure describing the network interface
   interface = &netInterface[0];
   //This flag will be set if a higher priority task must be woken
   flag = FALSE;

   //Read interrupt status register
   status = ETHER.EESR0;

   //A packet has been transmitted?
   if(status & ETHER_EESR0_TWB)
   {
      //Clear TWB interrupt flag
      ETHER.EESR0 = ETHER_EESR0_TWB;

      //Check whether the TX buffer is available for writing
      if(!(txDmaDesc[txIndex].td0 & ETHER_TD0_TACT))
      {
         //Notify the user that the transmitter is ready to send
         flag |= osSetEventFromIsr(&interface->nicTxEvent);
      }
   }
   //A packet has been received?
   if(status & ETHER_EESR0_FR)
   {
      //Disable FR interrupts
      ETHER.EESIPR0 &= ~ETHER_EESIPR0_FRIP;

      //Notify the user that a packet has been received
      flag |= osSetEventFromIsr(&interface->nicRxEvent);
   }

   //Leave interrupt service routine
   osExitIsr(flag);
}


/**
 * @brief RZ/A1 Ethernet MAC event handler
 * @param[in] interface Underlying network interface
 **/

void rza1EthEventHandler(NetInterface *interface)
{
   error_t error;
   size_t length;
   bool_t linkStateChange;

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
         //Set duplex mode for proper operation
         if(interface->linkState)
         {
            //Half-duplex or full-duplex mode?
            if(interface->fullDuplex)
               ETHER.ECMR0 |= ETH_ECMR0_DM;
            else
               ETHER.ECMR0 &= ~ETH_ECMR0_DM;
         }

         //Process link state change event
         nicNotifyLinkChange(interface);
      }
   }

   //Packet received?
   if(ETHER.EESR0 & ETHER_EESR0_FR)
   {
      //Clear FR interrupt flag
      ETHER.EESR0 = ETHER_EESR0_FR;

      //Process all pending packets
      do
      {
         //Read incoming packet
         error = rza1EthReceivePacket(interface,
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

   //Re-enable EDMAC interrupts
   ETHER.EESIPR0 =  ETHER_EESIPR0_TWBIP | ETHER_EESIPR0_FRIP;
}


/**
 * @brief Configure multicast MAC address filtering
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t rza1EthSetMacFilter(NetInterface *interface)
{
   uint_t i;
   volatile uint32_t *addressHigh;
   volatile uint32_t *addressLow;

   //Debug message
   TRACE_INFO("Updating RZ/A1 CAM entry table...\r\n");

   //Disable all CAM entries
   ETHER.TSU_TEN = 0;

   //The MAC filter table contains the multicast MAC addresses
   //to accept when receiving an Ethernet frame
   for(i = 0; i < interface->macFilterSize && i < 32; i++)
   {
      //Point to the current MAC address
      MacAddr *macAddr = &interface->macFilter[i].addr;

      //Debug message
      TRACE_INFO("  %s\r\n", macAddrToString(macAddr, NULL));

      //Point to the CAM entry registers
      addressHigh = &ETHER.TSU_ADRH0 + 2 * i;
      addressLow = &ETHER.TSU_ADRL0 + 2 * i;

      //The contents of the CAM entry table registers cannot be
      //modified while the ADSBSY flag is set
      while(ETHER.TSU_ADSBSY & ETHER_TSU_ADSBSY_ADSBSY);

      //Set the upper 32 bits of the MAC address
      *addressHigh = (macAddr->b[0] << 24) | (macAddr->b[1] << 16) |
         (macAddr->b[2] << 8) | macAddr->b[3];

      //Wait for the ADSBSY flag to be cleared
      while(ETHER.TSU_ADSBSY & ETHER_TSU_ADSBSY_ADSBSY);

      //Set the lower 16 bits of the MAC address
      *addressLow = (macAddr->b[4] << 8) | macAddr->b[5];

      //Enable the CAM entry
      ETHER.TSU_TEN |= 1 << (31 - i);
   }

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

error_t rza1EthSendPacket(NetInterface *interface,
   const NetBuffer *buffer, size_t offset)
{
   //Retrieve the length of the packet
   size_t length = netBufferGetLength(buffer) - offset;

   //Check the frame length
   if(length > RZA1_ETH_TX_BUFFER_SIZE)
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
      //Report an error
      return ERROR_INVALID_LENGTH;
   }

   //Make sure the current buffer is available for writing
   if(txDmaDesc[txIndex].td0 & ETHER_TD0_TACT)
      return ERROR_FAILURE;

   //Copy user data to the transmit buffer
   netBufferRead(txBuffer[txIndex], buffer, offset, length);

   //Write the number of bytes to send
   txDmaDesc[txIndex].td1 = (length << 16) & ETHER_TD1_TDL;

   //Check current index
   if(txIndex < (RZA1_ETH_TX_BUFFER_COUNT - 1))
   {
      //Give the ownership of the descriptor to the DMA engine
      txDmaDesc[txIndex].td0 = ETHER_TD0_TACT | ETHER_TD0_TFP_SOF |
         ETHER_TD0_TFP_EOF | ETHER_TD0_TWBI;

      //Point to the next descriptor
      txIndex++;
   }
   else
   {
      //Give the ownership of the descriptor to the DMA engine
      txDmaDesc[txIndex].td0 = ETHER_TD0_TACT | ETHER_TD0_TDLE |
         ETHER_TD0_TFP_SOF | ETHER_TD0_TFP_EOF | ETHER_TD0_TWBI;

      //Wrap around
      txIndex = 0;
   }

   //Instruct the DMA to poll the transmit descriptor list
   ETHER.EDTRR0 = ETHER_EDTRR0_TR;

   //Check whether the next buffer is available for writing
   if(!(txDmaDesc[txIndex].td0 & ETHER_TD0_TACT))
   {
      //The transmitter can accept another packet
      osSetEvent(&interface->nicTxEvent);
   }

   //Successful write operation
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

error_t rza1EthReceivePacket(NetInterface *interface,
   uint8_t *buffer, size_t size, size_t *length)
{
   error_t error;
   size_t n;

   //The current buffer is available for reading?
   if(!(rxDmaDesc[rxIndex].rd0 & ETHER_RD0_RACT))
   {
      //SOF and EOF flags should be set
      if((rxDmaDesc[rxIndex].rd0 & ETHER_RD0_RFP_SOF) &&
         (rxDmaDesc[rxIndex].rd0 & ETHER_RD0_RFP_EOF))
      {
         //Make sure no error occurred
         if(!(rxDmaDesc[rxIndex].rd0 & (ETHER_RD0_RFS_MASK & ~ETHER_RD0_RFS_RMAF)))
         {
            //Retrieve the length of the frame
            n = rxDmaDesc[rxIndex].rd1 & ETHER_RD1_RDL;
            //Limit the number of data to read
            n = MIN(n, size - 4);

            //Copy data from the receive buffer
            memcpy(buffer, rxBuffer[rxIndex], n);

            //CRC is not included in the transfer...
            buffer[n++] = 0xCC;
            buffer[n++] = 0xCC;
            buffer[n++] = 0xCC;
            buffer[n++] = 0xCC;

            //Total number of bytes that have been received
            *length = n;
            //Packet successfully received
            error = NO_ERROR;
         }
         else
         {
            //The received packet contains an error
            error = ERROR_INVALID_PACKET;
         }
      }
      else
      {
         //The packet is not valid
         error = ERROR_INVALID_PACKET;
      }

      //Check current index
      if(rxIndex < (RZA1_ETH_RX_BUFFER_COUNT - 1))
      {
         //Give the ownership of the descriptor back to the DMA
         rxDmaDesc[rxIndex].rd0 = ETHER_RD0_RACT;
         //Point to the next descriptor
         rxIndex++;
      }
      else
      {
         //Give the ownership of the descriptor back to the DMA
         rxDmaDesc[rxIndex].rd0 = ETHER_RD0_RACT | ETHER_RD0_RDLE;
         //Wrap around
         rxIndex = 0;
      }

      //Instruct the DMA to poll the receive descriptor list
      ETHER.EDRRR0 = ETHER_EDRRR0_RR;
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
 * @brief Write PHY register
 * @param[in] phyAddr PHY address
 * @param[in] regAddr Register address
 * @param[in] data Register value
 **/

void rza1EthWritePhyReg(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
   //Synchronization pattern
   rza1EthWriteSmi(SMI_SYNC, 32);
   //Start of frame
   rza1EthWriteSmi(SMI_START, 2);
   //Set up a write operation
   rza1EthWriteSmi(SMI_WRITE, 2);
   //Write PHY address
   rza1EthWriteSmi(phyAddr, 5);
   //Write register address
   rza1EthWriteSmi(regAddr, 5);
   //Turnaround
   rza1EthWriteSmi(SMI_TA, 2);
   //Write register value
   rza1EthWriteSmi(data, 16);
   //Release MDIO
   rza1EthReadSmi(1);
}


/**
 * @brief Read PHY register
 * @param[in] phyAddr PHY address
 * @param[in] regAddr Register address
 * @return Register value
 **/

uint16_t rza1EthReadPhyReg(uint8_t phyAddr, uint8_t regAddr)
{
   uint16_t data;

   //Synchronization pattern
   rza1EthWriteSmi(SMI_SYNC, 32);
   //Start of frame
   rza1EthWriteSmi(SMI_START, 2);
   //Set up a read operation
   rza1EthWriteSmi(SMI_READ, 2);
   //Write PHY address
   rza1EthWriteSmi(phyAddr, 5);
   //Write register address
   rza1EthWriteSmi(regAddr, 5);
   //Turnaround to avoid contention
   rza1EthReadSmi(1);
   //Read register value
   data = rza1EthReadSmi(16);
   //Force the PHY to release the MDIO pin
   rza1EthReadSmi(1);

   //Return PHY register contents
   return data;
}


/**
 * @brief SMI write operation
 * @param[in] data Raw data to be written
 * @param[in] length Number of bits to be written
 **/

void rza1EthWriteSmi(uint32_t data, uint_t length)
{
   //Skip the most significant bits since they are meaningless
   data <<= 32 - length;

   //Configure MDIO as an output
   ETHER.PIR0 |= ETHER_PIR0_MMD;

   //Write the specified number of bits
   while(length--)
   {
      //Write MDIO
      if(data & 0x80000000)
         ETHER.PIR0 |= ETHER_PIR0_MDO;
      else
         ETHER.PIR0 &= ~ETHER_PIR0_MDO;

      //Assert MDC
      usleep(1);
      ETHER.PIR0 |= ETHER_PIR0_MDC;
      //Deassert MDC
      usleep(1);
      ETHER.PIR0 &= ~ETHER_PIR0_MDC;

      //Rotate data
      data <<= 1;
   }
}


/**
 * @brief SMI read operation
 * @param[in] length Number of bits to be read
 * @return Data resulting from the MDIO read operation
 **/

uint32_t rza1EthReadSmi(uint_t length)
{
   uint32_t data = 0;

   //Configure MDIO as an input
   ETHER.PIR0 &= ~ETHER_PIR0_MMD;

   //Read the specified number of bits
   while(length--)
   {
      //Rotate data
      data <<= 1;

      //Assert MDC
      ETHER.PIR0 |= ETHER_PIR0_MDC;
      usleep(1);
      //Deassert MDC
      ETHER.PIR0 &= ~ETHER_PIR0_MDC;
      usleep(1);

      //Check MDIO state
      if(ETHER.PIR0 & ETHER_PIR0_MDI)
         data |= 0x00000001;
   }

   //Return the received data
   return data;
}
