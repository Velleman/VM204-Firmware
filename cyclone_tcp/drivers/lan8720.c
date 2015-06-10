/**
 * @file lan8720.c
 * @brief LAN8720 Ethernet PHY transceiver
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
#include "drivers/lan8720.h"
#include "debug.h"


/**
 * @brief LAN8720 Ethernet PHY driver
 **/

const PhyDriver lan8720PhyDriver =
{
   lan8720Init,
   lan8720Tick,
   lan8720EnableIrq,
   lan8720DisableIrq,
   lan8720EventHandler,
};


/**
 * @brief LAN8720 PHY transceiver initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t lan8720Init(NetInterface *interface)
{
   //Debug message
   TRACE_INFO("Initializing LAN8720...\r\n");

   //Reset PHY transceiver (soft reset)
   lan8720WritePhyReg(interface, LAN8720_PHY_REG_BMCR, BMCR_RESET);
   //Wait for the reset to complete
   while(lan8720ReadPhyReg(interface, LAN8720_PHY_REG_BMCR) & BMCR_RESET);

   //Dump PHY registers for debugging purpose
   lan8720DumpPhyReg(interface);

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief LAN8720 timer handler
 * @param[in] interface Underlying network interface
 **/

void lan8720Tick(NetInterface *interface)
{
   uint16_t value;
   bool_t linkState;

   //Read basic status register
   value = lan8720ReadPhyReg(interface, LAN8720_PHY_REG_BMSR);
   //Retrieve current link state
   linkState = (value & BMSR_LINK_STATUS) ? TRUE : FALSE;

   //Link up event?
   if(linkState && !interface->linkState)
   {
      //A PHY event is pending...
      interface->phyEvent = TRUE;
      //Notify the user that the link state has changed
      osSetEvent(&interface->nicRxEvent);
   }
   //Link down event?
   else if(!linkState && interface->linkState)
   {
      //A PHY event is pending...
      interface->phyEvent = TRUE;
      //Notify the user that the link state has changed
      osSetEvent(&interface->nicRxEvent);
   }
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void lan8720EnableIrq(NetInterface *interface)
{
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void lan8720DisableIrq(NetInterface *interface)
{
}


/**
 * @brief LAN8720 event handler
 * @param[in] interface Underlying network interface
 * @return TRUE if a link state change notification is received
 **/

bool_t lan8720EventHandler(NetInterface *interface)
{
   uint16_t value;
   bool_t linkState;

   //Read basic status register
   value = lan8720ReadPhyReg(interface, LAN8720_PHY_REG_BMSR);
   //Retrieve current link state
   linkState = (value & BMSR_LINK_STATUS) ? TRUE : FALSE;

   //Link is up?
   if(linkState && !interface->linkState)
   {
      //Read PHY special control/status register
      value = lan8720ReadPhyReg(interface, LAN8720_PHY_REG_PSCSR);

      //Check current operation mode
      switch(value & PSCSR_HCDSPEED_MASK)
      {
      //10BASE-T
      case PSCSR_HCDSPEED_10BT:
         interface->speed100 = FALSE;
         interface->fullDuplex = FALSE;
         break;
      //10BASE-T full-duplex
      case PSCSR_HCDSPEED_10BT_FD:
         interface->speed100 = FALSE;
         interface->fullDuplex = TRUE;
         break;
      //100BASE-TX
      case PSCSR_HCDSPEED_100BTX:
         interface->speed100 = TRUE;
         interface->fullDuplex = FALSE;
         break;
      //100BASE-TX full-duplex
      case PSCSR_HCDSPEED_100BTX_FD:
         interface->speed100 = TRUE;
         interface->fullDuplex = TRUE;
         break;
      //Unknown operation mode
      default:
         //Debug message
         TRACE_WARNING("Invalid Duplex mode\r\n");
         break;
      }

      //Update link state
      interface->linkState = TRUE;
      //Display link state
      TRACE_INFO("Link is up (%s)...\r\n", interface->name);

      //Display actual speed and duplex mode
      TRACE_INFO("%s %s\r\n",
         interface->speed100 ? "100BASE-TX" : "10BASE-T",
         interface->fullDuplex ? "Full-Duplex" : "Half-Duplex");

      //Notify the user that the link state has changed
      return TRUE;
   }
   //Link is down?
   else if(!linkState && interface->linkState)
   {
      //Update link state
      interface->linkState = FALSE;
      //Display link state
      TRACE_INFO("Link is down (%s)...\r\n", interface->name);

      //Notify the user that the link state has changed
      return TRUE;
   }
   else
   {
      //No link state change...
      return FALSE;
   }
}


/**
 * @brief Write PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address Register address
 * @param[in] data Register value
 **/

void lan8720WritePhyReg(NetInterface *interface, uint8_t address, uint16_t data)
{
   //Write the specified PHY register
   interface->nicDriver->writePhyReg(LAN8720_PHY_ADDR, address, data);
}


/**
 * @brief Read PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address PHY register address
 * @return Register value
 **/

uint16_t lan8720ReadPhyReg(NetInterface *interface, uint8_t address)
{
   //Read the specified PHY register
   return interface->nicDriver->readPhyReg(LAN8720_PHY_ADDR, address);
}


/**
 * @brief Dump PHY registers for debugging purpose
 * @param[in] interface Underlying network interface
 **/

void lan8720DumpPhyReg(NetInterface *interface)
{
   uint8_t i;

   //Loop through PHY registers
   for(i = 0; i < 32; i++)
   {
      //Display current PHY register
      TRACE_DEBUG("%02" PRIu8 ": 0x%04" PRIX16 "\r\n", i, lan8720ReadPhyReg(interface, i));
   }

   //Terminate with a line feed
   TRACE_DEBUG("\r\n");
}
