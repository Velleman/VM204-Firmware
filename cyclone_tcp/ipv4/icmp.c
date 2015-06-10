/**
 * @file icmp.c
 * @brief ICMP (Internet Control Message Protocol)
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
#define TRACE_LEVEL ICMP_TRACE_LEVEL

//Dependencies
#include <string.h>
#include "core/net.h"
#include "core/ip.h"
#include "ipv4/ipv4.h"
#include "ipv4/icmp.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (IPV4_SUPPORT == ENABLED)


/**
 * @brief Incoming ICMP message processing
 * @param[in] interface Underlying network interface
 * @param[in] srcIpAddr Source IPv4 address
 * @param[in] buffer Multi-part buffer containing the incoming ICMP message
 * @param[in] offset Offset to the first byte of the ICMP message
 **/

void icmpProcessMessage(NetInterface *interface,
   Ipv4Addr srcIpAddr, const NetBuffer *buffer, size_t offset)
{
   size_t length;
   IcmpHeader *header;

   //Retrieve the length of the ICMP message
   length = netBufferGetLength(buffer) - offset;

   //Ensure the message length is correct
   if(length < sizeof(IcmpHeader))
   {
      //Debug message
      TRACE_WARNING("ICMP message length is invalid!\r\n");
      //Silently discard incoming message
      return;
   }

   //Point to the ICMP message header
   header = netBufferAt(buffer, offset);
   //Sanity check
   if(!header) return;

   //Debug message
   TRACE_INFO("ICMP message received (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump message contents for debugging purpose
   icmpDumpMessage(header);

   //Verify checksum value
   if(ipCalcChecksumEx(buffer, offset, length) != 0x0000)
   {
      //Debug message
      TRACE_WARNING("Wrong ICMP header checksum!\r\n");
      //Drop incoming message
      return;
   }

   //Check the type of ICMP message
   switch(header->type)
   {
   //Echo request?
   case ICMP_TYPE_ECHO_REQUEST:
      //Process Echo Request message
      icmpProcessEchoRequest(interface, srcIpAddr, buffer, offset);
      break;
   //Unknown type?
   default:
      //Debug message
      TRACE_WARNING("Unknown ICMP message type!\r\n");
      //Discard incoming ICMP message
      break;
   }
}


/**
 * @brief Echo Request message processing
 * @param[in] interface Underlying network interface
 * @param[in] srcIpAddr Source IPv4 address
 * @param[in] request Multi-part buffer containing the incoming Echo Request message
 * @param[in] requestOffset Offset to the first byte of the Echo Request message
 **/

void icmpProcessEchoRequest(NetInterface *interface,
   Ipv4Addr srcIpAddr, const NetBuffer *request, size_t requestOffset)
{
   error_t error;
   size_t requestLength;
   size_t replyOffset;
   size_t replyLength;
   NetBuffer *reply;
   IcmpEchoMessage *requestHeader;
   IcmpEchoMessage *replyHeader;
   Ipv4PseudoHeader pseudoHeader;

   //Retrieve the length of the Echo Request message
   requestLength = netBufferGetLength(request) - requestOffset;

   //Ensure the packet length is correct
   if(requestLength < sizeof(IcmpEchoMessage))
      return;

   //Point to the Echo Request header
   requestHeader = netBufferAt(request, requestOffset);
   //Sanity check
   if(!requestHeader) return;

   //Debug message
   TRACE_INFO("ICMP Echo Request message received (%" PRIuSIZE " bytes)...\r\n", requestLength);
   //Dump message contents for debugging purpose
   icmpDumpEchoMessage(requestHeader);

   //Allocate memory to hold the Echo Reply message
   reply = ipAllocBuffer(sizeof(IcmpEchoMessage), &replyOffset);
   //Failed to allocate memory?
   if(!reply) return;

   //Point to the Echo Reply header
   replyHeader = netBufferAt(reply, replyOffset);

   //Format Echo Reply header
   replyHeader->type = ICMP_TYPE_ECHO_REPLY;
   replyHeader->code = 0;
   replyHeader->checksum = 0;
   replyHeader->identifier = requestHeader->identifier;
   replyHeader->sequenceNumber = requestHeader->sequenceNumber;

   //Point to the first data byte
   requestOffset += sizeof(IcmpEchoMessage);
   requestLength -= sizeof(IcmpEchoMessage);

   //Copy data
   error = netBufferConcat(reply, request, requestOffset, requestLength);
   //Any error to report?
   if(error)
   {
      //Clean up side effects
      netBufferFree(reply);
      //Exit immediately
      return;
   }

   //Get the length of the resulting message
   replyLength = netBufferGetLength(reply) - replyOffset;
   //Calculate ICMP header checksum
   replyHeader->checksum = ipCalcChecksumEx(reply, replyOffset, replyLength);

   //Format IPv4 pseudo header
   pseudoHeader.srcAddr = interface->ipv4Config.addr;
   pseudoHeader.destAddr = srcIpAddr;
   pseudoHeader.reserved = 0;
   pseudoHeader.protocol = IPV4_PROTOCOL_ICMP;
   pseudoHeader.length = htons(replyLength);

   //Debug message
   TRACE_INFO("Sending ICMP Echo Reply message (%" PRIuSIZE " bytes)...\r\n", replyLength);
   //Dump message contents for debugging purpose
   icmpDumpEchoMessage(replyHeader);

   //Send Echo Reply message
   ipv4SendDatagram(interface, &pseudoHeader, reply, replyOffset, IPV4_DEFAULT_TTL);

   //Free previously allocated memory block
   netBufferFree(reply);
}


/**
 * @brief Send an ICMP Error message
 * @param[in] interface Underlying network interface
 * @param[in] type Message type
 * @param[in] code Specific message code
 * @param[in] parameter Specific message parameter
 * @param[in] ipPacket Multi-part buffer that holds the invoking IPv4 packet
 * @return Error code
 **/

error_t icmpSendErrorMessage(NetInterface *interface, uint8_t type,
   uint8_t code, uint8_t parameter, const NetBuffer *ipPacket)
{
   error_t error;
   size_t offset;
   size_t length;
   Ipv4Header *ipHeader;
   NetBuffer *icmpMessage;
   IcmpErrorMessage *icmpHeader;
   Ipv4PseudoHeader pseudoHeader;

   //Retrieve the length of the invoking IPv4 packet
   length = netBufferGetLength(ipPacket);

   //Check the length of the IPv4 packet
   if(length < sizeof(Ipv4Header))
      return ERROR_INVALID_LENGTH;

   //Point to the header of the invoking packet
   ipHeader = netBufferAt(ipPacket, 0);
   //Sanity check
   if(!ipHeader) return ERROR_FAILURE;

   //Never respond to a packet destined to a broadcast or a multicast address
   if(ipv4IsBroadcastAddr(interface, ipHeader->destAddr) ||
      ipv4IsMulticastAddr(ipHeader->destAddr))
   {
      //Report an error
      return ERROR_INVALID_ADDRESS;
   }

   //Length of the data that will be returned along with the ICMP header
   length = MIN(length, ipHeader->headerLength * 4 + 8);

   //Allocate a memory buffer to hold the ICMP message
   icmpMessage = ipAllocBuffer(sizeof(IcmpErrorMessage), &offset);
   //Failed to allocate memory?
   if(!icmpMessage) return ERROR_OUT_OF_MEMORY;

   //Point to the ICMP header
   icmpHeader = netBufferAt(icmpMessage, offset);

   //Format ICMP message
   icmpHeader->type = type;
   icmpHeader->code = code;
   icmpHeader->checksum = 0;
   icmpHeader->parameter = parameter;
   icmpHeader->unused = 0;

   //Copy the IP header and the first 8 bytes of the original datagram data
   error = netBufferConcat(icmpMessage, ipPacket, 0, length);
   //Any error to report?
   if(error)
   {
      //Clean up side effects
      netBufferFree(icmpMessage);
      //Exit immediately
      return error;
   }

   //Get the length of the resulting message
   length = netBufferGetLength(icmpMessage) - offset;
   //Message checksum calculation
   icmpHeader->checksum = ipCalcChecksumEx(icmpMessage, offset, length);

   //Format IPv4 pseudo header
   pseudoHeader.srcAddr = ipHeader->destAddr;
   pseudoHeader.destAddr = ipHeader->srcAddr;
   pseudoHeader.reserved = 0;
   pseudoHeader.protocol = IPV4_PROTOCOL_ICMP;
   pseudoHeader.length = htons(length);

   //Debug message
   TRACE_INFO("Sending ICMP Error message (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump message contents for debugging purpose
   icmpDumpErrorMessage(icmpHeader);

   //Send ICMP Error message
   error = ipv4SendDatagram(interface, &pseudoHeader,
      icmpMessage, offset, IPV4_DEFAULT_TTL);

   //Free previously allocated memory
   netBufferFree(icmpMessage);
   //Return status code
   return error;
}


/**
 * @brief Dump ICMP message for debugging purpose
 * @param[in] message Pointer to the ICMP message
 **/

void icmpDumpMessage(const IcmpHeader *message)
{
   //Dump ICMP message
   TRACE_DEBUG("  Type = %" PRIu8 "\r\n", message->type);
   TRACE_DEBUG("  Code = %" PRIu8 "\r\n", message->code);
   TRACE_DEBUG("  Checksum = 0x%04" PRIX16 "\r\n", ntohs(message->checksum));
}


/**
 * @brief Dump ICMP Echo Request of Echo Reply message
 * @param[in] message Pointer to the ICMP message
 **/

void icmpDumpEchoMessage(const IcmpEchoMessage *message)
{
   //Dump ICMP message
   TRACE_DEBUG("  Type = %" PRIu8 "\r\n", message->type);
   TRACE_DEBUG("  Code = %" PRIu8 "\r\n", message->code);
   TRACE_DEBUG("  Checksum = 0x%04" PRIX16 "\r\n", ntohs(message->checksum));
   TRACE_DEBUG("  Identifier = 0x%04" PRIX16 "\r\n", ntohs(message->identifier));
   TRACE_DEBUG("  Sequence Number = 0x%04" PRIX16 "\r\n", ntohs(message->sequenceNumber));
}


/**
 * @brief Dump generic ICMP Error message
 * @param[in] message Pointer to the ICMP message
 **/

void icmpDumpErrorMessage(const IcmpErrorMessage *message)
{
   //Dump ICMP message
   TRACE_DEBUG("  Type = %" PRIu8 "\r\n", message->type);
   TRACE_DEBUG("  Code = %" PRIu8 "\r\n", message->code);
   TRACE_DEBUG("  Checksum = 0x%04" PRIX16 "\r\n", ntohs(message->checksum));
   TRACE_DEBUG("  Parameter = %" PRIu8 "\r\n", message->parameter);
}

#endif
