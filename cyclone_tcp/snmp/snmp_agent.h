/**
 * @file snmp_agent.h
 * @brief SNMP agent (Simple Network Management Protocol)
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

#ifndef _SNMP_AGENT_H
#define _SNMP_AGENT_H

//Dependencies
#include "core/net.h"
#include "snmp/snmp_common.h"
#include "snmp/mib_common.h"

//SNMP agent support
#ifndef SNMP_AGENT_SUPPORT
   #define SNMP_AGENT_SUPPORT DISABLED
#elif (SNMP_AGENT_SUPPORT != ENABLED && SNMP_AGENT_SUPPORT != DISABLED)
   #error SNMP_AGENT_SUPPORT parameter is not valid
#endif

//Stack size required to run the SNMP agent
#ifndef SNMP_AGENT_STACK_SIZE
   #define SNMP_AGENT_STACK_SIZE 550
#elif (SNMP_AGENT_STACK_SIZE < 1)
   #error SNMP_AGENT_STACK_SIZE parameter is not valid
#endif

//Priority at which the SNMP agent should run
#ifndef SNMP_AGENT_PRIORITY
   #define SNMP_AGENT_PRIORITY 1
#elif (SNMP_AGENT_PRIORITY < 0)
   #error SNMP_AGENT_PRIORITY parameter is not valid
#endif

//Maximum number of MIBs
#ifndef SNMP_AGENT_MAX_MIB_COUNT
   #define SNMP_AGENT_MAX_MIB_COUNT 4
#elif (SNMP_AGENT_MAX_MIB_COUNT < 1)
   #error SNMP_AGENT_MAX_MIB_COUNT parameter is not valid
#endif


/**
 * @brief SNMP agent settings
 **/

typedef struct
{
   NetInterface *interface;                           ///<Network interface to configure
   SnmpVersion version;                               ///<SNMP version identifier
   char_t readOnlyCommunity[SNMP_MAX_COMMUNITY_LEN];  ///<Read-only community string
   char_t readWriteCommunity[SNMP_MAX_COMMUNITY_LEN]; ///<Read-write community string
   char_t trapCommunity[SNMP_MAX_COMMUNITY_LEN];      ///<Trap community string
} SnmpAgentSettings;


/**
 * @brief SNMP request message
 **/

typedef struct
{
   uint8_t buffer[SNMP_MSG_MAX_SIZE]; ///<Buffer that holds the message
   size_t bufferLen;                  ///<Length of the message
   const uint8_t *community;          ///<Community name
   size_t communityLen;               ///<Length of the community name
   SnmpPduType pduType;               ///<PDU type
   int32_t requestId;                 ///<Request identifier
   int32_t errorStatus;               ///<Error status
   int32_t errorIndex;                ///<Error index
   int32_t nonRepeaters;              ///<GetBulkRequest-PDU specific parameter
   int32_t maxRepetitions;            ///<GetBulkRequest-PDU specific parameter
   const uint8_t *varBindList;        ///<List of variable bindings
   size_t varBindListLen;             ///<Length of the list in bytes
} SnmpAgentRequest;


/**
 * @brief SNMP response message
 **/

typedef struct
{
   uint8_t buffer[SNMP_MSG_MAX_SIZE]; ///<Buffer that holds the message
   const uint8_t *message;            ///<First byte of the message
   size_t messageLen;                 ///<Length of the message
   const uint8_t *community;          ///<Community name
   size_t communityLen;               ///<Length of the community name
   SnmpPduType pduType;               ///<PDU type
   int32_t requestId;                 ///<Request identifier
   int32_t errorStatus;               ///<Error status
   int32_t errorIndex;                ///<Error index
   uint8_t *varBindList;              ///<List of variable bindings
   size_t varBindListLen;             ///<Length of the list in bytes
   size_t bytesAvailable;             ///<Number of bytes available in the buffer
   size_t oidLen;                     ///<Length of the object identifier
} SnmpAgentResponse;


/**
 * @brief SNMP agent context
 **/

typedef struct
{
   NetInterface *interface;                              ///<Underlying network interface
   uint_t version;                                       ///<SNMP version identifier
   char_t readOnlyCommunity[SNMP_MAX_COMMUNITY_LEN];     ///<Read-only community string
   char_t readWriteCommunity[SNMP_MAX_COMMUNITY_LEN];    ///<Read-write community string
   char_t trapCommunity[SNMP_MAX_COMMUNITY_LEN];         ///<Trap community string
   const MibModule *mibModule[SNMP_AGENT_MAX_MIB_COUNT]; ///<MIB modules
   uint_t mibModuleCount;                                ///<Number of MIB modules
   Socket *socket;                                       ///<Underlying socket
   IpAddr remoteIpAddr;                                  ///<IP address of the manager
   uint16_t remotePort;                                  ///<Source port used by the SNMP manager
   SnmpAgentRequest request;                             ///<SNMP request message
   SnmpAgentResponse response;                           ///<SNMP response message
} SnmpAgentContext;


//SNMP agent related functions
void snmpAgentGetDefaultSettings(SnmpAgentSettings *settings);
error_t snmpAgentInit(SnmpAgentContext *context, const SnmpAgentSettings *settings);
error_t snmpAgentLoadMib(SnmpAgentContext *context, const MibModule *module);
error_t snmpAgentStart(SnmpAgentContext *context);

void snmpAgentTask(void *param);

#endif
