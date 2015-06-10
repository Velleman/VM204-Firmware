/**
 * @file mib2_module.c
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
 * @section Description
 *
 * The second version of the Management Information Base (MIB-II) is used to
 * manage TCP/IP-based hosts. Refer to the following RFCs for complete details:
 * - RFC 1156: MIB for Network Management of TCP/IP-based internets
 * - RFC 1213: MIB for Network Management of TCP/IP-based internets (version 2)
 * - RFC 2863: The Interfaces Group MIB
 * - RFC 4293: MIB for the Internet Protocol (IP)
 * - RFC 4022: MIB for the Transmission Control Protocol (TCP)
 * - RFC 4113: MIB for the User Datagram Protocol (UDP)
 * - RFC 3418: MIB for the Simple Network Management Protocol (SNMP)
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.6.0
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL SNMP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "snmp/mib2_module.h"
#include "snmp/mib2_impl.h"
#include "crypto.h"
#include "asn1.h"
#include "oid.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (MIB2_SUPPORT == ENABLED)


/**
 * @brief MIB-II base
 **/

Mib2Base mib2Base;


/**
 * @brief MIB-II objects
 **/

const MibObject mib2Objects[] =
{
   //System group
   {
      "sysDescr",
      {43, 6, 1, 2, 1, 1, 1},
      7,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_OCTET_STRING,
      MIB_ACCESS_READ_ONLY,
      &mib2Base.sysGroup.sysDescr,
      &mib2Base.sysGroup.sysDescrLen,
      MIB2_SYS_DESCR_SIZE,
      NULL,
      NULL,
      NULL
   },
   {
      "sysObjectID",
      {43, 6, 1, 2, 1, 1, 2},
      7,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_OBJECT_IDENTIFIER,
      MIB_ACCESS_READ_ONLY,
      &mib2Base.sysGroup.sysObjectID,
      &mib2Base.sysGroup.sysObjectIDLen,
      MIB2_SYS_OBJECT_ID_SIZE,
      NULL,
      NULL,
      NULL
   },
   {
      "sysUpTime",
      {43, 6, 1, 2, 1, 1, 3},
      7,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_TIME_TICKS,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetSysUpTime,
      NULL
   },
   //Interfaces group
   {
      "ifNumber",
      {43, 6, 1, 2, 1, 2, 1},
      7,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_ONLY,
      &mib2Base.ifGroup.ifNumber,
      NULL,
      sizeof(int32_t),
      NULL,
      NULL,
      NULL
   },
   //Interfaces table
   {
      "ifIndex",
      {43, 6, 1, 2, 1, 2, 2, 1, 1},
      9,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifDescr",
      {43, 6, 1, 2, 1, 2, 2, 1, 2},
      9,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_OCTET_STRING,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      MIB2_IF_DESCR_SIZE,
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifType",
      {43, 6, 1, 2, 1, 2, 2, 1, 3},
      9,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifMtu",
      {43, 6, 1, 2, 1, 2, 2, 1, 4},
      9,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifSpeed",
      {43, 6, 1, 2, 1, 2, 2, 1, 5},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_GAUGE32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifPhysAddress",
      {43, 6, 1, 2, 1, 2, 2, 1, 6},
      9,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_OCTET_STRING,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      MIB2_PHYS_ADDRESS_SIZE,
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifAdminStatus",
      {43, 6, 1, 2, 1, 2, 2, 1, 7},
      9,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifOperStatus",
      {43, 6, 1, 2, 1, 2, 2, 1, 8},
      9,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifLastChange",
      {43, 6, 1, 2, 1, 2, 2, 1, 9},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_TIME_TICKS,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifInOctets",
      {43, 6, 1, 2, 1, 2, 2, 1, 10},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifInUcastPkts",
      {43, 6, 1, 2, 1, 2, 2, 1, 11},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifInNUcastPkts",
      {43, 6, 1, 2, 1, 2, 2, 1, 12},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifInDiscards",
      {43, 6, 1, 2, 1, 2, 2, 1, 13},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifInErrors",
      {43, 6, 1, 2, 1, 2, 2, 1, 14},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifInUnknownProtos",
      {43, 6, 1, 2, 1, 2, 2, 1, 15},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifOutOctets",
      {43, 6, 1, 2, 1, 2, 2, 1, 16},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifOutUcastPkts",
      {43, 6, 1, 2, 1, 2, 2, 1, 17},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifOutNUcastPkts",
      {43, 6, 1, 2, 1, 2, 2, 1, 18},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifOutDiscards",
      {43, 6, 1, 2, 1, 2, 2, 1, 19},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifOutErrors",
      {43, 6, 1, 2, 1, 2, 2, 1, 20},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_COUNTER32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   },
   {
      "ifOutQLen",
      {43, 6, 1, 2, 1, 2, 2, 1, 21},
      9,
      ASN1_CLASS_APPLICATION,
      MIB_TYPE_GAUGE32,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(uint32_t),
      NULL,
      mib2GetIfEntry,
      mib2GetNextIfEntry
   }
};


/**
 * @brief MIB-II module
 **/

const MibModule mib2Module =
{
   mib2Objects,
   arraysize(mib2Objects),
   mib2Init,
   mib2Lock,
   mib2Unlock
};

#endif
