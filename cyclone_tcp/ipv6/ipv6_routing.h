/**
 * @file ipv6_routing.h
 * @brief IPv6 routing
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

#ifndef _IPV6_ROUTING_H
#define _IPV6_ROUTING_H

//Dependencies
#include "core/net.h"
#include "ipv6/ipv6.h"

//IPv6 routing support
#ifndef IPV6_ROUTING_SUPPORT
   #define IPV6_ROUTING_SUPPORT DISABLED
#elif (IPV6_ROUTING_SUPPORT != ENABLED && IPV6_ROUTING_SUPPORT != DISABLED)
   #error IPV6_ROUTING_SUPPORT parameter is not valid
#endif

//Size of the IPv6 routing table
#ifndef IPV6_ROUTING_TABLE_SIZE
   #define IPV6_ROUTING_TABLE_SIZE 8
#elif (IPV6_ROUTING_TABLE_SIZE < 1)
   #error IPV6_ROUTING_TABLE_SIZE parameter is not valid
#endif


/**
 * @brief Routing table entry
 **/

typedef struct
{
   Ipv6Addr prefix;         ///<Destination
   uint_t prefixLength;     ///<IPv6 prefix length
   NetInterface *interface; ///<Outgoing network interface
   Ipv6Addr nextHop;        ///<Next hop
} Ipv6RoutingTableEntry;


//IPv6 routing related functions
error_t ipv6InitRoutingTable(void);
error_t ipv6ClearRoutingTable(void);

error_t ipv6AddRoute(const Ipv6Addr *prefix, uint_t prefixLength,
   NetInterface *interface, const Ipv6Addr *nextHop);

error_t ipv6ForwardPacket(NetInterface *srcInterface,
   NetBuffer *srcBuffer, size_t srcOffset);

#endif
