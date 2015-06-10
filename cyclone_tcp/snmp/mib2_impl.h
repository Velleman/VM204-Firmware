/**
 * @file mib2_impl.h
 * @brief MIB-II module implementation
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

#ifndef _MIB2_IMPL_H
#define _MIB2_IMPL_H

//Dependencies
#include "core/net.h"
#include "snmp/mib_common.h"

//Macro definitions
#define MIB2_LOCK() mib2Lock()
#define MIB2_UNLOCK() mib2Unlock()
#define MIB2_SET_INTEGER(name, value) name = value
#define MIB2_SET_GAUGE32(name, value) name = value
#define MIB2_SET_TIME_TICKS(name, value) name = value
#define MIB2_SET_OCTET_STRING(name, value, length) memcpy(name, value, length)
#define MIB2_SET_OCTET_STRING_LEN(name, length) name = length
#define MIB2_INC_COUNTER32(name, value) name += value
#define MIB2_INC_COUNTER64(name, value) name += value

//MIB-II related functions
error_t mib2Init(void);
void mib2Lock(void);
void mib2Unlock(void);

error_t mib2GetSysUpTime(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen);

error_t mib2GetIfEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen);

error_t mib2GetNextIfEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, uint8_t *nextOid, size_t *nextOidLen);

#endif
