/**
 * @file snmp_agent_pdu.h
 * @brief SNMP agent (PDU processing)
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

#ifndef _SNMP_AGENT_PDU_H
#define _SNMP_AGENT_PDU_H

//Dependencies
#include "core/net.h"
#include "snmp/snmp_agent.h"

//SNMP agent related functions
error_t snmpParseMessage(SnmpAgentContext *context, const uint8_t *p, size_t length);

error_t snmpParseGetRequestPdu(SnmpAgentContext *context, const uint8_t *p, size_t length);
error_t snmpParseGetBulkRequestPdu(SnmpAgentContext *context, const uint8_t *p, size_t length);
error_t snmpParseSetRequestPdu(SnmpAgentContext *context, const uint8_t *p, size_t length);

error_t snmpParsePduHeader(SnmpAgentContext *context, const uint8_t *p, size_t length);
error_t snmpWritePduHeader(SnmpAgentContext *context);

#endif
