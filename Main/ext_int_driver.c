/**
 * @file ext_int.c
 * @brief External interrupt line driver
 *
 * @section License
 *
 * Copyright (C) 2010-2014 Oryx Embedded. All rights reserved.
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
 * @author Oryx Embedded (www.oryx-embedded.com)
 * @version 1.5.0
 **/

//Dependencies
#include <p32xxxx.h>
#include "core/net.h"
#include "ext_int_driver.h"
#include "debug.h"


/**
 * @brief External interrupt line driver
 **/

const ExtIntDriver extIntDriver =
{
   extIntInit,
   extIntEnableIrq,
   extIntDisableIrq
};


/**
 * @brief EXTI configuration
 * @return Error code
 **/

error_t extIntInit(void)
{
   //Configure edge polarity for INT3 interrupt (falling edge)
   INTCONCLR = _INTCON_INT3EP_MASK;
   //Set interrupt priority
   IPC3CLR = _IPC3_INT3IP_MASK;
   IPC3SET = (2 << _IPC3_INT3IP_POSITION);
   //Set interrupt subpriority
   IPC3CLR = _IPC3_INT3IS_MASK;
   IPC3SET = (0 << _IPC3_INT3IS_POSITION);

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Enable external interrupts
 **/

void extIntEnableIrq(void)
{
   //Enable INT3 interrupt
   IEC0SET = _IEC0_INT3IE_MASK;
}


/**
 * @brief Disable external interrupts
 **/

void extIntDisableIrq(void)
{
   //Disable INT3 interrupt
   IEC0CLR = _IEC0_INT3IE_MASK;
}


/**
 * @brief External interrupt handler
 **/

void extIntHandler(void)
{
   bool_t flag;
   NetInterface *interface;

   //Enter interrupt service routine
   osEnterIsr();

   //Point to the structure describing the network interface
   interface = &netInterface[0];
   //This flag will be set if a higher priority task must be woken
   flag = FALSE;

   //Check interrupt status
   if(IFS0 & _IFS0_INT3IF_MASK)
   {
      //Clear interrupt flag
      IFS0CLR = _IFS0_INT3IF_MASK;
      //A PHY event is pending...
      interface->phyEvent = TRUE;
      //Notify the user that the link state has changed
      flag = osSetEventFromIsr(&interface->nicRxEvent);
   }

   //Leave interrupt service routine
   osExitIsr(flag);
}
