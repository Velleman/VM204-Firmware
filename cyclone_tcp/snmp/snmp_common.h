/**
 * @file snmp_common.h
 * @brief Functions common to SNMP agent and SNMP manager
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

#ifndef _SNMP_COMMON_H
#define _SNMP_COMMON_H

//Dependencies
#include "core/net.h"

//Maximum size of SNMP messages
#ifndef SNMP_MSG_MAX_SIZE
   #define SNMP_MSG_MAX_SIZE 484
#elif (SNMP_MSG_MAX_SIZE < 484)
   #error SNMP_MSG_MAX_SIZE parameter is not valid
#endif

//Maximum length for community strings
#ifndef SNMP_MAX_COMMUNITY_LEN
   #define SNMP_MAX_COMMUNITY_LEN 20
#elif (SNMP_MAX_COMMUNITY_LEN < 8)
   #error SNMP_MAX_COMMUNITY_LEN parameter is not valid
#endif

//SNMP port number
#define SNMP_PORT 161
//SNMP trap port number
#define SNMP_TRAP_PORT 162

//SNMP message header overhead
#define SNMP_MSG_HEADER_OVERHEAD 37


/**
 * @brief SNMP version identifiers
 **/

typedef enum
{
   SNMP_VERSION_1 = 0,
   SNMP_VERSION_2 = 1,
   SNMP_VERSION_3 = 2
} SnmpVersion;


/**
 * @brief SNMP PDU types
 **/

typedef enum
{
   SNMP_PDU_GET_REQUEST      = 0,
   SNMP_PDU_GET_NEXT_REQUEST = 1,
   SNMP_PDU_GET_RESPONSE     = 2,
   SNMP_PDU_SET_REQUEST      = 3,
   SNMP_PDU_TRAP             = 4,
   SNMP_PDU_GET_BULK_REQUEST = 5,
   SNMP_PDU_INFORM_REQUEST   = 6,
   SNMP_PDU_TRAP_V2          = 7,
   SNMP_PDU_REPORT           = 8
} SnmpPduType;


/**
 * @brief SNMP generic traps
 **/

typedef enum
{
   SNMP_TRAP_COLD_START          = 0,
   SNMP_TRAP_WARM_START          = 1,
   SNMP_TRAP_LINK_DOWN           = 2,
   SNMP_TRAP_LINK_UP             = 3,
   SNMP_TRAP_AUTH_FAILURE        = 4,
   SNMP_TRAP_EGP_NEIGHBOR_LOSS   = 5,
   SNMP_TRAP_ENTERPRISE_SPECIFIC = 6
} SnmpTrap;


/**
 * @brief SNMP error status
 **/

typedef enum
{
   SNMP_ERROR_NONE                 = 0,
   SNMP_ERROR_TOO_BIG              = 1,
   SNMP_ERROR_NO_SUCH_NAME         = 2,
   SNMP_ERROR_BAD_VALUE            = 3,
   SNMP_ERROR_READ_ONLY            = 4,
   SNMP_ERROR_GENERIC              = 5,
   SNMP_ERROR_NO_ACCESS            = 6,
   SNMP_ERROR_WRONG_TYPE           = 7,
   SNMP_ERROR_WRONG_LENGTH         = 8,
   SNMP_ERROR_WRONG_ENCODING       = 9,
   SNMP_ERROR_WRONG_VALUE          = 10,
   SNMP_ERROR_NO_CREATION          = 11,
   SNMP_ERROR_INCONSISTENT_VALUE   = 12,
   SNMP_ERROR_RESOURCE_UNAVAILABLE = 13,
   SNMP_ERROR_COMMIT_FAILED        = 14,
   SNMP_ERROR_UNDO_FAILED          = 15,
   SNMP_ERROR_AUTHORIZATION        = 16,
   SNMP_ERROR_NOT_WRITABLE         = 17,
   SNMP_ERROR_INCONSISTENT_NAME    = 18
} SnmpErrorStatus;


/**
 * @brief SNMP exceptions
 **/

typedef enum
{
   SNMP_EXCEPTION_NO_SUCH_OBJECT   = 0,
   SNMP_EXCEPTION_NO_SUCH_INSTANCE = 1,
   SNMP_EXCEPTION_END_OF_MIB_VIEW  = 2
} SnmpException;


/**
 * @brief Variable binding
 **/

typedef struct
{
   const uint8_t *oid;
   size_t oidLen;
   uint_t class;
   uint_t type;
   const uint8_t *value;
   size_t valueLen;
} SnmpVarBind;


//SNMP related functions
error_t snmpEncodeInt32(int32_t value, uint8_t *dest, size_t *length);
error_t snmpEncodeUnsignedInt32(uint32_t value, uint8_t *dest, size_t *length);
error_t snmpEncodeUnsignedInt64(uint64_t value, uint8_t *dest, size_t *length);

error_t snmpDecodeInt32(const uint8_t *src, size_t length, int32_t *value);
error_t snmpDecodeUnsignedInt32(const uint8_t *src, size_t length, uint32_t *value);
error_t snmpDecodeUnsignedInt64(const uint8_t *src, size_t length, uint64_t *value);

#endif
