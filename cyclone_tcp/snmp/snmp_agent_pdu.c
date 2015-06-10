/**
 * @file snmp_agent_pdu.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL SNMP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "snmp/snmp_agent.h"
#include "snmp/snmp_agent_pdu.h"
#include "snmp/snmp_agent_misc.h"
#include "crypto.h"
#include "asn1.h"
#include "oid.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (SNMP_AGENT_SUPPORT == ENABLED)


/**
 * @brief Parse incoming SNMP message
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] p Pointer to the SNMP message
 * @param[in] length Length of the SNMP message
 * @return Error code
 **/

error_t snmpParseMessage(SnmpAgentContext *context, const uint8_t *p, size_t length)
{
   error_t error;
   int32_t version;
   Asn1Tag tag;

   //Debug message
   TRACE_INFO("SNMP message received from %s port %" PRIu16 " (%" PRIuSIZE " bytes)...\r\n",
      ipAddrToString(&context->remoteIpAddr, NULL), context->remotePort, length);

   //Display the contents of the SNMP message
   TRACE_DEBUG_ARRAY("  ", p, length);

   //Dump ASN.1 structure
   error = asn1DumpObject(p, length, 0);
   //Any error to report?
   if(error) return error;

   //The SNMP message is encapsulated within a sequence
   error = asn1ReadTag(p, length, &tag);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //Enforce encoding, class and type
   error = asn1CheckTag(&tag, TRUE, ASN1_CLASS_UNIVERSAL, ASN1_TYPE_SEQUENCE);
   //The tag does not match the criteria?
   if(error) return error;

   //Point to the first field of the sequence
   p = tag.value;
   length = tag.length;

   //Read version identifier
   error = asn1ReadInt32(p, length, &tag, &version);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //The SNMP agent verifies the version number. If there is a mismatch,
   //it discards the datagram and performs no further actions
   if(version != context->version)
      return ERROR_INVALID_VERSION;

   //Point to the next field
   p += tag.totalLength;
   length -= tag.totalLength;

   //Read SNMP community name
   error = asn1ReadTag(p, length, &tag);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //Enforce encoding, class and type
   error = asn1CheckTag(&tag, FALSE, ASN1_CLASS_UNIVERSAL, ASN1_TYPE_OCTET_STRING);
   //The tag does not match the criteria?
   if(error) return error;

   //Save community name
   context->request.community = tag.value;
   context->request.communityLen = tag.length;

   //Point to the next field
   p += tag.totalLength;
   length -= tag.totalLength;

   //Read PDU
   error = asn1ReadTag(p, length, &tag);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //Check encoding
   if(tag.constructed != TRUE)
      return ERROR_WRONG_ENCODING;
   //Enforce class
   if(tag.class != ASN1_CLASS_CONTEXT_SPECIFIC)
      return ERROR_INVALID_CLASS;

   //Save PDU type
   context->request.pduType = (SnmpPduType) tag.type;

   //Process the protocol data unit
   switch(context->request.pduType)
   {
   case SNMP_PDU_GET_REQUEST:
   case SNMP_PDU_GET_NEXT_REQUEST:
      //Parse GetRequest-PDU or GetNextRequest-PDU
      error = snmpParseGetRequestPdu(context, tag.value, tag.length);
      break;
   case SNMP_PDU_GET_BULK_REQUEST:
      //Parse GetBulkRequest-PDU
      error = snmpParseGetBulkRequestPdu(context, tag.value, tag.length);
      break;
   case SNMP_PDU_SET_REQUEST:
      //Parse SetRequest-PDU
      error = snmpParseSetRequestPdu(context, tag.value, tag.length);
      break;
   default:
      //Invalid PDU type
      error = ERROR_INVALID_TYPE;
      break;
   }

   //Failed to parse PDU?
   if(error)
      return error;

   //Format response PDU header
   error = snmpWritePduHeader(context);
   //Any error to report?
   if(error) return error;

   //Debug message
   TRACE_INFO("SNMP message sent (%" PRIuSIZE " bytes)...\r\n", context->response.messageLen);
   //Display the contents of the SNMP message
   TRACE_DEBUG_ARRAY("  ", context->response.message, context->response.messageLen);

   //Display ASN.1 structure
   error = asn1DumpObject(context->response.message, context->response.messageLen, 0);
   //Any error to report?
   if(error) return error;

   //Send SNMP response message
   error = socketSendTo(context->socket, &context->remoteIpAddr, context->remotePort,
      context->response.message, context->response.messageLen, NULL, 0);

   //Return status code
   return error;
}


/**
 * @brief Parse GetRequest-PDU or GetNextRequest-PDU
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] p Pointer to the protocol data unit
 * @param[in] length Length of the protocol data unit
 * @return Error code
 **/

error_t snmpParseGetRequestPdu(SnmpAgentContext *context, const uint8_t *p, size_t length)
{
   error_t error;
   size_t n;
   uint_t index;
   SnmpVarBind var;

   //Debug message
   if(context->request.pduType == SNMP_PDU_GET_REQUEST)
   {
      TRACE_INFO("Parsing GetRequest-PDU...\r\n");
   }
   else if(context->request.pduType == SNMP_PDU_GET_NEXT_REQUEST)
   {
      TRACE_INFO("Parsing GetNextRequest-PDU...\r\n");
   }

   //Verify community name
   error = snmpCheckCommunity(context, MIB_ACCESS_READ_ONLY);
   //Wrong community name?
   if(error) return error;

   //Parse PDU header
   error = snmpParsePduHeader(context, p, length);
   //Failed to parse PDU header?
   if(error) return error;

   //Point to the first variable binding of the request
   p = context->request.varBindList;
   length = context->request.varBindListLen;

   //Lock access to MIB bases
   snmpLockMib(context);

   //Loop through the list
   for(index = 1; length > 0; index++)
   {
      //Parse variable binding
      error = snmpParseVarBinding(p, length, &var, &n);
      //Failed to parse variable binding?
      if(error) break;

      //GetRequest-PDU?
      if(context->request.pduType == SNMP_PDU_GET_REQUEST)
      {
         //Retrieve object value
         error = snmpGetObjectValue(context, &var);
      }
      //GetNextRequest-PDU?
      else
      {
         //Search the MIB for the next object
         error = snmpGetNextObject(context, &var);

         //SNMPv1 version?
         if(context->version == SNMP_VERSION_1)
         {
            //Check status code
            if(error == NO_ERROR)
            {
               //Retrieve object value
               error = snmpGetObjectValue(context, &var);
            }
            else
            {
               //Stop immediately
               break;
            }
         }
         //SNMPv2c version?
         else
         {
            //Check status code
            if(error == NO_ERROR)
            {
               //Retrieve object value
               error = snmpGetObjectValue(context, &var);
            }
            else if(error == ERROR_OBJECT_NOT_FOUND)
            {
               //The variable binding's value field is set to endOfMibView
               var.class = ASN1_CLASS_CONTEXT_SPECIFIC;
               var.type = SNMP_EXCEPTION_END_OF_MIB_VIEW;
               var.valueLen = 0;

               //Catch exception
               error = NO_ERROR;
            }
            else
            {
               //Stop immediately
               break;
            }
         }
      }

      //Failed to retrieve object value?
      if(error)
      {
         //SNMPv1 version?
         if(context->version == SNMP_VERSION_1)
         {
            //Stop immediately
            break;
         }
         //SNMPv2c version?
         else
         {
            //Catch exception
            if(error == ERROR_ACCESS_DENIED ||
               error == ERROR_OBJECT_NOT_FOUND)
            {
               //The variable binding's value field is set to noSuchObject
               var.class = ASN1_CLASS_CONTEXT_SPECIFIC;
               var.type = SNMP_EXCEPTION_NO_SUCH_OBJECT;
               var.valueLen = 0;
            }
            else if(error == ERROR_INSTANCE_NOT_FOUND)
            {
               //The variable binding's value field is set to noSuchInstance
               var.class = ASN1_CLASS_CONTEXT_SPECIFIC;
               var.type = SNMP_EXCEPTION_NO_SUCH_INSTANCE;
               var.valueLen = 0;
            }
            else
            {
               //Stop immediately
               break;
            }
         }
      }

      //Write variable binding in the response message
      error = snmpWriteVarBinding(context, &var);
      //Any error to report?
      if(error) break;

      //Advance data pointer
      p += n;
      length -= n;
   }

   //Unlock access to MIB bases
   snmpUnlockMib(context);

   //Check status code
   if(error)
   {
      //Set error-status and error-index fields
      error = snmpTranslateStatusCode(context, error, index);
      //If the parsing of the request fails, the SNMP agent discards the message
      if(error) return error;

      //The Response-PDU is re-formatted with the same values in its request-id
      //and variable-bindings fields as the received GetRequest-PDU
      error = snmpCopyVarBindingList(context);
      //Any error to report?
      if(error) return error;
   }

   //Format PDU header
   error = snmpWritePduHeader(context);
   //Return status code
   return error;
}


/**
 * @brief Parse GetBulkRequest-PDU
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] p Pointer to the protocol data unit
 * @param[in] length Length of the protocol data unit
 * @return Error code
 **/

error_t snmpParseGetBulkRequestPdu(SnmpAgentContext *context, const uint8_t *p, size_t length)
{
   error_t error;
   size_t n;
   size_t m;
   uint_t index;
   bool_t endOfMibView;
   const uint8_t *next;
   SnmpVarBind var;

   //Debug message
   TRACE_INFO("Parsing GetBulkRequest-PDU...\r\n");

   //Verify community name
   error = snmpCheckCommunity(context, MIB_ACCESS_READ_ONLY);
   //Wrong community name?
   if(error) return error;

   //Parse PDU header
   error = snmpParsePduHeader(context, p, length);
   //Failed to parse PDU header?
   if(error) return error;

   //Point to the first variable binding of the request
   p = context->request.varBindList;
   length = context->request.varBindListLen;

   //Lock access to MIB bases
   snmpLockMib(context);

   //Loop through the list
   for(index = 1; length > 0; index++)
   {
      //The non-repeaters field specifies the number of non-repeating objects
      //at the start of the variable binding list
      if((index - 1) == context->request.nonRepeaters)
      {
         //Pointer to the first variable binding that will be processed during
         //the next iteration
         next = context->response.varBindList + context->response.varBindListLen;

         //Actual size of the variable binding list
         m = context->response.varBindListLen;

         //This flag tells whether all variable bindings have the value field
         //set to endOfMibView for a given iteration
         endOfMibView = TRUE;

         //If the max-repetitions field is zero, the list is trimmed to the
         //first non-repeating variable bindings
         if(context->request.maxRepetitions == 0)
            break;
      }

      //Parse variable binding
      error = snmpParseVarBinding(p, length, &var, &n);
      //Failed to parse variable binding?
      if(error) break;

      //Search the MIB for the next object
      error = snmpGetNextObject(context, &var);

      //SNMPv1 version?
      if(context->version == SNMP_VERSION_1)
      {
         //Check status code
         if(error == NO_ERROR)
         {
            //Retrieve object value
            error = snmpGetObjectValue(context, &var);
         }
         else
         {
            //Stop immediately
            break;
         }
      }
      //SNMPv2c version?
      else
      {
         //Check status code
         if(error == NO_ERROR)
         {
            endOfMibView = FALSE;
            //Retrieve object value
            error = snmpGetObjectValue(context, &var);
         }
         else if(error == ERROR_OBJECT_NOT_FOUND)
         {
            //The variable binding's value field is set to endOfMibView
            var.class = ASN1_CLASS_CONTEXT_SPECIFIC;
            var.type = SNMP_EXCEPTION_END_OF_MIB_VIEW;
            var.valueLen = 0;

            //Catch exception
            error = NO_ERROR;
         }
         else
         {
            //Stop immediately
            break;
         }
      }

      //Failed to retrieve object value?
      if(error)
      {
         //SNMPv1 version?
         if(context->version == SNMP_VERSION_1)
         {
            //Stop immediately
            break;
         }
         //SNMPv2c version?
         else
         {
            //Catch exception
            if(error == ERROR_ACCESS_DENIED ||
               error == ERROR_OBJECT_NOT_FOUND)
            {
               //The variable binding's value field is set to noSuchObject
               var.class = ASN1_CLASS_CONTEXT_SPECIFIC;
               var.type = SNMP_EXCEPTION_NO_SUCH_OBJECT;
               var.valueLen = 0;
            }
            else if(error == ERROR_INSTANCE_NOT_FOUND)
            {
               //The variable binding's value field is set to noSuchInstance
               var.class = ASN1_CLASS_CONTEXT_SPECIFIC;
               var.type = SNMP_EXCEPTION_NO_SUCH_INSTANCE;
               var.valueLen = 0;
            }
            else
            {
               //Stop immediately
               break;
            }
         }
      }

      //Write variable binding in the response message
      error = snmpWriteVarBinding(context, &var);
      //Any error to report?
      if(error) break;

      //Advance data pointer
      p += n;
      length -= n;

      //Next iteration?
      if(length == 0 && index > context->request.nonRepeaters)
      {
         //Decrement repeat counter
         context->request.maxRepetitions--;

         //Last iteration?
         if(!context->request.maxRepetitions)
            break;
         //All variable bindings have the value field set to endOfMibView?
         if(endOfMibView)
            break;

         //Point to the first variable binding to be processed
         p = next;
         //Number of bytes to be processed
         length = context->response.varBindListLen - m;
         //Rewind index
         index = context->request.nonRepeaters;
      }
   }

   //Unlock access to MIB bases
   snmpUnlockMib(context);

   //Check status code
   if(error == ERROR_BUFFER_OVERFLOW)
   {
      //If the size of the message containing the requested number of variable
      //bindings would be greater than the maximum message size, then the
      //response is generated with a lesser number of variable bindings
   }
   else if(error)
   {
      //Set error-status and error-index fields
      error = snmpTranslateStatusCode(context, error, index);
      //If the parsing of the request fails, the SNMP agent discards the message
      if(error) return error;

      //The Response-PDU is re-formatted with the same values in its request-id
      //and variable-bindings fields as the received GetRequest-PDU
      error = snmpCopyVarBindingList(context);
      //Any error to report?
      if(error) return error;
   }

   //Format PDU header
   error = snmpWritePduHeader(context);
   //Return status code
   return error;
}


/**
 * @brief Parse SetRequest-PDU
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] p Pointer to the protocol data unit
 * @param[in] length Length of the protocol data unit
 * @return Error code
 **/

error_t snmpParseSetRequestPdu(SnmpAgentContext *context, const uint8_t *p, size_t length)
{
   error_t error;
   size_t n;
   uint_t index;
   SnmpVarBind var;

   //Debug message
   TRACE_INFO("Parsing SetRequest-PDU...\r\n");

   //Verify community name
   error = snmpCheckCommunity(context, MIB_ACCESS_READ_WRITE);
   //Wrong community name?
   if(error) return error;

   //Parse PDU header
   error = snmpParsePduHeader(context, p, length);
   //Failed to parse PDU header?
   if(error) return error;

   //The variable bindings are processed as a two phase operation. In the
   //first phase, each variable binding is validated
   p = context->request.varBindList;
   length = context->request.varBindListLen;

   //Loop through the list
   for(index = 1; length > 0; index++)
   {
      //Parse variable binding
      error = snmpParseVarBinding(p, length, &var, &n);
      //Failed to parse variable binding?
      if(error) break;

      //Assign object value
      error = snmpSetObjectValue(context, &var, FALSE);
      //Any error to report?
      if(error) break;

      //Advance data pointer
      p += n;
      length -= n;
   }

   //If all validations are successful, then each variable is altered in
   //the second phase
   if(!error)
   {
      //The changes are commited to the MIB base during the second phase
      p = context->request.varBindList;
      length = context->request.varBindListLen;

      //Lock access to MIB bases
      snmpLockMib(context);

      //Loop through the list
      for(index = 1; length > 0; index++)
      {
         //Parse variable binding
         error = snmpParseVarBinding(p, length, &var, &n);
         //Failed to parse variable binding?
         if(error) break;

         //Assign object value
         error = snmpSetObjectValue(context, &var, TRUE);
         //Any error to report?
         if(error) break;

         //Advance data pointer
         p += n;
         length -= n;
      }

      //Unlock access to MIB bases
      snmpUnlockMib(context);
   }

   //Any error to report?
   if(error)
   {
      //Set error-status and error-index fields
      error = snmpTranslateStatusCode(context, error, index);
      //If the parsing of the request fails, the SNMP agent discards the message
      if(error) return error;
   }

   //The SNMP agent sends back a GetResponse-PDU of identical form
   error = snmpCopyVarBindingList(context);
   //Any error to report?
   if(error) return error;

   //Format PDU header
   error = snmpWritePduHeader(context);
   //Return status code
   return error;
}


/**
 * @brief Parse PDU header
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] p Pointer to the protocol data unit
 * @param[in] length Length of the protocol data unit
 * @return Error code
 **/

error_t snmpParsePduHeader(SnmpAgentContext *context, const uint8_t *p, size_t length)
{
   error_t error;
   Asn1Tag tag;

   //Read request-id field
   error = asn1ReadInt32(p, length, &tag, &context->request.requestId);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //Point to the next field
   p += tag.totalLength;
   length -= tag.totalLength;

   //GetBulkRequest-PDU?
   if(context->request.pduType == SNMP_PDU_GET_BULK_REQUEST)
   {
      //Read non-repeaters field
      error = asn1ReadInt32(p, length, &tag, &context->request.nonRepeaters);
      //Failed to decode ASN.1 tag?
      if(error) return error;

      //If the value in the non-repeaters field is less than zero, then the
      //value of the field is set to zero
      if(context->request.nonRepeaters < 0)
         context->request.nonRepeaters = 0;

      //Point to the next field
      p += tag.totalLength;
      length -= tag.totalLength;

      //Read max-repetitions field
      error = asn1ReadInt32(p, length, &tag, &context->request.maxRepetitions);
      //Failed to decode ASN.1 tag?
      if(error) return error;

      //If the value in the max-repetitions field is less than zero, then the
      //value of the field is set to zero
      if(context->request.maxRepetitions < 0)
         context->request.maxRepetitions = 0;
   }
   else
   {
      //Read error-status field
      error = asn1ReadInt32(p, length, &tag, &context->request.errorStatus);
      //Failed to decode ASN.1 tag?
      if(error) return error;

      //Point to the next field
      p += tag.totalLength;
      length -= tag.totalLength;

      //Read error-index field
      error = asn1ReadInt32(p, length, &tag, &context->request.errorIndex);
      //Failed to decode ASN.1 tag?
      if(error) return error;
   }

   //Point to the next field
   p += tag.totalLength;
   length -= tag.totalLength;

   //The variable bindings are encapsulated within a sequence
   error = asn1ReadTag(p, length, &tag);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //Enforce encoding, class and type
   error = asn1CheckTag(&tag, TRUE, ASN1_CLASS_UNIVERSAL, ASN1_TYPE_SEQUENCE);
   //The tag does not match the criteria?
   if(error) return error;

   //Save the location of the variable binding list
   context->request.varBindList = tag.value;
   context->request.varBindListLen = tag.length;

   //The SNMP agent will send to the originator of the received
   //message a GetResponse-PDU
   context->response.pduType = SNMP_PDU_GET_RESPONSE;

   //The response uses the same community name as the request
   context->response.community = context->request.community;
   context->response.communityLen = context->request.communityLen;

   //The response uses the same identifier as the request
   context->response.requestId = context->request.requestId;

   //Clear error status
   context->response.errorStatus = SNMP_ERROR_NONE;
   context->response.errorIndex = 0;

   //Make room for the message header at the beginning of the buffer
   context->response.varBindList = context->response.buffer +
      context->response.communityLen + SNMP_MSG_HEADER_OVERHEAD;

   //Number of bytes available in the reponse buffer
   context->response.bytesAvailable = SNMP_MSG_MAX_SIZE -
      SNMP_MSG_HEADER_OVERHEAD - context->response.communityLen;

   //Reset byte counters
   context->response.varBindListLen = 0;
   context->response.oidLen = 0;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Write PDU header
 * @param[in] context Pointer to the SNMP agent context
 * @return Error code
 **/

error_t snmpWritePduHeader(SnmpAgentContext *context)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;

   //The PDU header will be encoded in reverse order...
   p = context->response.varBindList;
   //Length of the message
   length = context->response.varBindListLen;

   //The variable bindings are encapsulated within a sequence
   tag.constructed = TRUE;
   tag.class = ASN1_CLASS_UNIVERSAL;
   tag.type = ASN1_TYPE_SEQUENCE;
   tag.length = length;
   tag.value = NULL;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= n;
   //Update the length of the message
   length += n;

   //Write error index
   error = asn1WriteInt32(context->response.errorIndex, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= n;
   //Update the length of the message
   length += n;

   //Write error status
   error = asn1WriteInt32(context->response.errorStatus, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= n;
   //Update the length of the message
   length += n;

   //Write request identifier
   error = asn1WriteInt32(context->response.requestId, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= n;
   //Update the length of the message
   length += n;

   //The PDU is encapsulated within a sequence
   tag.constructed = TRUE;
   tag.class = ASN1_CLASS_CONTEXT_SPECIFIC;
   tag.type = context->response.pduType;
   tag.length = length;
   tag.value = NULL;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= n;
   //Update the length of the message
   length += n;

   //The commmunity string is encoded in ASN.1 format
   tag.constructed = FALSE;
   tag.class = ASN1_CLASS_UNIVERSAL;
   tag.type = ASN1_TYPE_OCTET_STRING;
   tag.length = context->response.communityLen;
   tag.value = context->response.community;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= n;
   //Update the length of the message
   length += n;

   //Write version identifier
   error = asn1WriteInt32(context->version, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= n;
   //Update the length of the message
   length += n;

   //The message is encapsulated within a sequence
   tag.constructed = TRUE;
   tag.class = ASN1_CLASS_UNIVERSAL;
   tag.type = ASN1_TYPE_SEQUENCE;
   tag.length = length;
   tag.value = NULL;

   //Calculate the total length of the ASN.1 tag
   error = asn1WriteTag(&tag, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Point to the first byte of the message
   context->response.message = p - n;
   //Total length of the message
   context->response.messageLen = length + n;

   //Successful processing
   return NO_ERROR;
}

#endif
