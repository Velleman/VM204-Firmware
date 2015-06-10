/**
 * @file mib2_module.h
 * @brief MIB-II module
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

#ifndef _MIB2_MODULE_H
#define _MIB2_MODULE_H

//Dependencies
#include "core/net.h"
#include "snmp/mib_common.h"

//MIB-II module support
#ifndef MIB2_SUPPORT
   #define MIB2_SUPPORT DISABLED
#elif (MIB2_SUPPORT != ENABLED && MIB2_SUPPORT != DISABLED)
   #error MIB2_SUPPORT parameter is not valid
#endif

//Size of sysDescr object
#ifndef MIB2_SYS_DESCR_SIZE
   #define MIB2_SYS_DESCR_SIZE 32
#elif (MIB2_SYS_DESCR_SIZE < 1)
   #error MIB2_SYS_DESCR_SIZE parameter is not valid
#endif

//Size of sysObjectID object
#ifndef MIB2_SYS_OBJECT_ID_SIZE
   #define MIB2_SYS_OBJECT_ID_SIZE 16
#elif (MIB2_SYS_OBJECT_ID_SIZE < 1)
   #error MIB2_SYS_OBJECT_ID_SIZE parameter is not valid
#endif

//Size of ifDescr object
#ifndef MIB2_IF_DESCR_SIZE
   #define MIB2_IF_DESCR_SIZE 16
#elif (MIB2_IF_DESCR_SIZE < 1)
   #error MIB2_IF_DESCR_SIZE parameter is not valid
#endif

//Size of PhysAddress data type
#ifndef MIB2_PHYS_ADDRESS_SIZE
   #define MIB2_PHYS_ADDRESS_SIZE 6
#elif (MIB2_PHYS_ADDRESS_SIZE < 6)
   #error MIB2_PHYS_ADDRESS_SIZE parameter is not valid
#endif

//Size of IpAddress data type
#ifndef MIB2_IP_ADDRESS_SIZE
   #define MIB2_IP_ADDRESS_SIZE 4
#elif (MIB2_IP_ADDRESS_SIZE != 4)
   #error MIB2_IP_ADDRESS_SIZE parameter is not valid
#endif


/**
 * @brief Interface type
 **/

typedef enum
{
   MIB2_IF_TYPE_OTHER           = 1,
   MIB2_IF_TYPE_ETHERNET_CSMACD = 6,
   MIB2_IF_TYPE_PROP_PTP_SERIAL = 22,
   MIB2_IF_TYPE_PPP             = 23,
   MIB2_IF_TYPE_SOFT_LOOPBACK   = 24,
   MIB2_IF_TYPE_SLIP            = 28,
   MIB2_IF_TYPE_RS232           = 33,
   MIB2_IF_TYPE_PARA            = 34,
   MIB2_IF_TYPE_USB             = 160
} Mib2IfType;


/**
 * @brief The desired state of the interface
 **/

typedef enum
{
   MIB2_IF_ADMIN_STATUS_UP      = 1,
   MIB2_IF_ADMIN_STATUS_DOWN    = 2,
   MIB2_IF_ADMIN_STATUS_TESTING = 3
} Mib2IfAdminStatus;


/**
 * @brief The operational state of the interface
 **/

typedef enum
{
   MIB2_IF_OPER_STATUS_UP      = 1,
   MIB2_IF_OPER_STATUS_DOWN    = 2,
   MIB2_IF_OPER_STATUS_TESTING = 3
} Mib2IfOperStatus;


/**
 * @brief System group
 **/

typedef struct
{
   char_t sysDescr[MIB2_SYS_DESCR_SIZE];
   size_t sysDescrLen;
   uint8_t sysObjectID[MIB2_SYS_OBJECT_ID_SIZE];
   size_t sysObjectIDLen;
   uint32_t sysUpTime;
} Mib2SysGroup;


/**
 * @brief Interfaces table entry
 **/

typedef struct
{
   int32_t ifIndex;
   char_t ifDescr[MIB2_IF_DESCR_SIZE];
   size_t ifDescrLen;
   int32_t ifType;
   int32_t ifMtu;
   uint32_t ifSpeed;
   uint8_t ifPhysAddress[MIB2_PHYS_ADDRESS_SIZE];
   size_t ifPhysAddressLen;
   int32_t ifAdminStatus;
   int32_t ifOperStatus;
   uint32_t ifLastChange;
   uint32_t ifInOctets;
   uint32_t ifInUcastPkts;
   uint32_t ifInNUcastPkts;
   uint32_t ifInDiscards;
   uint32_t ifInErrors;
   uint32_t ifInUnknownProtos;
   uint32_t ifOutOctets;
   uint32_t ifOutUcastPkts;
   uint32_t ifOutNUcastPkts;
   uint32_t ifOutDiscards;
   uint32_t ifOutErrors;
   uint32_t ifOutQLen;
} Mib2IfEntry;


/**
 * @brief Interfaces group
 **/

typedef struct
{
   int32_t ifNumber;
   Mib2IfEntry ifTable[NET_INTERFACE_COUNT];
} Mib2IfGroup;


/**
 * @brief MIB-II base
 **/

typedef struct
{
   Mib2SysGroup sysGroup;
   Mib2IfGroup ifGroup;
} Mib2Base;


//MIB-II related constants
extern Mib2Base mib2Base;
extern const MibObject mib2Objects[];
extern const MibModule mib2Module;

#endif
