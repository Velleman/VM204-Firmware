/**
 * @file mdns_responder.c
 * @brief mDNS responder (Multicast DNS)
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
#include <ctype.h>
#include "core/net.h"
#include "mdns/mdns_responder.h"
#include "mdns/mdns_common.h"
#include "dns/dns_debug.h"
#include "dns_sd/dns_sd.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (MDNS_RESPONDER_SUPPORT == ENABLED)


/**
 * @brief mDNS responder initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t mdnsResponderInit(NetInterface *interface)
{
   //Clear mDNS responder context
   memset(&interface->mdnsContext, 0, sizeof(MdnsContext));

   //Initialize state machine
   if(interface->nicDriver->type == NIC_TYPE_ETHERNET)
      interface->mdnsContext.state = MDNS_STATE_INIT;
   else
      interface->mdnsContext.state = MDNS_STATE_DONE;

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief Start probing process
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t mdnsStartProbing(NetInterface *interface)
{
   MdnsContext *context;

   //Point to the mDNS context
   context = &interface->mdnsContext;

   //Reset state machine
   if(interface->nicDriver->type == NIC_TYPE_ETHERNET)
      context->state = MDNS_STATE_INIT;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief mDNS timer handler
 *
 * This routine must be periodically called by the TCP/IP stack to
 * manage mDNS operation
 *
 * @param[in] interface Underlying network interface
 **/

void mdnsTick(NetInterface *interface)
{
   error_t error;
   systime_t time;
   MdnsContext *context;

   //Get current time
   time = osGetSystemTime();
   //Point to the mDNS context
   context = &interface->mdnsContext;

   //Check current state
   if(context->state == MDNS_STATE_INIT)
   {
      //Make sure that the link is up
      if(interface->linkState)
      {
#if (IPV4_SUPPORT == ENABLED)
         //Check whether the IPv4 host address is valid
         if(interface->ipv4Config.addrState == IPV4_ADDR_STATE_VALID)
            context->state = MDNS_STATE_PROBING;
#endif
#if (IPV6_SUPPORT == ENABLED)
         //Check whether the IPv6 link-local address is valid
         if(interface->ipv6Config.linkLocalAddrState == IPV6_ADDR_STATE_PREFERRED)
            context->state = MDNS_STATE_PROBING;
#endif
         //Start probing?
         if(context->state == MDNS_STATE_PROBING)
         {
            //Clear conflict flag
            context->conflict = FALSE;
            //Set time stamp
            context->timestamp = time;
            //Initial random delay
            context->timeout = netGetRandRange(0, MDNS_INIT_DELAY);
            //Reset probe counter
            context->counter = 0;
         }
      }
   }
   else if(context->state == MDNS_STATE_PROBING)
   {
      //Check current time
      if((time - context->timestamp) >= context->timeout)
      {
         //Any conflict detected?
         if(context->conflict)
         {
            //Programmatically change the host name
            error = mdnsGenerateHostname(interface);

            //Failed to change host name?
            if(error)
            {
               //Report an error
               context->state = MDNS_STATE_ERROR;
            }
            else
            {
               //Restart probing
               context->state = MDNS_STATE_INIT;
            }
         }
         //Probing is on-going?
         else if(context->counter < MDNS_PROBE_NUM)
         {
            //Send probe packet
            mdnsSendProbe(interface);

            //Save the time at which the packet was sent
            context->timestamp = time;
            //Time interval between subsequent probe packets
            context->timeout = MDNS_PROBE_DELAY;
            //Increment packet counter
            context->counter++;
         }
         else
         {
            //Set time stamp
            context->timestamp = time;
            //Reset timeout value
            context->timeout = 0;
            //Reset probe counter
            context->counter = 0;

            //Move to the next step (announcing)
            context->state = MDNS_STATE_ANNOUNCING;
         }
      }
   }
   else if(context->state == MDNS_STATE_ANNOUNCING)
   {
      //Check current time
      if((time - context->timestamp) >= context->timeout)
      {
         //Send announcement packet
         mdnsSendAnnouncement(interface);

         //Save the time at which the packet was sent
         context->timestamp = time;
         //Time interval between subsequent announcement packets
         context->timeout = MDNS_ANNOUNCE_DELAY;
         //Increment packet counter
         context->counter++;

         //Announcing is complete?
         if(context->counter >= MDNS_ANNOUNCE_NUM)
         {
            //Probing and announcing steps are complete
            context->state = MDNS_STATE_DONE;
         }
      }
   }
   else if(context->state == MDNS_STATE_DONE)
   {
      if(interface->nicDriver->type == NIC_TYPE_ETHERNET)
      {
         //Any conflict detected?
         if(context->conflict)
         {
            //Programmatically change the host name
            error = mdnsGenerateHostname(interface);

            //Failed to change host name?
            if(error)
            {
               //Report an error
               context->state = MDNS_STATE_ERROR;
            }
            else
            {
               //Restart probing
               context->state = MDNS_STATE_INIT;
            }
         }
      }
   }
}


/**
 * @brief Callback function for link change event
 * @param[in] interface Underlying network interface
 **/

void mdnsLinkChangeEvent(NetInterface *interface)
{
   MdnsContext *context;

   //Point to the mDNS context
   context = &interface->mdnsContext;

   //Whenever a mDNS responder receives an indication of a link
   //change event, it must perform probing and announcing
   if(interface->nicDriver->type == NIC_TYPE_ETHERNET)
      context->state = MDNS_STATE_INIT;
}


/**
 * @brief Process mDNS query message
 * @param[in] interface Underlying network interface
 * @param[in] pseudoHeader UDP pseudo header
 * @param[in] udpHeader UDP header
 * @param[in] query Pointer to the mDNS query message
 * @param[in] queryLen Length of the message
 **/

void mdnsProcessQuery(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
   const UdpHeader *udpHeader, const DnsHeader *query, size_t queryLen)
{
   error_t error;
   uint_t i;
   size_t pos;
   size_t offset;
   size_t responseLen;
   DnsHeader *response;
   NetBuffer *buffer;

   //Check the state of the mDNS responder
   if(interface->mdnsContext.state != MDNS_STATE_DONE)
      return;

   //Initialize error code
   error = NO_ERROR;

   //This buffer will hold the mDNS response, if any
   buffer = NULL;
   //Point to the first question
   pos = sizeof(DnsHeader);

   //Parse question section
   for(i = 0; i < ntohs(query->qdcount); i++)
   {
      size_t n;
      uint16_t qclass;
      uint16_t qtype;
      DnsQuestion *question;

      //Parse domain name
      n = dnsParseName(query, queryLen, pos, NULL, 0);

      //Invalid name?
      if(!n)
         break;
      //Malformed mDNS message?
      if((n + sizeof(DnsQuestion)) > queryLen)
         break;

      //Point to the corresponding entry
      question = DNS_GET_QUESTION(query, n);
      //Convert the query class to host byte order
      qclass = ntohs(question->qclass);
      //Discard QU flag
      qclass &= ~MDNS_QCLASS_QU;
      //Convert the query type to host byte order
      qtype = ntohs(question->qtype);

      //Check the class of the query
      if(qclass == DNS_RR_CLASS_IN || qclass == DNS_RR_CLASS_ANY)
      {
#if (DNS_SD_SUPPORT == ENABLED)
         //PTR query?
         if(qtype == DNS_RR_TYPE_PTR || qtype == DNS_RR_TYPE_ANY)
         {
            uint_t j;

            //Service type enumeration meta-query received?
            if(mdnsCompareName(query, queryLen, pos, "", "_services._dns-sd._udp", ".local", 0))
            {
               //Any registered services?
               if(interface->numServices > 0 && interface->instanceName != NULL)
               {
                  //Create a mDNS response message only if necessary
                  if(!buffer)
                  {
                     //Allocate the mDNS response message
                     buffer = mdnsCreateResponse(query->id, &offset, &response, &responseLen);
                     //Failed to allocate memory?
                     if(!buffer) break;
                  }

                  //Loop through registered services
                  for(j = 0; j < interface->numServices; j++)
                  {
                     //Format PTR resource record
                     error = dnsSdAddPtrResourceRecord(interface,
                        &interface->services[j], TRUE, response, &responseLen);
                     //Any error to report?
                     if(error) break;
                  }

                  //Propagate exception if necessary...
                  if(error) break;
               }
            }
            else
            {
               //Loop through registered services
               for(j = 0; j < interface->numServices; j++)
               {
                  //Compare service name
                  if(mdnsCompareName(query, queryLen, pos, "",
                     interface->services[j].name, ".local", 0))
                  {
                     //The current service name matches a registered service
                     break;
                  }
               }

               //Any matching service name?
               if(j < interface->numServices && interface->instanceName != NULL)
               {
                  //Create a mDNS response message only if necessary
                  if(!buffer)
                  {
                     //Allocate the mDNS response message
                     buffer = mdnsCreateResponse(query->id, &offset, &response, &responseLen);
                     //Failed to allocate memory?
                     if(!buffer) break;
                  }

                  //Format PTR resource record
                  error = dnsSdAddPtrResourceRecord(interface,
                     &interface->services[j], FALSE, response, &responseLen);
                  //Any error to report?
                  if(error) break;

                  //Format TXT resource record
                  error = dnsSdAddTxtResourceRecord(interface,
                     &interface->services[j], response, &responseLen);
                  //Any error to report?
                  if(error) break;

                  //Format SRV resource record
                  error = dnsSdAddSrvResourceRecord(interface,
                     &interface->services[j], response, &responseLen);
                  //Any error to report?
                  if(error) break;

                  //Format A resource record
                  error = mdnsAddIpv4ResourceRecord(interface,
                     response, &responseLen, FALSE);
                  //Any error to report?
                  if(error) break;

                  //Format AAAA resource record
                  error = mdnsAddIpv6ResourceRecord(interface,
                     response, &responseLen, FALSE);
                  //Any error to report?
                  if(error) break;
               }
            }
         }
         //SRV or TXT query?
         else if(qtype == DNS_RR_TYPE_SRV || qtype == DNS_RR_TYPE_TXT)
         {
            uint_t j;

            //Loop through registered services
            for(j = 0; j < interface->numServices; j++)
            {
               //Compare service name
               if(mdnsCompareName(query, queryLen, pos, interface->instanceName,
                  interface->services[j].name, ".local", 0))
               {
                  //The current service name matches a registered service
                  break;
               }
            }

            //Any matching service name?
            if(j < interface->numServices && interface->instanceName != NULL)
            {
               //Create a mDNS response message only if necessary
               if(!buffer)
               {
                  //Allocate the mDNS response message
                  buffer = mdnsCreateResponse(query->id, &offset, &response, &responseLen);
                  //Failed to allocate memory?
                  if(!buffer) break;
               }

               //Check query type?
               if(qtype == DNS_RR_TYPE_TXT)
               {
                  //Format TXT resource record
                  error = dnsSdAddTxtResourceRecord(interface,
                     &interface->services[j], response, &responseLen);
                  //Any error to report?
                  if(error) break;
               }
               else if(qtype == DNS_RR_TYPE_SRV)
               {
                  //Format SRV resource record
                  error = dnsSdAddSrvResourceRecord(interface,
                     &interface->services[j], response, &responseLen);
                  //Any error to report?
                  if(error) break;

                  //Format A resource record
                  error = mdnsAddIpv4ResourceRecord(interface,
                     response, &responseLen, FALSE);
                  //Any error to report?
                  if(error) break;

                  //Format AAAA resource record
                  error = mdnsAddIpv6ResourceRecord(interface,
                     response, &responseLen, FALSE);
                  //Any error to report?
                  if(error) break;
               }
            }
         }
#endif
#if (IPV4_SUPPORT == ENABLED)
         //A query?
#if (DNS_SD_SUPPORT == ENABLED)
         if(qtype == DNS_RR_TYPE_A)
#else
         if(qtype == DNS_RR_TYPE_A || qtype == DNS_RR_TYPE_ANY)
#endif
         {
            //Compare domain name
            if(mdnsCompareName(query, queryLen, pos, interface->hostname, "", ".local", 0))
            {
               //Create a mDNS response message only if necessary
               if(!buffer)
               {
                  //Allocate the mDNS response message
                  buffer = mdnsCreateResponse(query->id, &offset, &response, &responseLen);
                  //Failed to allocate memory?
                  if(!buffer) break;
               }

               //Format A resource record
               error = mdnsAddIpv4ResourceRecord(interface, response, &responseLen, FALSE);
               //Any error to report?
               if(error) break;
            }
         }
#endif
#if (IPV6_SUPPORT == ENABLED)
         //AAAA query?
#if (DNS_SD_SUPPORT == ENABLED)
         if(qtype == DNS_RR_TYPE_AAAA)
#else
         if(qtype == DNS_RR_TYPE_AAAA || qtype == DNS_RR_TYPE_ANY)
#endif
         {
            //Compare domain name
            if(mdnsCompareName(query, queryLen, pos, interface->hostname, "", ".local", 0))
            {
               //Create a mDNS response message only if necessary
               if(!buffer)
               {
                  //Allocate the mDNS response message
                  buffer = mdnsCreateResponse(query->id, &offset, &response, &responseLen);
                  //Failed to allocate memory?
                  if(!buffer) break;
               }

               //Format AAAA resource record
               error = mdnsAddIpv6ResourceRecord(interface, response, &responseLen, FALSE);
               //Any error to report?
               if(error) break;
            }
         }
#endif
      }

      //Point to the next question
      pos = n + sizeof(DnsQuestion);
   }

   //Any response to send?
   if(buffer != NULL)
   {
      //Check status code
      if(!error)
      {
         //Send mDNS response message
         mdnsSendResponse(interface, pseudoHeader, udpHeader,
            buffer, offset, responseLen);
      }

      //Free previously allocated memory
      netBufferFree(buffer);
   }
}


/**
 * @brief Send probe packet
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t mdnsSendProbe(NetInterface *interface)
{
   error_t error;
   size_t length;
   size_t offset;
   NetBuffer *buffer;
   DnsHeader *message;
   DnsQuestion *dnsQuestion;
   IpAddr destIpAddr;

   //Initialize error code
   error = NO_ERROR;

   //Allocate a memory buffer to hold the mDNS query message
   buffer = udpAllocBuffer(DNS_MESSAGE_MAX_SIZE, &offset);
   //Failed to allocate buffer?
   if(!buffer) return ERROR_OUT_OF_MEMORY;

   //Point to the mDNS header
   message = netBufferAt(buffer, offset);

   //Format mDNS query message
   message->id = 0;
   message->qr = 0;
   message->opcode = DNS_OPCODE_QUERY;
   message->aa = 0;
   message->tc = 0;
   message->rd = 0;
   message->ra = 0;
   message->z = 0;
   message->rcode = DNS_RCODE_NO_ERROR;

   //The mDNS query contains one question
   message->qdcount = HTONS(1);
   message->ancount = 0;
   message->nscount = 0;
   message->arcount = 0;

   //Length of the mDNS query message
   length = sizeof(DnsHeader);

   //Encode the host name using the DNS name notation
   length += mdnsEncodeName(interface->hostname, "",
      ".local", (uint8_t *) message + length);

   //Point to the corresponding question structure
   dnsQuestion = DNS_GET_QUESTION(message, length);
   //Fill in question structure
   dnsQuestion->qtype = HTONS(DNS_RR_TYPE_ANY);
   dnsQuestion->qclass = HTONS(DNS_RR_CLASS_IN);

   //Update the length of the mDNS query message
   length += sizeof(DnsQuestion);

   //Adjust the length of the multi-part buffer
   netBufferSetLength(buffer, offset + length);

   //Debug message
   TRACE_INFO("Sending mDNS probe (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump message
   dnsDumpMessage(message, length);

#if (IPV4_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Select the relevant multicast address (224.0.0.251)
      destIpAddr.length = sizeof(Ipv4Addr);
      destIpAddr.ipv4Addr = MDNS_IPV4_MULTICAST_ADDR;

      //All multicast DNS queries should be sent with an IP TTL set to 255
      error = udpSendDatagramEx(interface, MDNS_PORT, &destIpAddr,
         MDNS_PORT, buffer, offset, MDNS_DEFAULT_IP_TTL);
   }
#endif

#if (IPV6_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Select the relevant multicast address (ff02::fb)
      destIpAddr.length = sizeof(Ipv6Addr);
      destIpAddr.ipv6Addr = MDNS_IPV6_MULTICAST_ADDR;

      //All multicast DNS queries should be sent with an IP TTL set to 255
      error = udpSendDatagramEx(interface, MDNS_PORT, &destIpAddr,
         MDNS_PORT, buffer, offset, MDNS_DEFAULT_IP_TTL);
   }
#endif

   //Free previously allocated memory
   netBufferFree(buffer);
   //Return status code
   return error;
}


/**
 * @brief Send announcement packet
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t mdnsSendAnnouncement(NetInterface *interface)
{
   error_t error;
   size_t length;
   size_t offset;
   NetBuffer *buffer;
   DnsHeader *message;
   IpAddr destIpAddr;

   //Initialize error code
   error = NO_ERROR;

   //Allocate a memory buffer to hold the mDNS query message
   buffer = udpAllocBuffer(DNS_MESSAGE_MAX_SIZE, &offset);
   //Failed to allocate buffer?
   if(!buffer) return ERROR_OUT_OF_MEMORY;

   //Point to the mDNS header
   message = netBufferAt(buffer, offset);

   //Format mDNS query message
   message->id = 0;
   message->qr = 1;
   message->opcode = DNS_OPCODE_QUERY;
   message->aa = 1;
   message->tc = 0;
   message->rd = 0;
   message->ra = 0;
   message->z = 0;
   message->rcode = DNS_RCODE_NO_ERROR;

   //Multicast DNS responses must not contain any questions
   message->qdcount = 0;
   message->ancount = 0;
   message->nscount = 0;
   message->arcount = 0;

   //Length of the mDNS query message
   length = sizeof(DnsHeader);

   //Start of exception handling block
   do
   {
      //Format A resource record
      error = mdnsAddIpv4ResourceRecord(interface, message, &length, TRUE);
      //Any error to report?
      if(error) break;

      //Format AAAA resource record
      error = mdnsAddIpv6ResourceRecord(interface, message, &length, TRUE);
      //Any error to report?
      if(error) break;

      //Convert 16-bit value to network byte order
      message->ancount = htons(message->ancount);

      //Adjust the length of the multi-part buffer
      netBufferSetLength(buffer, offset + length);

      //Debug message
      TRACE_INFO("Sending mDNS announcement (%" PRIuSIZE " bytes)...\r\n", length);
      //Dump message
      dnsDumpMessage(message, length);

#if (IPV4_SUPPORT == ENABLED)
      //Select the relevant multicast address (224.0.0.251)
      destIpAddr.length = sizeof(Ipv4Addr);
      destIpAddr.ipv4Addr = MDNS_IPV4_MULTICAST_ADDR;

      //All multicast DNS queries should be sent with an IP TTL set to 255
      error = udpSendDatagramEx(interface, MDNS_PORT, &destIpAddr,
         MDNS_PORT, buffer, offset, MDNS_DEFAULT_IP_TTL);
      //Any error to report?
      if(error)break;
#endif

#if (IPV6_SUPPORT == ENABLED)
      //Select the relevant multicast address (ff02::fb)
      destIpAddr.length = sizeof(Ipv6Addr);
      destIpAddr.ipv6Addr = MDNS_IPV6_MULTICAST_ADDR;

      //All multicast DNS queries should be sent with an IP TTL set to 255
      error = udpSendDatagramEx(interface, MDNS_PORT, &destIpAddr,
         MDNS_PORT, buffer, offset, MDNS_DEFAULT_IP_TTL);
      //Any error to report?
      if(error)break;
#endif

      //End of exception handling block
   } while(0);

   //Free previously allocated memory
   netBufferFree(buffer);
   //Return status code
   return error;
}


/**
 * @brief Create mDNS response message
 * @param[in] id 16-bit identifier
 * @param[out] offset Offset to the first byte of the response
 * @param[out] response Pointer to the response header
 * @param[out] responseLen Actual length of the response
 * @return Pointer the buffer that holds the response message
 * @return Error code
 **/

NetBuffer *mdnsCreateResponse(uint16_t id, size_t *offset,
   DnsHeader **response, size_t *responseLen)
{
   NetBuffer *buffer;
   DnsHeader *header;

   //Allocate a memory buffer to hold the mDNS message
   buffer = udpAllocBuffer(MDNS_MESSAGE_MAX_SIZE, offset);

   //Successful memory allocation?
   if(buffer != NULL)
   {
      //Point to the mDNS response header
      header = netBufferAt(buffer, *offset);

      //Take the identifier from the query message
      header->id = id;

      //Format mDNS response header
      header->qr = 1;
      header->opcode = DNS_OPCODE_QUERY;
      header->aa = 1;
      header->tc = 0;
      header->rd = 0;
      header->ra = 0;
      header->z = 0;
      header->rcode = DNS_RCODE_NO_ERROR;

      //Multicast DNS responses must not contain any questions
      header->qdcount = 0;
      header->ancount = 0;
      header->nscount = 0;
      header->arcount = 0;

      //Pointer to the mDNS response header
      *response = header;
      //Actual length of the mDNS response message
      *responseLen = sizeof(DnsHeader);
   }

   //Return a pointer to the buffer that holds the mDNS message
   return buffer;
}


/**
 * @brief Send mDNS response message
 * @param[in] interface Underlying network interface
 * @param[in] pseudoHeader UDP pseudo header from the query message
 * @param[in] udpHeader UDP header from the query message
 * @param[in] buffer Multi-part buffer containing the response message
 * @param[in] offset Offset to the first byte of the response message
 * @param[in] length Length of the response message
 * @return Error code
 **/

error_t mdnsSendResponse(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
   const UdpHeader *udpHeader, NetBuffer *buffer, size_t offset, size_t length)
{
   uint16_t destPort;
   IpAddr destIpAddr;
   DnsHeader *response;

#if (IPV4_SUPPORT == ENABLED)
   //Check whether the mDNS query was received from an IPv4 peer
   if(pseudoHeader->length == sizeof(Ipv4PseudoHeader))
   {
      //If the source UDP port in a received Multicast DNS query is not port 5353,
      //this indicates that the querier originating the query is a simple resolver
      if(udpHeader->srcPort != HTONS(MDNS_PORT))
      {
         //the mDNS responder must send a UDP response directly back to the querier,
         //via unicast, to the query packet's source IP address and port
         destIpAddr.length = sizeof(Ipv4Addr);
         destIpAddr.ipv4Addr = pseudoHeader->ipv4Data.srcAddr;
      }
      else
      {
         //Use mDNS IPv4 multicast address
         destIpAddr.length = sizeof(Ipv4Addr);
         destIpAddr.ipv4Addr = MDNS_IPV4_MULTICAST_ADDR;
      }
   }
#endif
#if (IPV6_SUPPORT == ENABLED)
   //Check whether the mDNS query was received from an IPv6 peer
   if(pseudoHeader->length == sizeof(Ipv6PseudoHeader))
   {
      //If the source UDP port in a received Multicast DNS query is not port 5353,
      //this indicates that the querier originating the query is a simple resolver
      if(udpHeader->srcPort != HTONS(MDNS_PORT))
      {
         //the mDNS responder must send a UDP response directly back to the querier,
         //via unicast, to the query packet's source IP address and port
         destIpAddr.length = sizeof(Ipv6Addr);
         destIpAddr.ipv6Addr = pseudoHeader->ipv6Data.srcAddr;
      }
      else
      {
         //Use mDNS IPv6 multicast address
         destIpAddr.length = sizeof(Ipv6Addr);
         destIpAddr.ipv6Addr = MDNS_IPV6_MULTICAST_ADDR;
      }
   }
#endif

   //Destination port
   destPort = ntohs(udpHeader->srcPort);

   //Point to the mDNS response header
   response = netBufferAt(buffer, offset);
   //Convert 16-bit value to network byte order
   response->ancount = htons(response->ancount);

   //Adjust the length of the multi-part buffer
   netBufferSetLength(buffer, offset + length);

   //Debug message
   TRACE_INFO("Sending mDNS message (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump message
   dnsDumpMessage(response, length);

   //All multicast DNS responses should be sent with an IP TTL set to 255
   return udpSendDatagramEx(interface, MDNS_PORT, &destIpAddr,
      destPort, buffer, offset, MDNS_DEFAULT_IP_TTL);
}


/**
 * @brief Add A record to a mDNS message
 * @param[in] interface Underlying network interface
 * @param[in,out] message Pointer to the mDNS message
 * @param[in,out] length Actual length of the mDNS message
 * @param[in] flush Cache-flush bit
 * @return Error code
 **/

error_t mdnsAddIpv4ResourceRecord(NetInterface *interface,
   DnsHeader *message, size_t *length, bool_t flush)
{
#if (IPV4_SUPPORT == ENABLED)
   size_t n;
   size_t offset;
   DnsResourceRecord *resourceRecord;

   //Set the position to the end of the buffer
   offset = *length;

   //The first pass calculates the length of the DNS encoded host name
   n = mdnsEncodeName(interface->hostname, "", ".local", NULL);

   //Check the length of the resulting mDNS message
   if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //The second pass encodes the host name using the DNS name notation
   offset += mdnsEncodeName(interface->hostname, "",
      ".local", (uint8_t *) message + offset);

   //Consider the length of the resource record itself
   n = sizeof(DnsResourceRecord) + sizeof(Ipv4Addr);

   //Check the length of the resulting mDNS message
   if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //Point to the corresponding resource record
   resourceRecord = DNS_GET_RESOURCE_RECORD(message, offset);

   //Check whether the cache-fluch bit should be set
   if(flush)
      resourceRecord->rclass = HTONS(MDNS_RCLASS_CACHE_FLUSH | DNS_RR_CLASS_IN);
   else
      resourceRecord->rclass = HTONS(DNS_RR_CLASS_IN);

   //Fill in resource record
   resourceRecord->rtype = HTONS(DNS_RR_TYPE_A);
   resourceRecord->ttl = HTONL(MDNS_DEFAULT_RESOURCE_RECORD_TTL);
   resourceRecord->rdlength = HTONS(sizeof(Ipv4Addr));

   //Copy IPv4 address
   ipv4CopyAddr(resourceRecord->rdata, &interface->ipv4Config.addr);

   //Number of resource records in the answer section
   message->ancount++;

   //Update the length of the mDNS response message
   *length = offset + n;
#endif

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Add AAAA record to a mDNS message
 * @param[in] interface Underlying network interface
 * @param[in,out] message Pointer to the mDNS message
 * @param[in,out] length Actual length of the mDNS message
 * @param[in] flush Cache-flush bit
 * @return Error code
 **/

error_t mdnsAddIpv6ResourceRecord(NetInterface *interface,
   DnsHeader *message, size_t *length, bool_t flush)
{
#if (IPV6_SUPPORT == ENABLED)
   size_t n;
   size_t offset;
   DnsResourceRecord *resourceRecord;

   //Set the position to the end of the buffer
   offset = *length;

   //The first pass calculates the length of the DNS encoded host name
   n = mdnsEncodeName(interface->hostname, "", ".local", NULL);

   //Check the length of the resulting mDNS message
   if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //The second pass encodes the host name using the DNS name notation
   offset += mdnsEncodeName(interface->hostname,
      "", ".local", (uint8_t *) message + offset);

   //Consider the length of the resource record itself
   n = sizeof(DnsResourceRecord) + sizeof(Ipv6Addr);

   //Check the length of the resulting mDNS message
   if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //Point to the corresponding resource record
   resourceRecord = DNS_GET_RESOURCE_RECORD(message, offset);

   //Check whether the cache-fluch bit should be set
   if(flush)
      resourceRecord->rclass = HTONS(MDNS_RCLASS_CACHE_FLUSH | DNS_RR_CLASS_IN);
   else
      resourceRecord->rclass = HTONS(DNS_RR_CLASS_IN);

   //Fill in resource record
   resourceRecord->rtype = HTONS(DNS_RR_TYPE_AAAA);
   resourceRecord->ttl = HTONL(MDNS_DEFAULT_RESOURCE_RECORD_TTL);
   resourceRecord->rdlength = HTONS(sizeof(Ipv6Addr));

   //Copy IPv6 address
   ipv6CopyAddr(resourceRecord->rdata, &interface->ipv6Config.linkLocalAddr);

   //Number of resource records in the answer section
   message->ancount++;

   //Update the length of the mDNS response message
   *length = offset + n;
#endif

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Generate a new host name
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t mdnsGenerateHostname(NetInterface *interface)
{
   size_t i;
   size_t m;
   size_t n;
   uint32_t index;
   char_t s[11];
   char_t hostname[NET_MAX_HOSTNAME_LEN];

   //Copy current host name
   strcpy(hostname, interface->hostname);
   //Retrieve the length of the name
   n = strlen(hostname);

   //Parse the string
   for(i = n; i > 0; i--)
   {
      //Check whether the current character is a digit
      if(!isdigit((uint8_t) hostname[i - 1]))
         break;
   }

   //Any number following the name?
   if(hostname[i] != '\0')
   {
      //Increment the number at the end of the name
      index = atoi(hostname + i) + 1;
   }
   else
   {
      //Append the digit "2" to the name
      index = 2;
   }

   //Convert the number to a string of characters
   m = sprintf(s, "%" PRIu32, index);

   //Add padding if necessary
   while((i + m) < n)
      hostname[i++] = '0';

   //Properly terminate the string
   hostname[i] = '\0';

   //Sanity check
   if((i + m + 1) >= NET_MAX_HOSTNAME_LEN)
   {
      //Report an error
      return ERROR_FAILURE;
   }

   //Programmatically change the host name
   strcat(hostname, s);
   //Update host name
   netSetHostname(interface, hostname);

   //Successful processing
   return NO_ERROR;
}

#endif
