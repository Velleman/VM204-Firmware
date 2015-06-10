/**
 * @file dm9161.c
 * @brief DM9161 Ethernet PHY transceiver
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
#include "drivers/dm9161.h"
#include "debug.h"


/**
 * @brief DM9161 Ethernet PHY driver
 **/

const PhyDriver dm9161PhyDriver =
{
   dm9161Init,
   dm9161Tick,
   dm9161EnableIrq,
   dm9161DisableIrq,
   dm9161EventHandler,
};


/**
 * @brief DM9161 PHY transceiver initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t dm9161Init(NetInterface *interface)
{
   volatile uint32_t status;

   //Debug message
   TRACE_INFO("Initializing DM9161...\r\n");

   //Initialize external interrupt line driver
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->init();

   //Reset PHY transceiver
   dm9161WritePhyReg(interface, DM9161_PHY_REG_BMCR, BMCR_RESET);
   //Wait for the reset to complete
   while(dm9161ReadPhyReg(interface, DM9161_PHY_REG_BMCR) & BMCR_RESET);

   //Dump PHY registers for debugging purpose
   dm9161DumpPhyReg(interface);

   //The PHY will generate interrupts when link status changes are detected
   dm9161WritePhyReg(interface, DM9161_PHY_REG_MDINTR, ~(MDINTR_LINK_MASK | MDINTR_INTR_MASK));

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief DM9161 timer handler
 * @param[in] interface Underlying network interface
 **/

void dm9161Tick(NetInterface *interface)
{
   //No external interrupt line driver?
   if(interface->extIntDriver == NULL)
   {
      uint16_t value;
      bool_t linkState;

      //Read basic status register
      value = dm9161ReadPhyReg(interface, DM9161_PHY_REG_BMSR);
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

void dm9161EnableIrq(NetInterface *interface)
{
   //Enable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->enableIrq();
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void dm9161DisableIrq(NetInterface *interface)
{
   //Disable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->disableIrq();
}


/**
 * @brief DM9161 event handler
 * @param[in] interface Underlying network interface
 * @return TRUE if a link state change notification is received
 **/

bool_t dm9161EventHandler(NetInterface *interface)
{
   uint16_t value;
   bool_t end;

   //Read status register to acknowledge the interrupt
   value = dm9161ReadPhyReg(interface, DM9161_PHY_REG_MDINTR);

   //Link status change?
   if(value & MDINTR_LINK_CHANGE)
   {
      //Any link failure condition is latched in the BMSR register...
      //Reading the register twice always return the actual link status
      value = dm9161ReadPhyReg(interface, DM9161_PHY_REG_BMSR);
      value = dm9161ReadPhyReg(interface, DM9161_PHY_REG_BMSR);

      //Link is up?
      if(value & BMSR_LINK_STATUS)
      {
         //Wait for the auto-negotiation to complete
         do
         {
            //Read DSCSR register
            value = dm9161ReadPhyReg(interface, DM9161_PHY_REG_DSCSR);

            //Check current state
            switch(value & DSCSR_ANMB_MASK)
            {
            //Auto-negotiation is still in progress?
            case DSCSR_ANMB_ABILITY_MATCH:
            case DSCSR_ANMB_ACK_MATCH:
            case DSCSR_ANMB_CONSIST_MATCH:
            case DSCSR_ANMB_SIGNAL_LINK_READY:
               end = FALSE;
               break;
            //Auto-negotiation is complete?
            default:
               end = TRUE;
               break;
            }

            //Check loop condition variable
         } while(!end);

         //Read DSCSR register
         value = dm9161ReadPhyReg(interface, DM9161_PHY_REG_DSCSR);

         //Check current operation mode
         if(value & DSCSR_10HDX)
         {
            //10BASE-T half-duplex
            interface->speed100 = FALSE;
            interface->fullDuplex = FALSE;
         }
         else if(value & DSCSR_10FDX)
         {
            //10BASE-T full-duplex
            interface->speed100 = FALSE;
            interface->fullDuplex = TRUE;
         }
         else if(value & DSCSR_100HDX)
         {
            //100BASE-TX half-duplex
            interface->speed100 = TRUE;
            interface->fullDuplex = FALSE;
         }
         else if(value & DSCSR_100FDX)
         {
            //100BASE-TX full-duplex
            interface->speed100 = TRUE;
            interface->fullDuplex = TRUE;
         }
         else
         {
            //Debug message
            TRACE_WARNING("Invalid Duplex mode\r\n");
         }

         //Update link state
         interface->linkState = TRUE;
         //Display link state
         TRACE_INFO("Link is up (%s)...\r\n", interface->name);

         //Display actual speed and duplex mode
         TRACE_INFO("%s %s\r\n",
            interface->speed100 ? "100BASE-TX" : "10BASE-T",
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

void dm9161WritePhyReg(NetInterface *interface, uint8_t address, uint16_t data)
{
   //Write the specified PHY register
   interface->nicDriver->writePhyReg(DM9161_PHY_ADDR, address, data);
}


/**
 * @brief Read PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address PHY register address
 * @return Register value
 **/

uint16_t dm9161ReadPhyReg(NetInterface *interface, uint8_t address)
{
   //Read the specified PHY register
   return interface->nicDriver->readPhyReg(DM9161_PHY_ADDR, address);
}


/**
 * @brief Dump PHY registers for debugging purpose
 * @param[in] interface Underlying network interface
 **/

void dm9161DumpPhyReg(NetInterface *interface)
{
   uint8_t i;

   //Loop through PHY registers
   for(i = 0; i < 32; i++)
   {
      //Display current PHY register
      TRACE_DEBUG("%02" PRIu8 ": 0x%04" PRIX16 "\r\n", i, dm9161ReadPhyReg(interface, i));
   }

   //Terminate with a line feed
   TRACE_DEBUG("\r\n");
}
