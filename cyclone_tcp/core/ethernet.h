/**
 * @file ethernet.h
 * @brief Ethernet
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

#ifndef _ETHERNET_H
#define _ETHERNET_H

//Dependencies
#include "core/net.h"

//Ethernet support
#ifndef ETH_SUPPORT
   #define ETH_SUPPORT ENABLED
#elif (ETH_SUPPORT != ENABLED && ETH_SUPPORT != DISABLED)
   #error ETH_SUPPORT parameter is not valid
#endif

//Maximum size of the MAC filter table
#ifndef MAC_FILTER_MAX_SIZE
   #define MAC_FILTER_MAX_SIZE 8
#elif (MAC_FILTER_MAX_SIZE < 4)
   #error MAC_FILTER_MAX_SIZE parameter is not valid
#endif

//CRC32 calculation using a pre-calculated lookup table
#ifndef ETH_FAST_CRC_SUPPORT
   #define ETH_FAST_CRC_SUPPORT DISABLED
#elif (ETH_FAST_CRC_SUPPORT != ENABLED && ETH_FAST_CRC_SUPPORT != DISABLED)
   #error ETH_FAST_CRC_SUPPORT parameter is not valid
#endif

//Minimum Ethernet frame size
#define ETH_MIN_FRAME_SIZE 64
//Maximum Ethernet frame size
#define ETH_MAX_FRAME_SIZE 1518
//Ethernet maximum transmission unit
#define ETH_MTU 1500
//Ethernet CRC field size
#define ETH_CRC_SIZE 4

//Copy MAC address
#define macCopyAddr(destMacAddr, srcMacAddr) memcpy(destMacAddr, srcMacAddr, sizeof(MacAddr))

//Compare MAC addresses
#define macCompAddr(macAddr1, macAddr2) (!memcmp(macAddr1, macAddr2, sizeof(MacAddr)))

//Determine whether a MAC address is a group address
#define macIsMulticastAddr(macAddr) ((macAddr)->b[0] & 0x01)


/**
 * @brief MAC address flags
 **/

typedef enum
{
   MAC_ADDR_FLAG_MULTICAST = 0x01,
   MAC_ADDR_FLAG_LOCAL     = 0x02
} MacAddrFlags;


/**
 * @brief Ethernet Type field
 **/

typedef enum
{
   ETH_TYPE_IPV4 = 0x0800,
   ETH_TYPE_ARP  = 0x0806,
   ETH_TYPE_RARP = 0x8035,
   ETH_TYPE_IPV6 = 0x86DD
} EthType;


//Win32 compiler?
#if defined(_WIN32)
   #pragma pack(push, 1)
#endif


/**
 * @brief MAC address
 **/

typedef __start_packed struct
{
   __start_packed union
   {
      uint8_t b[6];
      uint16_t w[3];
   };
} __end_packed MacAddr;


/**
 * @brief Ethernet frame header
 **/

typedef __start_packed struct
{
   MacAddr destAddr; //0-5
   MacAddr srcAddr;  //6-11
   uint16_t type;    //12-13
   uint8_t data[];   //14
} __end_packed EthHeader;


//Win32 compiler?
#if defined(_WIN32)
   #pragma pack(pop)
#endif


/**
 * @brief MAC filter table entry
 **/

typedef struct
{
   MacAddr addr;    ///<MAC address
   uint_t refCount; ///<Reference count for the current entry
} MacFilterEntry;


//Ethernet related constants
extern const MacAddr MAC_UNSPECIFIED_ADDR;
extern const MacAddr MAC_BROADCAST_ADDR;
extern const uint8_t ethPadding[64];

//Ethernet related functions
error_t ethInit(NetInterface *interface);

void ethProcessFrame(NetInterface *interface, EthHeader *ethFrame, size_t length);

error_t ethSendFrame(NetInterface *interface, const MacAddr *destAddr,
   NetBuffer *buffer, size_t offset, uint16_t type);

error_t ethCheckDestAddr(NetInterface *interface, const MacAddr *macAddr);
error_t ethAcceptMulticastAddr(NetInterface *interface, const MacAddr *macAddr);
error_t ethDropMulticastAddr(NetInterface *interface, const MacAddr *macAddr);

uint32_t ethCalcCrc(const void *data, size_t length);
uint32_t ethCalcCrcEx(const NetBuffer *buffer, size_t offset, size_t length);

NetBuffer *ethAllocBuffer(size_t length, size_t *offset);

error_t macStringToAddr(const char_t *str, MacAddr *macAddr);
char_t *macAddrToString(const MacAddr *macAddr, char_t *str);

void ethDumpHeader(const EthHeader *ethHeader);

#endif
