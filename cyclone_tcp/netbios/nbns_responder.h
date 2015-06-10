/**
 * @file nbns_responder.h
 * @brief NBNS responder (NetBIOS Name Service)
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

#ifndef _NBNS_RESPONDER_H
#define _NBNS_RESPONDER_H

//Dependencies
#include "core/net.h"
#include "core/udp.h"
#include "dns/dns_common.h"
#include "netbios/nbns_common.h"

//NBNS responder support
#ifndef NBNS_RESPONDER_SUPPORT
   #define NBNS_RESPONDER_SUPPORT ENABLED
#elif (NBNS_RESPONDER_SUPPORT != ENABLED && NBNS_RESPONDER_SUPPORT != DISABLED)
   #error NBNS_RESPONDER_SUPPORT parameter is not valid
#endif

//NBNS related functions
void nbnsProcessQuery(NetInterface *interface, const Ipv4PseudoHeader *pseudoHeader,
   const UdpHeader *udpHeader, const NbnsHeader *message, size_t length);

error_t nbnsSendResponse(NetInterface *interface,
   const IpAddr *destIpAddr, uint16_t destPort, uint16_t id);

#endif
