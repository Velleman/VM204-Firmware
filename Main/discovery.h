/**
 * @file echo.h
 * @brief Echo protocol
 *
 * @section License
 *
 * Copyright (C) 2010-2014 Oryx Embedded. All rights reserved.
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
 * @author Oryx Embedded (www.oryx-embedded.com)
 * @version 1.4.2
 **/

#ifndef _DISCOVERY_H
#define _DISCOVERY_H

//Dependencies
#include "net_config.h"
#include "debug.h"
#include "dhcp/dhcp_client.h"
#include "VM204.h"
#include "shared.h"

//Stack size required to run the echo service
#ifndef DISCOVERY_SERVICE_STACK_SIZE
   #define DISCOVERY_SERVICE_STACK_SIZE 200
#elif (DISCOVERY_SERVICE_STACK_SIZE < 1)
   #error DISCOVERY_SERVICE_STACK_SIZE parameter is not valid
#endif

//Priority at which the echo service should run
#ifndef DISCOVERY_SERVICE_PRIORITY
   #define DISCOVERY_SERVICE_PRIORITY 2
#elif (DISCOVERY_SERVICE_PRIORITY < 0)
   #error DISCOVERY_SERVICE_PRIORITY parameter is not valid
#endif

//Size of the buffer for input/output operations
#ifndef DISCOVERY_BUFFER_SIZE
   #define DISCOVERY_BUFFER_SIZE 500
#elif (DISCOVERY_BUFFER_SIZE < 1)
   #error DISCOVERY_BUFFER_SIZE parameter is not valid
#endif

//Maximum time the TCP echo server will wait before closing the connection
#ifndef DISCOVERY_TIMEOUT
   #define DISCOVERY_TIMEOUT 20000
#elif (DISCOVERY_TIMEOUT < 1)
   #error DISCOVERY_TIMEOUT parameter is not valid
#endif

//Echo service port
#define DISCOVERY_PORT 30303


/**
 * @brief Discovery service context
 **/

typedef struct
{
   Socket *socket;
   char_t buffer[DISCOVERY_BUFFER_SIZE];
} DiscoveryServiceContext;


//UDP echo service related functions
error_t udpDiscoveryStart(void);
void udpDiscoveryTask(void *param);
void udpSendDiscovery(DiscoveryServiceContext *context, IpAddr ipAddr, int port);
#endif
