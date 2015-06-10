/**
 * @file snmp_agent_misc.h
 * @brief SNMP agent (miscellaneous functions)
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

#ifndef _SNMP_AGENT_MISC_H
#define _SNMP_AGENT_MISC_H

//Dependencies
#include "core/net.h"
#include "snmp/snmp_agent.h"

//SNMP agent related functions
void snmpLockMib(SnmpAgentContext *context);
void snmpUnlockMib(SnmpAgentContext *context);

error_t snmpParseVarBinding(const uint8_t *p,
   size_t length, SnmpVarBind *var, size_t *consumed);

error_t snmpWriteVarBinding(SnmpAgentContext *context, const SnmpVarBind *var);
error_t snmpCopyVarBindingList(SnmpAgentContext *context);

error_t snmpCheckCommunity(SnmpAgentContext *context, MibAccess mode);
error_t snmpTranslateStatusCode(SnmpAgentContext *context, error_t status, uint_t index);

error_t snmpSetObjectValue(SnmpAgentContext *context, SnmpVarBind *var, bool_t commit);
error_t snmpGetObjectValue(SnmpAgentContext *context, SnmpVarBind *var);
error_t snmpGetNextObject(SnmpAgentContext *context, SnmpVarBind *var);

const MibObject *snmpFindMibObject(SnmpAgentContext *context,
   const uint8_t *oid, size_t oidLen);

#endif
