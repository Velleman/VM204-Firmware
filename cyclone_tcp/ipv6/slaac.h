/**
 * @file slaac.h
 * @brief IPv6 Stateless Address Autoconfiguration
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

#ifndef _SLAAC_H
#define _SLAAC_H

//Dependencies
#include "core/net.h"
#include "ipv6/ndp.h"

//SLAAC support
#ifndef SLAAC_SUPPORT
   #define SLAAC_SUPPORT ENABLED
#elif (SLAAC_SUPPORT != ENABLED && SLAAC_SUPPORT != DISABLED)
   #error SLAAC_SUPPORT parameter is not valid
#endif

//SLAAC tick interval
#ifndef SLAAC_TICK_INTERVAL
   #define SLAAC_TICK_INTERVAL 200
#elif (SLAAC_TICK_INTERVAL < 100)
   #error SLAAC_TICK_INTERVAL parameter is not valid
#endif


/**
 * @brief SLAAC FSM states
 **/

typedef enum
{
   SLAAC_STATE_INIT,
   SLAAC_STATE_LINK_LOCAL_ADDR_DAD,
   SLAAC_STATE_ROUTER_SOLICIT,
   SLAAC_STATE_GLOBAL_ADDR_DAD,
   SLAAC_STATE_CONFIGURED,
   SLAAC_STATE_ERROR
} SlaacState;


/**
 * @brief SLAAC settings
 **/

typedef struct
{
   NetInterface *interface; ///<Network interface to configure
   bool_t manualDnsConfig;  ///<Force manual DNS configuration
} SlaacSettings;


/**
 * @brief SLAAC context
 **/

typedef struct
{
   NetInterface *interface; ///<Underlying network interface
   bool_t manualDnsConfig;  ///<Force manual DNS configuration
   OsMutex mutex;           ///<Mutex preventing simultaneous access to SLAAC functions
   bool_t running;          ///<SLAAC is currently running
   SlaacState state;        ///<Current state of the FSM
   systime_t timestamp;     ///<Timestamp to manage retransmissions
   systime_t timeout;       ///<Timeout value
   uint_t retransmitCount;  ///<Retransmission counter
} SlaacContext;


//Win32 compiler?
#if defined(_WIN32)
   #pragma pack(push, 1)
#endif


/**
 * @brief IPv6 modified EUI-64 identifier
 **/

typedef __start_packed struct
{
   __start_packed union
   {
      uint8_t b[8];
      uint16_t w[4];
      uint32_t dw[2];
   };
} __end_packed Eui64;


//Win32 compiler?
#if defined(_WIN32)
   #pragma pack(pop)
#endif


//SLAAC related functions
void slaacGetDefaultSettings(SlaacSettings *settings);
error_t slaacInit(SlaacContext *context, const SlaacSettings *settings);
error_t slaacStart(SlaacContext *context);
error_t slaacStop(SlaacContext *context);
SlaacState slaacGetState(SlaacContext *context);

void slaacTick(SlaacContext *context);
void slaacLinkChangeEvent(SlaacContext *context);

void slaacProcessRouterAdv(SlaacContext *context,
   const Ipv6Addr *srcAddr, NdpRouterAdvMessage *message, size_t length);

void slaacDumpConfig(SlaacContext *context);

void macAddrToEui64(const MacAddr *macAddr, Eui64 *interfaceId);

#endif
