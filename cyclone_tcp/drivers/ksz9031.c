/**
 * @file ksz9031.c
 * @brief KSZ9031 Gigabit Ethernet PHY transceiver
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
#include "drivers/ksz9031.h"
#include "debug.h"


/**
 * @brief KSZ9031 Ethernet PHY driver
 **/

const PhyDriver ksz9031PhyDriver =
{
   ksz9031Init,
   ksz9031Tick,
   ksz9031EnableIrq,
   ksz9031DisableIrq,
   ksz9031EventHandler,
};


/**
 * @brief KSZ9031 PHY transceiver initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t ksz9031Init(NetInterface *interface)
{
   //Debug message
   TRACE_INFO("Initializing KSZ9031...\r\n");

   //Initialize external interrupt line driver
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->init();

   //Reset PHY transceiver
   ksz9031WritePhyReg(interface, KSZ9031_PHY_REG_BMCR, BMCR_RESET);
   //Wait for the reset to complete
   while(ksz9031ReadPhyReg(interface, KSZ9031_PHY_REG_BMCR) & BMCR_RESET);

   //Dump PHY registers for debugging purpose
   ksz9031DumpPhyReg(interface);

   //The PHY will generate interrupts when link status changes are detected
   ksz9031WritePhyReg(interface, KSZ9031_PHY_REG_ICSR, ICSR_LINK_DOWN_IE | ICSR_LINK_UP_IE);

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief KSZ9031 timer handler
 * @param[in] interface Underlying network interface
 **/

void ksz9031Tick(NetInterface *interface)
{
   //No external interrupt line driver?
   if(interface->extIntDriver == NULL)
   {
      uint16_t value;
      bool_t linkState;

      //Read basic status register
      value = ksz9031ReadPhyReg(interface, KSZ9031_PHY_REG_BMSR);
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
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void ksz9031EnableIrq(NetInterface *interface)
{
   //Enable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->enableIrq();
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void ksz9031DisableIrq(NetInterface *interface)
{
   //Disable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->disableIrq();
}


/**
 * @brief KSZ9031 event handler
 * @param[in] interface Underlying network interface
 * @return TRUE if a link state change notification is received
 **/

bool_t ksz9031EventHandler(NetInterface *interface)
{
   uint16_t value;

   //Read status register to acknowledge the interrupt
   value = ksz9031ReadPhyReg(interface, KSZ9031_PHY_REG_ICSR);

   //Link status change?
   if(value & (ICSR_LINK_DOWN_IF | ICSR_LINK_UP_IF))
   {
      //Read basic status register
      value = ksz9031ReadPhyReg(interface, KSZ9031_PHY_REG_BMSR);

      //Link is up?
      if(value & BMSR_LINK_STATUS)
      {
         //Read PHY control register
         value = ksz9031ReadPhyReg(interface, KSZ9031_PHY_REG_PHYCON);

         //Check current speed
         if(value & PHYCON_SPEED_1000BT)
         {
            //1000BASE-T
            interface->speed100 = FALSE;
            interface->speed1000 = TRUE;
         }
         else if(value & PHYCON_SPEED_100BTX)
         {
            //100BASE-TX
            interface->speed100 = TRUE;
            interface->speed1000 = FALSE;
         }
         else if(value & PHYCON_SPEED_10BT)
         {
            //10BASE-T
            interface->speed100 = FALSE;
            interface->speed1000 = FALSE;
         }
         else
         {
            //Debug message
            TRACE_WARNING("Invalid speed!\r\n");
         }

         //Check current duplex mode
         if(value & PHYCON_DUPLEX_STATUS)
            interface->fullDuplex = TRUE;
         else
            interface->fullDuplex = FALSE;

         //Update link state
         interface->linkState = TRUE;
         //Display link state
         TRACE_INFO("Link is up (%s)...\r\n", interface->name);

         //Display actual speed and duplex mode
         TRACE_INFO("%s %s\r\n",
            interface->speed1000 ? "1000BASE-T" : (interface->speed100 ? "100BASE-TX" : "10BASE-T"),
            interface->fullDuplex ? "Full-Duplex" : "Half-Duplex");
      }
      else
      {
         //Update link state
         interface->linkState = FALSE;
         //Display link state
         TRACE_INFO("Link is down (%s)...\r\n", interface->name);
      }

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

void ksz9031WritePhyReg(NetInterface *interface, uint8_t address, uint16_t data)
{
   //Write the specified PHY register
   interface->nicDriver->writePhyReg(KSZ9031_PHY_ADDR, address, data);
}


/**
 * @brief Read PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address PHY register address
 * @return Register value
 **/

uint16_t ksz9031ReadPhyReg(NetInterface *interface, uint8_t address)
{
   //Read the specified PHY register
   return interface->nicDriver->readPhyReg(KSZ9031_PHY_ADDR, address);
}


/**
 * @brief Dump PHY registers for debugging purpose
 * @param[in] interface Underlying network interface
 **/

void ksz9031DumpPhyReg(NetInterface *interface)
{
   uint8_t i;

   //Loop through PHY registers
   for(i = 0; i < 32; i++)
   {
      //Display current PHY register
      TRACE_DEBUG("%02" PRIu8 ": 0x%04" PRIX16 "\r\n", i, ksz9031ReadPhyReg(interface, i));
   }

   //Terminate with a line feed
   TRACE_DEBUG("\r\n");
}
