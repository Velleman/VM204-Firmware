/**
 * @file net.h
 * @brief TCP/IP stack core
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

#ifndef _NET_H
#define _NET_H

//Forward declaration of NetInterface structure
struct _NetInterface;
#define NetInterface struct _NetInterface

//Dependencies
#include "os_port.h"
#include "net_config.h"
#include "core/net_mem.h"
#include "endian.h"
#include "error.h"
#include "core/nic.h"
#include "core/ethernet.h"
#include "ipv4/ipv4.h"
#include "ipv4/ipv4_frag.h"
#include "ipv4/auto_ip.h"
#include "ipv6/ipv6.h"
#include "ipv6/ipv6_frag.h"
#include "ipv4/arp.h"
#include "ipv6/ndp.h"
#include "ipv6/slaac.h"
#include "ppp/ppp.h"
#include "dns/dns_client.h"
#include "mdns/mdns_responder.h"
#include "mdns/mdns_common.h"
#include "dns_sd/dns_sd.h"
#include "snmp/mib2_module.h"

//Deprecated properties
#ifdef TCP_IP_CALLBACK_TABLE_SIZE
   #warning TCP_IP_CALLBACK_TABLE_SIZE property is deprecated. NET_CALLBACK_TABLE_SIZE should be used instead.
   #define NET_CALLBACK_TABLE_SIZE TCP_IP_CALLBACK_TABLE_SIZE
#endif

#ifdef TCP_IP_MAX_IF_NAME_LEN
   #warning TCP_IP_MAX_IF_NAME_LEN property is deprecated. NET_MAX_IF_NAME_LEN should be used instead.
   #define NET_MAX_IF_NAME_LEN TCP_IP_MAX_IF_NAME_LEN
#endif

#ifdef TCP_IP_MAX_HOSTNAME_LEN
   #warning TCP_IP_MAX_HOSTNAME_LEN property is deprecated. NET_MAX_HOSTNAME_LEN should be used instead.
   #define NET_MAX_HOSTNAME_LEN TCP_IP_MAX_HOSTNAME_LEN
#endif

#ifdef TCP_IP_MAX_PROXY_NAME_LEN
   #warning TCP_IP_MAX_PROXY_NAME_LEN property is deprecated. NET_MAX_PROXY_NAME_LEN should be used instead.
   #define NET_MAX_PROXY_NAME_LEN TCP_IP_MAX_PROXY_NAME_LEN
#endif

#ifdef TCP_IP_STATIC_OS_RESOURCES
   #warning TCP_IP_STATIC_OS_RESOURCES property is deprecated. NET_STATIC_OS_RESOURCES should be used instead.
   #define NET_STATIC_OS_RESOURCES TCP_IP_STATIC_OS_RESOURCES
#endif

#ifdef TCP_IP_TICK_STACK_SIZE
   #warning TCP_IP_TICK_STACK_SIZE property is deprecated. NET_TICK_STACK_SIZE should be used instead.
   #define NET_TICK_STACK_SIZE TCP_IP_TICK_STACK_SIZE
#endif

#ifdef TCP_IP_TICK_PRIORITY
   #warning TCP_IP_TICK_PRIORITY property is deprecated. NET_TICK_PRIORITY should be used instead.
   #define NET_TICK_PRIORITY TCP_IP_TICK_PRIORITY
#endif

#ifdef TCP_IP_TICK_INTERVAL
   #warning TCP_IP_TICK_INTERVAL property is deprecated. NET_TICK_INTERVAL should be used instead.
   #define NET_TICK_INTERVAL TCP_IP_TICK_INTERVAL
#endif

#ifdef TCP_IP_RX_STACK_SIZE
   #warning TCP_IP_RX_STACK_SIZE property is deprecated. NET_RX_STACK_SIZE should be used instead.
   #define NET_RX_STACK_SIZE TCP_IP_RX_STACK_SIZE
#endif

#ifdef TCP_IP_RX_PRIORITY
   #warning TCP_IP_RX_PRIORITY property is deprecated. NET_RX_PRIORITY should be used instead.
   #define NET_RX_PRIORITY TCP_IP_RX_PRIORITY
#endif

//Number of network adapters
#ifndef NET_INTERFACE_COUNT
   #define NET_INTERFACE_COUNT 1
#elif (NET_INTERFACE_COUNT < 1)
   #error NET_INTERFACE_COUNT parameter is not valid
#endif

//Maximum number of callback functions that can be registered
//to monitor link changes
#ifndef NET_CALLBACK_TABLE_SIZE
   #define NET_CALLBACK_TABLE_SIZE 6
#elif (NET_CALLBACK_TABLE_SIZE < 1)
   #error NET_CALLBACK_TABLE_SIZE parameter is not valid
#endif

//Maximum length of interface name
#ifndef NET_MAX_IF_NAME_LEN
   #define NET_MAX_IF_NAME_LEN 8
#elif (NET_MAX_IF_NAME_LEN < 1)
   #error NET_MAX_IF_NAME_LEN parameter is not valid
#endif

//Maximum length of host name
#ifndef NET_MAX_HOSTNAME_LEN
   #define NET_MAX_HOSTNAME_LEN 16
#elif (NET_MAX_HOSTNAME_LEN < 1)
   #error NET_MAX_HOSTNAME_LEN parameter is not valid
#endif

//Maximum length of proxy server name
#ifndef NET_MAX_PROXY_NAME_LEN
   #define NET_MAX_PROXY_NAME_LEN 16
#elif (NET_MAX_PROXY_NAME_LEN < 1)
   #error NET_MAX_PROXY_NAME_LEN parameter is not valid
#endif

//OS resources are statically allocated at compile time
#ifndef NET_STATIC_OS_RESOURCES
   #define NET_STATIC_OS_RESOURCES DISABLED
#elif (NET_STATIC_OS_RESOURCES != ENABLED && NET_STATIC_OS_RESOURCES != DISABLED)
   #error NET_STATIC_OS_RESOURCES parameter is not valid
#endif

//Stack size required to run the TCP/IP tick task
#ifndef NET_TICK_STACK_SIZE
   #define NET_TICK_STACK_SIZE 550
#elif (NET_TICK_STACK_SIZE < 1)
   #error NET_TICK_STACK_SIZE parameter is not valid
#endif

//Priority at which the TCP/IP tick task should run
#ifndef NET_TICK_PRIORITY
   #define NET_TICK_PRIORITY 1
#elif (NET_TICK_PRIORITY < 0)
   #error NET_TICK_PRIORITY parameter is not valid
#endif

//TCP/IP stack tick interval
#ifndef NET_TICK_INTERVAL
   #define NET_TICK_INTERVAL 100
#elif (NET_TICK_INTERVAL < 100)
   #error NET_TICK_INTERVAL parameter is not valid
#endif

//Stack size required to run the TCP/IP RX task
#ifndef NET_RX_STACK_SIZE
   #define NET_RX_STACK_SIZE 650
#elif (NET_RX_STACK_SIZE < 1)
   #error NET_RX_STACK_SIZE parameter is not valid
#endif

//Priority at which the TCP/IP RX task should run
#ifndef NET_RX_PRIORITY
   #define NET_RX_PRIORITY 2
#elif (NET_RX_PRIORITY < 0)
   #error NET_RX_PRIORITY parameter is not valid
#endif

//Deprecated API support
#ifndef NET_DEPRECATED_API_SUPPORT
   #define NET_DEPRECATED_API_SUPPORT ENABLED
#elif (NET_DEPRECATED_API_SUPPORT != ENABLED && NET_DEPRECATED_API_SUPPORT != DISABLED)
   #error NET_DEPRECATED_API_SUPPORT parameter is not valid
#endif


/**
 * @brief Structure describing a network interface
 **/

struct _NetInterface
{
   uint32_t id;                                         ///<A unique number identifying the interface
   char_t name[NET_MAX_IF_NAME_LEN];                    ///<A unique name identifying the interface
   char_t hostname[NET_MAX_HOSTNAME_LEN];               ///<Host name
   MacAddr macAddr;                                     ///<Link-layer address
   char_t proxyName[NET_MAX_PROXY_NAME_LEN];            ///<Proxy server name
   uint16_t proxyPort;                                  ///<Proxy server port
   OsMutex macFilterMutex;                              ///<Mutex preventing simultaneous access to the MAC filter table
   MacFilterEntry macFilter[MAC_FILTER_MAX_SIZE];       ///<MAC filter table
   uint_t macFilterSize;                                ///<Number of entries in the MAC filter table
   uint8_t ethFrame[1536 /*ETH_MAX_FRAME_SIZE*/];       ///<Incoming Ethernet frame
   OsEvent nicTxEvent;                                  ///<Network controller TX event
   OsEvent nicRxEvent;                                  ///<Network controller RX event
   bool_t phyEvent;                                     ///<A PHY event is pending
   OsMutex nicDriverMutex;                              ///<Mutex preventing simultaneous access to the NIC driver
   const NicDriver *nicDriver;                          ///<NIC driver
   const PhyDriver *phyDriver;                          ///<PHY driver
   const SpiDriver *spiDriver;                          ///<Underlying SPI driver
   const UartDriver *uartDriver;                        ///<Underlying UART driver
   const ExtIntDriver *extIntDriver;                    ///<External interrupt line driver
   uint8_t nicContext[NIC_CONTEXT_SIZE];                ///<Driver specific context
   bool_t linkState;                                    ///<Link state
   bool_t speed100;                                     ///<Link speed
   bool_t speed1000;
   bool_t fullDuplex;                                   ///<Duplex mode
   bool_t configured;                                   ///<Configuration done

#if (IPV4_SUPPORT == ENABLED)
   Ipv4Config ipv4Config;                               ///<IPv4 configuration
   uint16_t ipv4Identification;                         ///<IPv4 fragment identification field
#if (IPV4_FRAG_SUPPORT == ENABLED)
   OsMutex ipv4FragQueueMutex;                          ///<Mutex preventing simultaneous access to reassembly queue
   Ipv4FragDesc ipv4FragQueue[IPV4_MAX_FRAG_DATAGRAMS]; ///<IPv4 fragment reassembly queue
#endif
   OsMutex arpCacheMutex;                               ///<Mutex preventing simultaneous access to ARP cache
   ArpCacheEntry arpCache[ARP_CACHE_SIZE];              ///<ARP cache
   OsMutex ipv4FilterMutex;                             ///<Mutex preventing simultaneous access to the IPv4 filter table
   Ipv4FilterEntry ipv4Filter[IPV4_FILTER_MAX_SIZE];    ///<IPv4 filter table
   uint_t ipv4FilterSize;                               ///<Number of entries in the IPv4 filter table
#if (IGMP_SUPPORT == ENABLED)
   systime_t igmpv1RouterPresentTimer;                  ///<IGMPv1 router present timer
   bool_t igmpv1RouterPresent;                          ///<An IGMPv1 query has been recently heard
#endif
#if (AUTO_IP_SUPPORT == ENABLED)
   AutoIpContext *autoIpContext;                        ///<Auto-IP context
#endif
#endif

#if (IPV6_SUPPORT == ENABLED)
   Ipv6Config ipv6Config;                               ///<IPv6 configuration
#if (IPV6_FRAG_SUPPORT == ENABLED)
   uint32_t ipv6Identification;                         ///<IPv6 Fragment identification field
   OsMutex ipv6FragQueueMutex;                          ///<Mutex preventing simultaneous access to reassembly queue
   Ipv6FragDesc ipv6FragQueue[IPV6_MAX_FRAG_DATAGRAMS]; ///<IPv6 fragment reassembly queue
#endif
   OsMutex ndpCacheMutex;                               ///<Mutex preventing simultaneous access to Neighbor cache
   NdpCacheEntry ndpCache[NDP_CACHE_SIZE];              ///<Neighbor cache
   OsMutex ipv6FilterMutex;                             ///<Mutex preventing simultaneous access to the IPv6 filter table
   Ipv6FilterEntry ipv6Filter[IPV6_FILTER_MAX_SIZE];    ///<IPv6 filter table
   uint_t ipv6FilterSize;                               ///<Number of entries in the IPv6 filter table
#if (SLAAC_SUPPORT == ENABLED)
   SlaacContext *slaacContext;                          ///<SLAAC context
#endif
#endif

#if (MDNS_RESPONDER_SUPPORT == ENABLED)
   MdnsContext mdnsContext;                             ///<mDNS responder context
#endif

#if (DNS_SD_SUPPORT == ENABLED)
   char_t instanceName[DNS_SD_MAX_INSTANCE_LEN];        ///<Instance name
   const DnsSdService *services;                        ///<List of registered services
   uint_t numServices;                                  ///<Number of registered services
#endif

#if (PPP_SUPPORT == ENABLED)
   PppContext *pppContext;                              ///<PPP context
#endif

#if (NET_STATIC_OS_RESOURCES == ENABLED)
   OsTask rxTask;                                       ///<Task that handles incoming frames
   uint_t rxTaskStack[NET_RX_STACK_SIZE];               ///<Stack size required to run RX task
#else
   OsTask *rxTask;                                      ///<Task that handles incoming frames
#endif

#if (MIB2_SUPPORT == ENABLED)
   Mib2IfEntry *mibIfEntry;
#endif
};


/**
 * @brief Link change callback
 **/

typedef void (*LinkChangeCallback)(NetInterface *interface, bool_t linkState, void *params);


/**
 * @brief Entry describing a user callback
 **/

typedef struct
{
   NetInterface *interface;
   LinkChangeCallback callback;
   void *params;
} LinkChangeCallbackDesc;


//Network interfaces
extern NetInterface netInterface[NET_INTERFACE_COUNT];

//TCP/IP stack related functions
error_t netInit(void);

error_t netSetMacAddr(NetInterface *interface, const MacAddr *macAddr);
error_t netGetMacAddr(NetInterface *interface, MacAddr *macAddr);

error_t netSetInterfaceName(NetInterface *interface, const char_t *name);
error_t netSetHostname(NetInterface *interface, const char_t *name);
error_t netSetProxy(NetInterface *interface, const char_t *name, uint16_t port);

error_t netSetDriver(NetInterface *interface, const NicDriver *driver);
error_t netSetPhyDriver(NetInterface *interface, const PhyDriver *driver);
error_t netSetSpiDriver(NetInterface *interface, const SpiDriver *driver);
error_t netSetUartDriver(NetInterface *interface, const UartDriver *driver);
error_t netSetExtIntDriver(NetInterface *interface, const ExtIntDriver *driver);

bool_t netGetLinkState(NetInterface *interface);

error_t netConfigInterface(NetInterface *interface);

void netTickTask(void *param);
void netRxTask(void *param);

NetInterface *netGetDefaultInterface(void);

error_t netInitRand(uint32_t seed);
uint32_t netGetRand(void);
int32_t netGetRandRange(int32_t min, int32_t max);

error_t netAttachLinkChangeCallback(NetInterface *interface,
   LinkChangeCallback callback, void *params, uint_t *cookie);

error_t netDetachLinkChangeCallback(uint_t cookie);

void netInvokeLinkChangeCallback(NetInterface *interface, bool_t linkState);

//Deprecated API
#if (NET_DEPRECATED_API_SUPPORT == ENABLED)
   #define tcpIpStackInit netInit
   #define tcpIpStackSetInterfaceName netSetInterfaceName
   #define tcpIpStackSetHostname netSetHostname
   #define tcpIpStackSetDriver netSetDriver
   #define tcpIpStackSetPhyDriver netSetPhyDriver
   #define tcpIpStackSetSpiDriver netSetSpiDriver
   #define tcpIpStackSetUartDriver netSetUartDriver
   #define tcpIpStackSetExtIntDriver netSetExtIntDriver
   #define tcpIpStackSetMacAddr netSetMacAddr
   #define tcpIpStackSetProxy netSetProxy
   #define tcpIpStackGetLinkState netGetLinkState
   #define tcpIpStackConfigInterface netConfigInterface
   #define tcpIpStackTickTask netTickTask
   #define tcpIpStackRxTask netRxTask
   #define tcpIpStackGetDefaultInterface netGetDefaultInterface
   #define tcpIpStackInitRand netInitRand
   #define tcpIpStackGetRand netGetRand
   #define tcpIpStackGetRandRange netGetRandRange
   #define tcpIpStackAttachLinkChangeCallback netAttachLinkChangeCallback
   #define tcpIpStackDetachLinkChangeCallback netDetachLinkChangeCallback
   #define tcpIpStackInvokeLinkChangeCallback netInvokeLinkChangeCallback

   #define ChunkedBuffer NetBuffer
   #define chunkedBufferGetLength netBufferGetLength
   #define chunkedBufferRead netBufferRead
#endif

#endif
