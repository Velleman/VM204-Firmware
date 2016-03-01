/**
 * @file Discovery.c
 * @brief Discovery protocol
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
 * @section Description
 *
 * The Discovery service simply sends back to the originating source
 * any data it receives. Refer to RFC 862 for complete details
 *
 * @author Oryx Embedded (www.oryx-embedded.com)
 * @version 1.4.2
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL STD_SERVICES_TRACE_LEVEL

//Dependencies
#include "discovery.h"

//Check TCP/IP stack configuration
#if (TCP_IP_STATIC_OS_RESOURCES == ENABLED)

//UDP Discovery service
static OsTask udpDiscoveryTaskStruct;
static uint_t udpDiscoveryTaskStack[Discovery_SERVICE_STACK_SIZE];

#endif

/**
 * @brief Start UDP Discovery service
 * @return Error code
 **/

error_t udpDiscoveryStart(void) {
    error_t error;
    DiscoveryServiceContext *context;

#if (TCP_IP_STATIC_OS_RESOURCES == DISABLED)
    OsTask *task;
#endif

    //Debug message
    TRACE_INFO("Starting UDP Discovery service...\r\n");

    //Allocate a memory block to hold the context
    context = osAllocMem(sizeof (DiscoveryServiceContext));
    //Failed to allocate memory?
    if (!context) return ERROR_OUT_OF_MEMORY;

    //Start of exception handling block
    do {
        //Open a UDP socket
        context->socket = socketOpen(SOCKET_TYPE_DGRAM, SOCKET_PROTOCOL_UDP);

        //Failed to open socket?
        if (!context->socket) {
            //Report an error
            error = ERROR_OPEN_FAILED;
            //Exit immediately
            break;
        }

        //The server listens for incoming datagrams on port 30303
        error = socketBind(context->socket, &IP_ADDR_ANY, DISCOVERY_PORT);
        //Unable to bind the socket to the desired port?
        if (error) break;

#if (TCP_IP_STATIC_OS_RESOURCES == ENABLED)
        //Create a task to handle incoming datagrams
        osTaskCreateStatic(&udpDiscoveryTaskStruct, "UDP Discovery", udpDiscoveryTask, context,
                udpDiscoveryTaskStack, Discovery_SERVICE_STACK_SIZE, Discovery_SERVICE_PRIORITY);
#else
        //Create a task to handle incoming datagrams
        task = osCreateTask("UDP Discovery", udpDiscoveryTask,
                context, DISCOVERY_SERVICE_STACK_SIZE, DISCOVERY_SERVICE_PRIORITY);

        //Unable to create the task?
        if (task == OS_INVALID_HANDLE) {
            //Report an error to the calling function
            error = ERROR_OUT_OF_RESOURCES;
            break;
        }
#endif

        //End of exception handling block
    } while (0);

    //Any error to report?
    if (error) {
        //Clean up side effects...
        socketClose(context->socket);
        osFreeMem(context);
    }

    //Return status code
    return error;
}

/**
 * @brief UDP Discovery service implementation
 * @param[in] param Pointer to the Discovery service context
 **/
int diff;

error_t error;

void udpDiscoveryTask(void *param) {
    //error_t error;
    size_t length;
    uint16_t port;
    IpAddr ipAddr;
    DiscoveryServiceContext *discoveryContext;

    int n = 0;
    //Get a pointer to the context
    discoveryContext = (DiscoveryServiceContext *) param;

    port = 30303;
    while (tcpIpStackGetDefaultInterface()->ipv4Config.addr == 0 || !netGetLinkState(tcpIpStackGetDefaultInterface())) {
        osDelayTask(100);
    }
    TRACE_INFO("SEND DISCOVERY\r\n");
    ipAddr.length = sizeof (Ipv4Addr);
    ipAddr.ipv4Addr = IPV4_BROADCAST_ADDR;
    udpSendDiscovery(discoveryContext, ipAddr, 30303);


    //Main loop
    while (1) {


        //Wait for an incoming datagram
        error = socketReceiveFrom(discoveryContext->socket, &ipAddr, &port,
                discoveryContext->buffer, DISCOVERY_BUFFER_SIZE, &length, 0);

        //Any datagram received?
        if (!error) {
            diff = strcmp("VM204,Knock Knock\r\n", discoveryContext->buffer);
            if (diff == 0) {
                ipAddr.ipv4Addr = IPV4_BROADCAST_ADDR;
                udpSendDiscovery(discoveryContext, ipAddr, 30303);
                memset(discoveryContext->buffer, 0, arraysize (discoveryContext->buffer));
            } else {
                memset(discoveryContext->buffer, 0, arraysize (discoveryContext->buffer));
            }
        }
        osDelayTask(500);
    }
}

void udpSendDiscovery(DiscoveryServiceContext *dcontext, IpAddr ipAddr, int port) {
    error_t error;
    NetInterface* interface;
    interface = tcpIpStackGetDefaultInterface();
    char buffer[33];
    memset(buffer, 0, arraysize(buffer));
    itoa(buffer, appSettings.NetworkSetting.PortWebServer, 10);
    sprintf(dcontext->buffer, "Yes?\r\n%s\r\n%s\r\n%s\r\n%s\r\n", buffer, interface->hostname, macAddrToString(&interface->macAddr, NULL), FIRMWARE_VERSION);
    error = socketSendTo(dcontext->socket, &ipAddr, port,
            dcontext->buffer, strlen(dcontext->buffer), NULL, 0);
}
