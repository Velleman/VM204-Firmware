/**
 * @file auto_ip.c
 * @brief Auto-IP (Dynamic Configuration of IPv4 Link-Local Addresses)
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
 * @section Description
 *
 * Auto-IP describes a method by which a host may automatically configure an
 * interface with an IPv4 address in the 169.254/16 prefix that is valid for
 * Link-Local communication on that interface. This is especially valuable in
 * environments where no other configuration mechanism is available. Refer to
 * the following RFCs for complete details:
 * - RFC 3927: Dynamic Configuration of IPv4 Link-Local Addresses
 * - RFC 5227: IPv4 Address Conflict Detection
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.6.0
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL AUTO_IP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "core/ethernet.h"
#include "ipv4/arp.h"
#include "ipv4/auto_ip.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (IPV4_SUPPORT == ENABLED && AUTO_IP_SUPPORT == ENABLED)


/**
 * @brief Initialize settings with default values
 * @param[out] settings Structure that contains Auto-IP settings
 **/

void autoIpGetDefaultSettings(AutoIpSettings *settings)
{
   //Use default interface
   settings->interface = NULL;
   //Default link-local address
   settings->linkLocalAddr = IPV4_UNSPECIFIED_ADDR;
}


/**
 * @brief Auto-IP initialization
 * @param[in] context Pointer to the Auto-IP context
 * @param[in] settings Auto-IP specific settings
 * @return Error code
 **/

error_t autoIpInit(AutoIpContext *context, const AutoIpSettings *settings)
{
   NetInterface *interface;

   //Debug message
   TRACE_INFO("Initializing Auto-IP...\r\n");

   //Ensure the parameters are valid
   if(!context || !settings)
      return ERROR_INVALID_PARAMETER;
   //A valid pointer to the interface being configured is required
   if(!settings->interface)
      return ERROR_INVALID_PARAMETER;

   //Point to the underlying network interface
   interface = settings->interface;
   //Clear the Auto-IP context
   memset(context, 0, sizeof(AutoIpContext));

   //Save the network interface to configure
   context->interface = settings->interface;
   //Use default link-local address
   context->linkLocalAddr = settings->linkLocalAddr;

   //Initialize mutex object
   if(!osCreateMutex(&context->mutex))
   {
      //Failed to create mutex
      return ERROR_OUT_OF_RESOURCES;
   }

   //Auto-IP operation is currently suspended
   context->running = FALSE;
   //Initialize state machine
   context->state = AUTO_IP_STATE_INIT;
   //Reset conflict counter
   context->conflictCount = 0;

   //Attach the Auto-IP context to the network interface
   interface->autoIpContext = context;

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief Start Auto-IP process
 * @param[in] context Pointer to the Auto-IP context
 * @return Error code
 **/

error_t autoIpStart(AutoIpContext *context)
{
   //Enter critical section
   osAcquireMutex(&context->mutex);

   //Start Auto-IP operation
   context->running = TRUE;
   //Initialize state machine
   context->state = AUTO_IP_STATE_INIT;
   //Reset conflict counter
   context->conflictCount = 0;

   //Leave critical section
   osReleaseMutex(&context->mutex);

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Stop Auto-IP process
 * @param[in] context Pointer to the Auto-IP context
 * @return Error code
 **/

error_t autoIpStop(AutoIpContext *context)
{
   //Enter critical section
   osAcquireMutex(&context->mutex);

   //Suspend Auto-IP operation
   context->running = FALSE;
   //Reinitialize state machine
   context->state = AUTO_IP_STATE_INIT;

   //Leave critical section
   osReleaseMutex(&context->mutex);

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Retrieve current state
 * @param[in] context Pointer to the Auto-IP context
 * @return Current Auto-IP state
 **/

AutoIpState autoIpGetState(AutoIpContext *context)
{
   AutoIpState state;

   //Enter critical section
   osAcquireMutex(&context->mutex);
   //Get current state
   state = context->state;
   //Leave critical section
   osReleaseMutex(&context->mutex);

   //Return current state
   return state;
}


/**
 * @brief Auto-IP timer handler
 *
 * This routine must be periodically called by the TCP/IP stack to
 * manage Auto-IP operation
 *
 * @param[in] context Pointer to the Auto-IP context
 **/

void autoIpTick(AutoIpContext *context)
{
   systime_t time;

   //Get current time
   time = osGetSystemTime();

   //Enter critical section
   osAcquireMutex(&context->mutex);

   //Check current state
   if(context->state == AUTO_IP_STATE_INIT)
   {
      //Check link state
      if(context->running && context->interface->linkState)
      {
         //Configure subnet mask
         ipv4SetSubnetMask(context->interface, AUTO_IP_SUBNET_MASK);

         //The address must be in the range from 169.54.1.0 to 169.254.254.255
         if(ntohl(context->linkLocalAddr) < ntohl(AUTO_IP_ADDR_MIN) ||
            ntohl(context->linkLocalAddr) > ntohl(AUTO_IP_ADDR_MAX))
         {
            //Generate a random link-local address
            autoIpGenerateAddr(&context->linkLocalAddr);
         }

         //Use the link-local address as a tentative address
         ipv4SetHostAddrEx(context->interface,
            context->linkLocalAddr, IPV4_ADDR_STATE_TENTATIVE);

         //Set time stamp
         context->timestamp = time;
         //Initial random delay
         context->timeout = netGetRandRange(0, AUTO_IP_PROBE_WAIT);
         //Reset retransmission counter
         context->retransmitCount = 0;

         //The number of conflicts exceeds the maximum acceptable value?
         if(context->conflictCount >= AUTO_IP_MAX_CONFLICTS)
         {
            //The host must limit the rate at which it probes for new addresses
            context->timeout += AUTO_IP_RATE_LIMIT_INTERVAL;
         }

         //Verify the uniqueness of the link-local address
         context->state = AUTO_IP_STATE_PROBING;
      }
   }
   else if(context->state == AUTO_IP_STATE_PROBING)
   {
      //Check current time
      if((time - context->timestamp) >= context->timeout)
      {
         //Address Conflict Detection failed?
         if(context->interface->ipv4Config.addrConflict)
         {
            //The address is already in use by some other host and
            //must not be assigned to the interface
            ipv4SetHostAddrEx(context->interface,
               IPV4_UNSPECIFIED_ADDR, IPV4_ADDR_STATE_INVALID);

            //The host should maintain a counter of the number of address
            //conflicts it has experienced
            context->conflictCount++;

            //The host must select a new pseudo-random address...
            autoIpGenerateAddr(&context->linkLocalAddr);
            //...and repeat the process
            context->state = AUTO_IP_STATE_INIT;
         }
         //Address Conflict Detection is on-going?
         else if(context->retransmitCount < AUTO_IP_PROBE_NUM)
         {
            //Conflict detection is done using ARP probes
            arpSendRequest(context->interface, IPV4_UNSPECIFIED_ADDR,
               context->linkLocalAddr, &MAC_BROADCAST_ADDR);

            //Save the time at which the packet was sent
            context->timestamp = time;
            //Increment retransmission counter
            context->retransmitCount++;

            //Last probe packet sent?
            if(context->retransmitCount == AUTO_IP_PROBE_NUM)
            {
               //Delay before announcing
               context->timeout = AUTO_IP_ANNOUNCE_WAIT;
            }
            else
            {
               //Maximum delay till repeated probe
               context->timeout = netGetRandRange(AUTO_IP_PROBE_MIN,
                  AUTO_IP_PROBE_MAX);
            }
         }
         //Address Conflict Detection is complete?
         else
         {
            //The use of the IPv4 address is now unrestricted
            ipv4SetHostAddrEx(context->interface,
               context->linkLocalAddr, IPV4_ADDR_STATE_VALID);

            //Set time stamp
            context->timestamp = time;
            //Reset timeout value
            context->timeout = 0;
            //Reset retransmission counter
            context->retransmitCount = 0;

            //The host must then announce its claimed address
            context->state = AUTO_IP_STATE_ANNOUNCING;
         }
      }
   }
   else if(context->state == AUTO_IP_STATE_ANNOUNCING)
   {
      //Check current time
      if((time - context->timestamp) >= context->timeout)
      {
         //An ARP announcement is identical to an ARP probe, except that
         //now the sender and target IP addresses are both set to the
         //host's newly selected IPv4 address
         arpSendRequest(context->interface, context->linkLocalAddr,
            context->linkLocalAddr, &MAC_BROADCAST_ADDR);

         //Save the time at which the packet was sent
         context->timestamp = time;
         //Time between announcement packets
         context->timeout = AUTO_IP_ANNOUNCE_INTERVAL;
         //Increment retransmission counter
         context->retransmitCount++;

         //Announcing is complete?
         if(context->retransmitCount >= AUTO_IP_ANNOUNCE_NUM)
         {
            //Successful address autoconfiguration
            context->state = AUTO_IP_STATE_CONFIGURED;
            //Reset conflict counter
            context->conflictCount = 0;

            //Dump current IPv4 configuration for debugging purpose
            autoIpDumpConfig(context);
         }
      }
   }
   else if(context->state == AUTO_IP_STATE_CONFIGURED)
   {
      //Upon receiving a conflicting ARP packet, a host may elect to
      //immediately configure a new IPv4 link-local address
      if(context->interface->ipv4Config.addrConflict)
      {
         //The link-local address cannot be used anymore
         ipv4SetHostAddrEx(context->interface,
            IPV4_UNSPECIFIED_ADDR, IPV4_ADDR_STATE_INVALID);

         //The host must select a new pseudo-random address...
         autoIpGenerateAddr(&context->linkLocalAddr);
         //...and force address reconfiguration
         context->state = AUTO_IP_STATE_INIT;
      }
   }

   //Leave critical section
   osReleaseMutex(&context->mutex);
}


/**
 * @brief Callback function for link change event
 * @param[in] context Pointer to the Auto-IP context
 **/

void autoIpLinkChangeEvent(AutoIpContext *context)
{
   //Enter critical section
   osAcquireMutex(&context->mutex);

   //Check whether Auto-IP is enabled
   if(context->running)
   {
      //The host address is not longer valid
      ipv4SetHostAddrEx(context->interface,
         IPV4_UNSPECIFIED_ADDR, IPV4_ADDR_STATE_INVALID);

      //Clear subnet mask
      ipv4SetSubnetMask(context->interface, IPV4_UNSPECIFIED_ADDR);
   }

   //Reinitialize state machine
   context->state = AUTO_IP_STATE_INIT;
   //Reset conflict counter
   context->conflictCount = 0;

   //Leave critical section
   osReleaseMutex(&context->mutex);
}


/**
 * @brief Dump Auto-IP configuration for debugging purpose
 * @param[in] context Pointer to the Auto-IP context
 **/

void autoIpDumpConfig(AutoIpContext *context)
{
   Ipv4Addr ipv4Addr;

   //Debug message
   TRACE_INFO("\r\nAuto-IP configuration:\r\n");

   //Link-local address
   ipv4GetHostAddr(context->interface, &ipv4Addr);
   TRACE_INFO("  Link-local Address = %s\r\n", ipv4AddrToString(ipv4Addr, NULL));

   //Subnet mask
   ipv4GetSubnetMask(context->interface, &ipv4Addr);
   TRACE_INFO("  Subnet Mask = %s\r\n", ipv4AddrToString(ipv4Addr, NULL));
}


/**
 * @brief Generate a random link-local address
 * @param[out] ipAddr Random link-local address
 **/

void autoIpGenerateAddr(Ipv4Addr *ipAddr)
{
   uint32_t n;

   //Generate a random address in the range from 169.254.1.0 to 169.254.254.255
   n = netGetRand() % ntohl(AUTO_IP_ADDR_MAX - AUTO_IP_ADDR_MIN);
   n += ntohl(AUTO_IP_ADDR_MIN);

   //Convert the resulting address to network byte order
   *ipAddr = htonl(n);
}

#endif
