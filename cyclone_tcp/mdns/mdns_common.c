/**
 * @file mdns_common.c
 * @brief Functions common to mDNS client and mDNS responder
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
#define TRACE_LEVEL MDNS_TRACE_LEVEL

//Dependencies
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "core/net.h"
#include "mdns/mdns_client.h"
#include "mdns/mdns_responder.h"
#include "mdns/mdns_common.h"
#include "dns/dns_debug.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (MDNS_CLIENT_SUPPORT == ENABLED || MDNS_RESPONDER_SUPPORT == ENABLED)

#if (IPV6_SUPPORT == ENABLED)

//mDNS IPv6 multicast group (ff02::fb)
const Ipv6Addr MDNS_IPV6_MULTICAST_ADDR =
   IPV6_ADDR(0xFF02, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00FB);

#endif


/**
 * @brief mDNS related initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t mdnsInit(NetInterface *interface)
{
   error_t error;

#if (MDNS_RESPONDER_SUPPORT == ENABLED)
   //Initialize mDNS responder
   error = mdnsResponderInit(interface);
   //Any error to report?
   if(error) return error;
#endif

#if (IPV4_SUPPORT == ENABLED)
   //Join the mDNS IPv4 multicast group
   error = ipv4JoinMulticastGroup(interface, MDNS_IPV4_MULTICAST_ADDR);
   //Any error to report?
   if(error) return error;
#endif

#if (IPV6_SUPPORT == ENABLED)
   //Join the mDNS IPv6 multicast group
   error = ipv6JoinMulticastGroup(interface, &MDNS_IPV6_MULTICAST_ADDR);
   //Any error to report?
   if(error) return error;
#endif

   //Callback function to be called when a mDNS message is received
   error = udpAttachRxCallback(interface, MDNS_PORT, mdnsProcessMessage, NULL);
   //Any error to report?
   if(error) return error;

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief Process incoming mDNS message
 * @param[in] interface Underlying network interface
 * @param[in] pseudoHeader UDP pseudo header
 * @param[in] udpHeader UDP header
 * @param[in] buffer Multi-part buffer containing the incoming mDNS message
 * @param[in] offset Offset to the first byte of the mDNS message
 * @param[in] params Callback function parameter (not used)
 **/

void mdnsProcessMessage(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
   const UdpHeader *udpHeader, const NetBuffer *buffer, size_t offset, void *params)
{
   size_t length;
   DnsHeader *message;

   //Retrieve the length of the mDNS message
   length = netBufferGetLength(buffer) - offset;

   //Ensure the mDNS message is valid
   if(length < sizeof(DnsHeader))
      return;
   if(length > MDNS_MESSAGE_MAX_SIZE)
      return;

   //Point to the mDNS message header
   message = netBufferAt(buffer, offset);
   //Sanity check
   if(!message) return;

   //Debug message
   TRACE_INFO("mDNS message received (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump message
   dnsDumpMessage(message, length);

   //mDNS messages received with an opcode other than zero must be silently ignored
   if(message->opcode != DNS_OPCODE_QUERY)
      return;
   //mDNS messages received with non-zero response codes must be silently ignored
   if(message->rcode != DNS_RCODE_NO_ERROR)
      return;

   //mDNS query received?
   if(!message->qr)
   {
#if (MDNS_RESPONDER_SUPPORT == ENABLED)
      //Process incoming mDNS query message
      mdnsProcessQuery(interface, pseudoHeader, udpHeader, message, length);
#endif
   }
   //mDNS response received?
   else
   {
#if (MDNS_CLIENT_SUPPORT == ENABLED)
      //Process incoming mDNS response message
      mdnsProcessResponse(interface, pseudoHeader, udpHeader, message, length);
#endif
   }
}


/**
 * @brief Encode instance, service and domain names using the DNS name notation
 * @param[in] instance Instance name
 * @param[in] service Service name
 * @param[in] domain Domain name
 * @param[out] dest Pointer to the encoded name (optional parameter)
 * @return Length of the encoded domain name
 **/

size_t mdnsEncodeName(const char_t *instance, const char_t *service,
   const char_t *domain, uint8_t *dest)
{
   size_t n;
   size_t length;

   //Total length of the encoded name
   length = 0;

   //Any instance name?
   if(*instance != '\0')
   {
      //Encode instance name
      n = dnsEncodeName(instance, dest);

      //Failed to encode instance name?
      if(!n)
         return 0;

      //Update the length of the encoded name
      length += n;
   }

   //Any service name?
   if(*service != '\0')
   {
      //If an instance name precedes the service name, then
      //remove the null label
      if(length > 0)
         length--;

      //Encode service name
      if(dest != NULL)
         n = dnsEncodeName(service, dest + length);
      else
         n = dnsEncodeName(service, NULL);

      //Failed to encode instance name?
      if(!n)
         return 0;

      //Update the length of the encoded name
      length += n;
   }

   //Skip the separator that may precede the domain name
   if(*domain == '.')
      domain++;

   //Any domain name to encode?
   if(*domain != '\0')
   {
      //If an instance or a service name precedes the domain name, then
      //remove the null label
      if(length > 0)
         length--;

      //Encode domain name
      if(dest != NULL)
         n = dnsEncodeName(domain, dest + length);
      else
         n = dnsEncodeName(domain, NULL);

      //Failed to encode instance name?
      if(!n)
         return 0;

      //Update the length of the encoded name
      length += n;
   }

   //Return the length of the encoded string
   return length;
}


/**
 * @brief Compare instance, service and domain names
 * @param[in] message Pointer to the DNS message
 * @param[in] length Length of the DNS message
 * @param[in] pos Offset of the encoded name
 * @param[in] instance Instance name
 * @param[in] service Service name
 * @param[in] domain Domain name
 * @param[in] level Current level of recursion
 * @return TRUE if the domain names match, else FALSE
 **/

bool_t mdnsCompareName(const DnsHeader *message, size_t length, size_t pos,
   const char_t *instance, const char_t *service, const char_t *domain, uint_t level)
{
   size_t n;
   size_t pointer;
   uint8_t *src;

   //Check parameters
   if(instance == NULL || service == NULL || domain == NULL)
      return FALSE;

   //Recursion limit exceeded?
   if(level >= DNS_NAME_MAX_RECURSION)
      return FALSE;

   //Cast the input DNS message to byte array
   src = (uint8_t *) message;

   //Skip the separator that may precede the domain name
   if(*domain == '.')
      domain++;

   //Parse encoded domain name
   while(pos < length)
   {
      //End marker found?
      if(src[pos] == 0)
      {
         //Return comparison result
         if(*instance == '\0' && *service == '\0' && *domain == '\0')
            return TRUE;
         else
            return FALSE;
      }
      //Compression tag found?
      if(src[pos] >= DNS_COMPRESSION_TAG)
      {
         //Malformed DNS message?
         if((pos + 1) >= length)
            return FALSE;

         //Read the most significant byte of the pointer
         pointer = (src[pos] & ~DNS_COMPRESSION_TAG) << 8;
         //Read the least significant byte of the pointer
         pointer |= src[pos + 1];

         //Compare the remaining part of the domain name
         return mdnsCompareName(message, length, pointer,
            instance, service, domain, level + 1);
      }
      //Valid label length?
      else if(src[pos] < DNS_LABEL_MAX_SIZE)
      {
         //Get the length of the current label
         n = src[pos++];

         //Malformed DNS message?
         if((pos + n) > length)
            return FALSE;

         //Compare current label
         if(*instance != '\0')
         {
            //Compare instance name
            if(strncasecmp((char_t *) src + pos, instance, n))
               return FALSE;

            //Advance data pointer
            instance += n;

            //Any separator in instance name?
            if(*instance == '.')
               instance++;
         }
         else if(*service != '\0')
         {
            //Compare service name
            if(strncasecmp((char_t *) src + pos, service, n))
               return FALSE;

            //Advance data pointer
            service += n;

            //Any separator in service name?
            if(*service == '.')
               service++;
         }
         else
         {
            //Compare domain name
            if(strncasecmp((char_t *) src + pos, domain, n))
               return FALSE;

            //Advance data pointer
            domain += n;

            //Any separator in domain name?
            if(*domain == '.')
               domain++;
         }

         //Advance data pointer
         pos += n;
      }
      //Invalid label length?
      else
      {
         //Comparison failed
         return FALSE;
      }
   }

   //Comparison failed
   return FALSE;
}

#endif
