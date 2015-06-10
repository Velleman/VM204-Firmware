/**
 * @file mdns_responder.h
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

#ifndef _MDNS_RESPONDER_H
#define _MDNS_RESPONDER_H

//Dependencies
#include "core/net.h"
#include "core/udp.h"
#include "dns/dns_common.h"

//mDNS responder support
#ifndef MDNS_RESPONDER_SUPPORT
   #define MDNS_RESPONDER_SUPPORT ENABLED
#elif (MDNS_RESPONDER_SUPPORT != ENABLED && MDNS_RESPONDER_SUPPORT != DISABLED)
   #error MDNS_RESPONDER_SUPPORT parameter is not valid
#endif

//mDNS responder tick interval
#ifndef MDNS_TICK_INTERVAL
   #define MDNS_TICK_INTERVAL 250
#elif (MDNS_TICK_INTERVAL < 100)
   #error MDNS_TICK_INTERVAL parameter is not valid
#endif

//Initial random delay
#ifndef MDNS_INIT_DELAY
   #define MDNS_INIT_DELAY 250
#elif (MDNS_INIT_DELAY < 0)
   #error MDNS_INIT_DELAY parameter is not valid
#endif

//Number of probe packets
#ifndef MDNS_PROBE_NUM
   #define MDNS_PROBE_NUM 3
#elif (MDNS_PROBE_NUM < 1)
   #error MDNS_PROBE_NUM parameter is not valid
#endif

//Time interval between subsequent probe packets
#ifndef MDNS_PROBE_DELAY
   #define MDNS_PROBE_DELAY 250
#elif (MDNS_PROBE_DELAY < 100)
   #error MDNS_PROBE_DELAY parameter is not valid
#endif

//Number of announcement packets
#ifndef MDNS_ANNOUNCE_NUM
   #define MDNS_ANNOUNCE_NUM 2
#elif (MDNS_ANNOUNCE_NUM < 1)
   #error MDNS_ANNOUNCE_NUM parameter is not valid
#endif

//Time interval between subsequent announcement packets
#ifndef MDNS_ANNOUNCE_DELAY
   #define MDNS_ANNOUNCE_DELAY 1000
#elif (MDNS_ANNOUNCE_DELAY < 100)
   #error MDNS_ANNOUNCE_DELAY parameter is not valid
#endif


/**
 * @brief mDNS responder states
 **/

typedef enum
{
   MDNS_STATE_INIT,
   MDNS_STATE_PROBING,
   MDNS_STATE_ANNOUNCING,
   MDNS_STATE_DONE,
   MDNS_STATE_ERROR
} MdnsState;


/**
 * @brief mDNS responder context
 **/

typedef struct
{
   MdnsState state;     ///<mDNS responder state
   bool_t conflict;     ///<Conflict detected
   systime_t timestamp; ///<Timestamp to manage retransmissions
   systime_t timeout;   ///<Timeout value
   uint_t counter;      ///<Packet counter
} MdnsContext;


//mDNS related functions
error_t mdnsResponderInit(NetInterface *interface);
error_t mdnsStartProbing(NetInterface *interface);
void mdnsTick(NetInterface *interface);
void mdnsLinkChangeEvent(NetInterface *interface);

void mdnsProcessQuery(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
   const UdpHeader *udpHeader, const DnsHeader *query, size_t queryLen);

error_t mdnsSendProbe(NetInterface *interface);
error_t mdnsSendAnnouncement(NetInterface *interface);

NetBuffer *mdnsCreateResponse(uint16_t id, size_t *offset,
   DnsHeader **response, size_t *responseLen);

error_t mdnsSendResponse(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
   const UdpHeader *udpHeader, NetBuffer *buffer, size_t offset, size_t length);

error_t mdnsAddIpv4ResourceRecord(NetInterface *interface,
   DnsHeader *message, size_t *length, bool_t flush);

error_t mdnsAddIpv6ResourceRecord(NetInterface *interface,
   DnsHeader *message, size_t *length, bool_t flush);

error_t mdnsGenerateHostname(NetInterface *interface);

#endif
