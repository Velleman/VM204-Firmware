/**
 * @file auto_ip.h
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
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.6.0
 **/

#ifndef _AUTO_IP_H
#define _AUTO_IP_H

//Dependencies
#include "core/net.h"

//Auto-IP support
#ifndef AUTO_IP_SUPPORT
   #define AUTO_IP_SUPPORT DISABLED
#elif (AUTO_IP_SUPPORT != ENABLED && AUTO_IP_SUPPORT != DISABLED)
   #error AUTO_IP_SUPPORT parameter is not valid
#endif

//Auto-IP tick interval
#ifndef AUTO_IP_TICK_INTERVAL
   #define AUTO_IP_TICK_INTERVAL 200
#elif (AUTO_IP_TICK_INTERVAL < 100)
   #error AUTO_IP_TICK_INTERVAL parameter is not valid
#endif

//Initial random delay
#ifndef AUTO_IP_PROBE_WAIT
   #define AUTO_IP_PROBE_WAIT 1000
#elif (AUTO_IP_PROBE_WAIT < 0)
   #error AUTO_IP_PROBE_WAIT parameter is not valid
#endif

//Number of probe packets
#ifndef AUTO_IP_PROBE_NUM
   #define AUTO_IP_PROBE_NUM 3
#elif (AUTO_IP_PROBE_NUM < 1)
   #error AUTO_IP_PROBE_NUM parameter is not valid
#endif

//Minimum delay till repeated probe
#ifndef AUTO_IP_PROBE_MIN
   #define AUTO_IP_PROBE_MIN 1000
#elif (AUTO_IP_PROBE_MIN < 100)
   #error AUTO_IP_PROBE_MIN parameter is not valid
#endif

//Maximum delay till repeated probe
#ifndef AUTO_IP_PROBE_MAX
   #define AUTO_IP_PROBE_MAX 2000
#elif (AUTO_IP_PROBE_MAX < AUTO_IP_PROBE_MIN)
   #error AUTO_IP_PROBE_MAX parameter is not valid
#endif

//Delay before announcing
#ifndef AUTO_IP_ANNOUNCE_WAIT
   #define AUTO_IP_ANNOUNCE_WAIT 2000
#elif (AUTO_IP_ANNOUNCE_WAIT < 100)
   #error AUTO_IP_ANNOUNCE_WAIT parameter is not valid
#endif

//Number of announcement packets
#ifndef AUTO_IP_ANNOUNCE_NUM
   #define AUTO_IP_ANNOUNCE_NUM 2
#elif (AUTO_IP_ANNOUNCE_NUM < 1)
   #error AUTO_IP_ANNOUNCE_NUM parameter is not valid
#endif

//Time between announcement packets
#ifndef AUTO_IP_ANNOUNCE_INTERVAL
   #define AUTO_IP_ANNOUNCE_INTERVAL 2000
#elif (AUTO_IP_ANNOUNCE_INTERVAL < 100)
   #error AUTO_IP_ANNOUNCE_INTERVAL parameter is not valid
#endif

//Max conflicts before rate limiting
#ifndef AUTO_IP_MAX_CONFLICTS
   #define AUTO_IP_MAX_CONFLICTS 10
#elif (AUTO_IP_MAX_CONFLICTS < 1)
   #error AUTO_IP_MAX_CONFLICTS parameter is not valid
#endif

//Delay between successive attempts
#ifndef AUTO_IP_RATE_LIMIT_INTERVAL
   #define AUTO_IP_RATE_LIMIT_INTERVAL 60000
#elif (AUTO_IP_RATE_LIMIT_INTERVAL < 1000)
   #error AUTO_IP_RATE_LIMIT_INTERVAL parameter is not valid
#endif

//Minimum interval between defensive
#ifndef AUTO_IP_DEFEND_INTERVAL
   #define AUTO_IP_DEFEND_INTERVAL 10000
#elif (AUTO_IP_DEFEND_INTERVAL < 1000)
   #error AUTO_IP_DEFEND_INTERVAL parameter is not valid
#endif

//Auto-IP address prefix
#define AUTO_IP_ADDR_PREFIX IPV4_ADDR(169,254,0,0)
//Auto-IP subnet mask
#define AUTO_IP_SUBNET_MASK IPV4_ADDR(255,255,0,0)

//Auto-IP address range
#define AUTO_IP_ADDR_MIN IPV4_ADDR(169,254,1,0)
#define AUTO_IP_ADDR_MAX IPV4_ADDR(169,254,254,255)


/**
 * @brief Auto-IP FSM states
 **/

typedef enum
{
   AUTO_IP_STATE_INIT,
   AUTO_IP_STATE_PROBING,
   AUTO_IP_STATE_ANNOUNCING,
   AUTO_IP_STATE_CONFIGURED,
   AUTO_IP_STATE_ERROR
} AutoIpState;


/**
 * @brief Auto-IP settings
 **/

typedef struct
{
   NetInterface *interface; ///<Network interface to configure
   Ipv4Addr linkLocalAddr;  ///<Default link-local address
} AutoIpSettings;


/**
 * @brief Auto-IP context
 **/

typedef struct
{
   NetInterface *interface; ///<Underlying network interface
   Ipv4Addr linkLocalAddr;  ///<Link-local address
   OsMutex mutex;           ///<Mutex preventing simultaneous access to Auto-IP functions
   bool_t running;          ///<Auto-IP is currently running
   AutoIpState state;       ///<Current state of the FSM
   uint_t conflictCount;    ///<Number of conflicts
   systime_t timestamp;     ///<Timestamp to manage retransmissions
   systime_t timeout;       ///<Timeout value
   uint_t retransmitCount;  ///<Retransmission counter
} AutoIpContext;


//Auto-IP related functions
void autoIpGetDefaultSettings(AutoIpSettings *settings);
error_t autoIpInit(AutoIpContext *context, const AutoIpSettings *settings);
error_t autoIpStart(AutoIpContext *context);
error_t autoIpStop(AutoIpContext *context);
AutoIpState autoIpGetState(AutoIpContext *context);

void autoIpTick(AutoIpContext *context);
void autoIpLinkChangeEvent(AutoIpContext *context);

void autoIpGenerateAddr(Ipv4Addr *ipAddr);

void autoIpDumpConfig(AutoIpContext *context);

#endif
