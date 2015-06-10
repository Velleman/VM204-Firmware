/**
 * @file snmp_agent.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL SNMP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "snmp/snmp_agent.h"
#include "snmp/snmp_agent_pdu.h"
#include "oid.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (SNMP_AGENT_SUPPORT == ENABLED)


/**
 * @brief Initialize settings with default values
 * @param[out] settings Structure that contains SNMP agent settings
 **/

void snmpAgentGetDefaultSettings(SnmpAgentSettings *settings)
{
   //Use default interface
   settings->interface = NULL;
   //Default SNMP version
   settings->version = SNMP_VERSION_1;

   //Default read-only community string
   strcpy(settings->readOnlyCommunity, "public");
   //Default read-write community string
   strcpy(settings->readWriteCommunity, "private");
   //Default trap community string
   strcpy(settings->trapCommunity, "public");
}


/**
 * @brief SNMP agent initialization
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] settings SNMP agent specific settings
 * @return Error code
 **/

error_t snmpAgentInit(SnmpAgentContext *context, const SnmpAgentSettings *settings)
{
   error_t error;
   OsTask *task;

   //Debug message
   TRACE_INFO("Initializing SNMP agent...\r\n");

   //Ensure the parameters are valid
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   //Clear the SNMP agent context
   memset(context, 0, sizeof(SnmpAgentContext));

   //Save the underlying network interface
   context->interface = settings->interface;
   //SNMP version identifier
   context->version = settings->version;

   //Read-only community string
   strcpy(context->readOnlyCommunity, settings->readOnlyCommunity);
   //Read-write community string
   strcpy(context->readWriteCommunity, settings->readWriteCommunity);
   //Trap community string
   strcpy(context->trapCommunity, settings->trapCommunity);

   //Open a UDP socket
   context->socket = socketOpen(SOCKET_TYPE_DGRAM, SOCKET_IP_PROTO_UDP);
   //Failed to open socket?
   if(!context->socket)
      return ERROR_OPEN_FAILED;

   //Start of exception handling block
   do
   {
      //Explicitly associate the socket with the relevant interface
      error = socketBindToInterface(context->socket, context->interface);
      //Unable to bind the socket to the desired interface?
      if(error) break;

      //The client listens for SNMP messages on port 161
      error = socketBind(context->socket, &IP_ADDR_ANY, SNMP_PORT);
      //Unable to bind the socket to the desired port?
      if(error) break;

      //The socket operates in non-blocking mode
      //error = socketSetTimeout(context->socket, 0);
      //Any error to report?
      //if(error) break;

      //Start the SNMP agent service
      task = osCreateTask("SNMP Agent", snmpAgentTask,
         context, SNMP_AGENT_STACK_SIZE, SNMP_AGENT_PRIORITY);

      //Unable to create the task?
      if(task == OS_INVALID_HANDLE)
         error = ERROR_OUT_OF_RESOURCES;

      //End of exception handling block
   } while(0);

   //Any error to report?
   if(error)
   {
      //Close underlying socket
      socketClose(context->socket);
   }

   //Return status code
   return error;
}


/**
 * @brief Load a MIB module
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] module Pointer the MIB module
 * @return Error code
 **/

error_t snmpAgentLoadMib(SnmpAgentContext *context, const MibModule *module)
{
   uint_t i;
   uint_t j;

   //Check parameters
   if(context == NULL || module == NULL)
      return ERROR_INVALID_PARAMETER;
   if(module->numObjects < 1)
      return ERROR_INVALID_PARAMETER;

   //Make sure there is enough room to add the specified MIB
   if(context->mibModuleCount >= SNMP_AGENT_MAX_MIB_COUNT)
      return ERROR_OUT_OF_RESOURCES;

   //Loop through existing MIBs
   for(i = 0; i < context->mibModuleCount; i++)
   {
      //Compare object identifiers
      if(oidComp(module->objects[0].oid, module->objects[0].oidLen,
         context->mibModule[i]->objects[0].oid, context->mibModule[i]->objects[0].oidLen) < 0)
      {
         //Make room for the new MIB
         for(j = context->mibModuleCount; j > i; j--)
            context->mibModule[j] = context->mibModule[j - 1];

         //We are done
         break;
      }
   }

   //Add the new MIB to the list
   context->mibModule[i] = module;
   //Update the number of MIBs
   context->mibModuleCount++;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Start SNMP agent
 * @param[in] context Pointer to the SNMP agent context
 * @return Error code
 **/

error_t snmpAgentStart(SnmpAgentContext *context)
{
   //Check parameters
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   //Debug message
   TRACE_INFO("Starting SNMP agent...\r\n");

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief SNMP agent task
 * @param[in] param Pointer to the SNMP agent context
 **/

void snmpAgentTask(void *param)
{
   error_t error;
   SnmpAgentContext *context;

   //Point to the SNMP agent context
   context = (SnmpAgentContext *) param;

   //Main loop
   while(1)
   {
      //Wait for an incoming datagram
      error = socketReceiveFrom(context->socket, &context->remoteIpAddr, &context->remotePort,
         context->request.buffer, SNMP_MSG_MAX_SIZE, &context->request.bufferLen, 0);

      //Any datagram received?
      if(!error)
      {
         //Parse incoming SNMP message
         snmpParseMessage(context, context->request.buffer, context->request.bufferLen);
      }
   }
}

#endif
