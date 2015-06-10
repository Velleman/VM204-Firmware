/**
 * @file snmp_agent_misc.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL SNMP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "snmp/snmp_agent.h"
#include "snmp/snmp_agent_misc.h"
#include "crypto.h"
#include "asn1.h"
#include "oid.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (SNMP_AGENT_SUPPORT == ENABLED)


/**
 * @brief Lock MIB bases
 **/

void snmpLockMib(SnmpAgentContext *context)
{
   uint_t i;

   //Loop through MIBs
   for(i = 0; i < context->mibModuleCount; i++)
   {
      //Lock access to MIB base
      if(context->mibModule[i]->lock != NULL)
      {
         context->mibModule[i]->lock();
      }
   }
}


/**
 * @brief Unlock MIB bases
 **/

void snmpUnlockMib(SnmpAgentContext *context)
{
   uint_t i;

   //Loop through MIBs
   for(i = 0; i < context->mibModuleCount; i++)
   {
      //Unlock access to MIB base
      if(context->mibModule[i]->unlock != NULL)
      {
         context->mibModule[i]->unlock();
      }
   }
}


/**
 * @brief Parse variable binding
 * @param[in] p Input stream where to read the variable binding
 * @param[in] length Number of bytes available in the input stream
 * @param[out] var Variable binding
 * @param[out] consumed Total number of bytes that have been consumed
 * @return Error code
 **/

error_t snmpParseVarBinding(const uint8_t *p,
   size_t length, SnmpVarBind *var, size_t *consumed)
{
   error_t error;
   Asn1Tag tag;

   //The variable binding is encapsulated within a sequence
   error = asn1ReadTag(p, length, &tag);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //Enforce encoding, class and type
   error = asn1CheckTag(&tag, TRUE, ASN1_CLASS_UNIVERSAL, ASN1_TYPE_SEQUENCE);
   //The tag does not match the criteria?
   if(error) return error;

   //Total number of bytes that have been consumed
   *consumed = tag.totalLength;

   //Point to the first item of the sequence
   p = tag.value;
   length = tag.length;

   //Read object name
   error = asn1ReadTag(p, length, &tag);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //Enforce encoding, class and type
   error = asn1CheckTag(&tag, FALSE, ASN1_CLASS_UNIVERSAL, ASN1_TYPE_OBJECT_IDENTIFIER);
   //The tag does not match the criteria?
   if(error) return error;

   //Save object identifier
   var->oid = tag.value;
   var->oidLen = tag.length;

   //Point to the next item
   p += tag.totalLength;
   length += tag.totalLength;

   //Read object value
   error = asn1ReadTag(p, length, &tag);
   //Failed to decode ASN.1 tag?
   if(error) return error;

   //Make sure that the tag is valid
   if(tag.constructed)
      return ERROR_INVALID_TAG;

   //Save object class
   var->class = tag.class;
   //Save object type
   var->type = tag.type;
   //Save object value
   var->value = tag.value;
   var->valueLen = tag.length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Write variable binding
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] var Variable binding
 * @return Error code
 **/

error_t snmpWriteVarBinding(SnmpAgentContext *context, const SnmpVarBind *var)
{
   error_t error;
   size_t m;
   size_t n;
   uint8_t *p;
   Asn1Tag tag;

   //The object's name is encoded in ASN.1 format
   tag.constructed = FALSE;
   tag.class = ASN1_CLASS_UNIVERSAL;
   tag.type = ASN1_TYPE_OBJECT_IDENTIFIER;
   tag.length = var->oidLen;
   tag.value = NULL;

   //Calculate the total length of the ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, NULL, &m);
   //Any error to report?
   if(error) return error;

   //The object's value is encoded in ASN.1 format
   tag.constructed = FALSE;
   tag.class = var->class;
   tag.type = var->type;
   tag.length = var->valueLen;
   tag.value = NULL;

   //Calculate the total length of the ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, NULL, &n);
   //Any error to report?
   if(error) return error;

   //The variable binding is encapsulated within a sequence
   tag.constructed = TRUE;
   tag.class = ASN1_CLASS_UNIVERSAL;
   tag.type = ASN1_TYPE_SEQUENCE;
   tag.length = m + n;
   tag.value = NULL;

   //The first pass computes the total length of the sequence
   error = asn1WriteTag(&tag, FALSE, NULL, &n);
   //Any error to report?
   if(error) return error;

   //Make the buffer is large enough to hold the whole sequence
   if(n > context->response.bytesAvailable)
      return ERROR_BUFFER_OVERFLOW;

   //The second pass encodes the sequence in reverse order
   p = context->response.varBindList + context->response.varBindListLen + n;

   //Encode the object's value using ASN.1
   tag.constructed = FALSE;
   tag.class = var->class;
   tag.type = var->type;
   tag.length = var->valueLen;
   tag.value = var->value;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, TRUE, p, &m);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= m;

   //Encode the object's name using ASN.1
   tag.constructed = FALSE;
   tag.class = ASN1_CLASS_UNIVERSAL;
   tag.type = ASN1_TYPE_OBJECT_IDENTIFIER;
   tag.length = var->oidLen;
   tag.value = var->oid;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Move backward
   p -= n;

   //The variable binding is encapsulated within a sequence
   tag.constructed = TRUE;
   tag.class = ASN1_CLASS_UNIVERSAL;
   tag.type = ASN1_TYPE_SEQUENCE;
   tag.length = m + n;
   tag.value = NULL;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, TRUE, p, &n);
   //Any error to report?
   if(error) return error;

   //Update the length of the list
   context->response.varBindListLen += tag.totalLength;
   //Number of bytes available in the reponse buffer
   context->response.bytesAvailable -= tag.totalLength;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Copy the list of variable bindings
 * @param[in] context Pointer to the SNMP agent context
 * @return Error code
 **/

error_t snmpCopyVarBindingList(SnmpAgentContext *context)
{
   size_t n;

   //Number of bytes available in the reponse buffer
   n = SNMP_MSG_MAX_SIZE - SNMP_MSG_HEADER_OVERHEAD -
      context->response.communityLen;

   //Sanity check
   if(context->request.varBindListLen > n)
      return ERROR_BUFFER_OVERFLOW;

   //Copy the list of variable bindings to the response buffer
   memcpy(context->response.varBindList, context->request.varBindList,
      context->request.varBindListLen);

   //Save the length of the list
   context->response.varBindListLen = context->request.varBindListLen;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Verify community name
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] mode Desired access mode
 * @return Error code
 **/

error_t snmpCheckCommunity(SnmpAgentContext *context, MibAccess mode)
{
   size_t n;

   //Retrieve the length of the read-write community string
   n = strlen(context->readWriteCommunity);

   //Check whether the community name matches the read-write community string
   if(context->request.communityLen == n)
   {
      if(!memcmp(context->request.community, context->readWriteCommunity, n))
         return NO_ERROR;
   }

   //Read-only access mode?
   if(mode == MIB_ACCESS_READ_ONLY)
   {
      //Retrieve the length of the read-only community string
      n = strlen(context->readOnlyCommunity);

      //Check whether the community name matches the read-only community string
      if(context->request.communityLen == n)
      {
         if(!memcmp(context->request.community, context->readOnlyCommunity, n))
            return NO_ERROR;
      }
   }

   //Debug message
   TRACE_WARNING("  Invalid community name!\r\n");

   //Invalid community name
   return ERROR_ACCESS_DENIED;
}


/**
 * @brief Translate status code
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] status Status code
 * @param[in] index Index of the variable binding in the list that caused an exception
 * @return error code
 **/

error_t snmpTranslateStatusCode(SnmpAgentContext *context, error_t status, uint_t index)
{
   //SNMPv1 version?
   if(context->version == SNMP_VERSION_1)
   {
      //Set error-status and error-index fields
      switch(status)
      {
      case NO_ERROR:
         //Return noError status code
         context->response.errorStatus = SNMP_ERROR_NONE;
         context->response.errorIndex = 0;
         break;
      case ERROR_OBJECT_NOT_FOUND:
      case ERROR_INSTANCE_NOT_FOUND:
      case ERROR_ACCESS_DENIED:
         //Return noSuchName status code
         context->response.errorStatus = SNMP_ERROR_NO_SUCH_NAME;
         context->response.errorIndex = index;
         break;
      case ERROR_WRONG_TYPE:
      case ERROR_WRONG_LENGTH:
      case ERROR_WRONG_ENCODING:
      case ERROR_WRONG_VALUE:
         //Return badValue status code
         context->response.errorStatus = SNMP_ERROR_BAD_VALUE;
         context->response.errorIndex = index;
         break;
      case ERROR_READ_FAILED:
      case ERROR_WRITE_FAILED:
         //Return genError status code
         context->response.errorStatus = SNMP_ERROR_GENERIC;
         context->response.errorIndex = index;
         break;
      case SNMP_ERROR_TOO_BIG:
         //Return tooBig status code
         context->response.errorStatus = SNMP_ERROR_TOO_BIG;
         context->response.errorIndex = 0;
         break;
      default:
         //If the parsing of the request fails, the SNMP agent discards
         //the message and performs no further actions
         return status;
      }
   }
   else
   //SNMPv2c version?
   {
      //Set error-status and error-index fields
      switch(status)
      {
      case NO_ERROR:
         //Return noError status code
         context->response.errorStatus = SNMP_ERROR_NONE;
         context->response.errorIndex = 0;
         break;
      case ERROR_OBJECT_NOT_FOUND:
      case ERROR_INSTANCE_NOT_FOUND:
      case ERROR_ACCESS_DENIED:
         //Return noAccess status code
         context->response.errorStatus = SNMP_ERROR_NO_ACCESS;
         context->response.errorIndex = index;
         break;
      case ERROR_WRONG_TYPE:
         //Return wrongType status code
         context->response.errorStatus = SNMP_ERROR_WRONG_TYPE;
         context->response.errorIndex = index;
      case ERROR_WRONG_LENGTH:
         //Return wrongLength status code
         context->response.errorStatus = SNMP_ERROR_WRONG_LENGTH;
         context->response.errorIndex = index;
      case ERROR_WRONG_ENCODING:
         //Return wrongEncoding status code
         context->response.errorStatus = SNMP_ERROR_WRONG_ENCODING;
         context->response.errorIndex = index;
         break;
      case ERROR_WRONG_VALUE:
         //Return wrongValue status code
         context->response.errorStatus = SNMP_ERROR_WRONG_VALUE;
         context->response.errorIndex = index;
         break;
      case ERROR_READ_FAILED:
      case ERROR_WRITE_FAILED:
         //Return genError status code
         context->response.errorStatus = SNMP_ERROR_GENERIC;
         context->response.errorIndex = index;
         break;
      case SNMP_ERROR_TOO_BIG:
         //Return tooBig status code
         context->response.errorStatus = SNMP_ERROR_TOO_BIG;
         context->response.errorIndex = 0;
         break;
      default:
         //If the parsing of the request fails, the SNMP agent discards
         //the message and performs no further actions
         return status;
      }
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Assign object value
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] var Variable binding
 * @param[in] commit This flag tells whether the changes should be
 *   committed to the MIB base
 * @return Error code
 **/

error_t snmpSetObjectValue(SnmpAgentContext *context, SnmpVarBind *var, bool_t commit)
{
   error_t error;
   size_t n;
   MibVariant *value;
   const MibObject *object;

   //Search the MIB for the specified object
   object = snmpFindMibObject(context, var->oid, var->oidLen);

   //Cannot found the specified object?
   if(object == NULL)
      return ERROR_OBJECT_NOT_FOUND;

   //Debug message
   TRACE_INFO("  %s\r\n", object->name);

   //Make sure the specified object is available for set operations
   if(object->access != MIB_ACCESS_READ_WRITE)
      return ERROR_ACCESS_DENIED;

   //Check class
   if(var->class != object->class)
      return ERROR_WRONG_TYPE;
   //Check type
   if(var->type != object->type)
      return ERROR_WRONG_TYPE;

   //Point to the object value
   value = (MibVariant *) var->value;
   //Get the length of the object value
   n = var->valueLen;

   //Check object class
   if(object->class == ASN1_CLASS_UNIVERSAL)
   {
      //Check object type
      if(object->type == ASN1_TYPE_INTEGER)
      {
         int32_t val;

         //Integer objects use ASN.1 encoding rules
         error = snmpDecodeInt32(var->value, n, &val);
         //Conversion failed?
         if(error) return ERROR_WRONG_ENCODING;

         //Point to the scratch buffer
         value = (MibVariant *) context->response.buffer;
         //Save resulting value
         value->integer = val;
         //Integer size
         n = sizeof(int32_t);
      }
   }
   else if(object->class == ASN1_CLASS_APPLICATION)
   {
      //Check object type
      if(object->type == MIB_TYPE_IP_ADDRESS)
      {
         //IpAddress objects have fixed size
         if(n != object->valueSize)
            return ERROR_WRONG_LENGTH;
      }
      else if(object->type == MIB_TYPE_COUNTER32 ||
         object->type == MIB_TYPE_GAUGE32 ||
         object->type == MIB_TYPE_TIME_TICKS)
      {
         uint32_t val;

         //Counter32, Gauge32 and TimeTicks objects use ASN.1 encoding rules
         error = snmpDecodeUnsignedInt32(var->value, n, &val);
         //Conversion failed?
         if(error) return ERROR_WRONG_ENCODING;

         //Point to the scratch buffer
         value = (MibVariant *) context->response.buffer;
         //Save resulting value
         value->counter32 = val;
         //Integer size
         n = sizeof(uint32_t);
      }
      else if(object->type == MIB_TYPE_COUNTER64)
      {
         uint64_t val;

         //Counter64 objects use ASN.1 encoding rules
         error = snmpDecodeUnsignedInt64(var->value, n, &val);
         //Conversion failed?
         if(error) return ERROR_WRONG_ENCODING;

         //Point to the scratch buffer
         value = (MibVariant *) context->response.buffer;
         //Save resulting value
         value->counter64 = val;
         //Integer size
         n = sizeof(uint64_t);
      }
   }

   //Check the length of the object
   if(n > object->valueSize)
      return ERROR_WRONG_LENGTH;

   //Objects can be assigned a value using a callback function
   if(object->setValue != NULL)
   {
      //Check whether the changes shall be committed to the MIB base
      if(commit)
      {
         //Invoke callback function to assign object value
         error = object->setValue(object, var->oid, var->oidLen, value, n);
      }
      else
      {
         //Successful write operation
         error = NO_ERROR;
      }
   }
   //Simple scalar objects can also be attached to a variable
   else if(object->value != NULL)
   {
      //Check whether the changes shall be committed to the MIB base
      if(commit)
      {
         //Record the length of the object value
         if(object->valueLen != NULL)
            *object->valueLen = n;

         //Set object value
         memcpy(object->value, value, n);
      }

      //Successful write operation
      error = NO_ERROR;
   }
   else
   {
      //Report an error
      error = ERROR_READ_FAILED;
   }

   //Return status code
   return error;
}


/**
 * @brief Retrieve object value
 * @param[in] context Pointer to the SNMP agent context
 * @param[out] var Variable binding
 * @return Error code
 **/

error_t snmpGetObjectValue(SnmpAgentContext *context, SnmpVarBind *var)
{
   error_t error;
   size_t n;
   MibVariant *value;
   const MibObject *object;

   //Search the MIB for the specified object
   object = snmpFindMibObject(context, var->oid, var->oidLen);

   //Cannot found the specified object?
   if(object == NULL)
      return ERROR_OBJECT_NOT_FOUND;

   //Debug message
   TRACE_INFO("  %s\r\n", object->name);

   //Make sure the specified object is available for get operations
   if(object->access != MIB_ACCESS_READ_ONLY &&
      object->access != MIB_ACCESS_READ_WRITE)
   {
      //Report an error
      return ERROR_ACCESS_DENIED;
   }

   //Buffer where to store the object value
   value = (MibVariant *) (context->response.varBindList +
      context->response.varBindListLen + context->response.oidLen);

   //Number of bytes available in the buffer
   n = context->response.bytesAvailable - context->response.oidLen;

   //Check object class
   if(object->class == ASN1_CLASS_UNIVERSAL)
   {
      //Check object type
      if(object->type == ASN1_TYPE_INTEGER)
      {
         //Make sure the buffer is large enough
         if(n < object->valueSize)
            return ERROR_BUFFER_OVERFLOW;

         //Integer objects have fixed size
         n = object->valueSize;
      }
   }
   else if(object->class == ASN1_CLASS_APPLICATION)
   {
      //Check object type
      if(object->type == MIB_TYPE_IP_ADDRESS ||
         object->type == MIB_TYPE_COUNTER32 ||
         object->type == MIB_TYPE_GAUGE32 ||
         object->type == MIB_TYPE_TIME_TICKS ||
         object->type == MIB_TYPE_COUNTER64)
      {
         //Make sure the buffer is large enough
         if(n < object->valueSize)
            return ERROR_BUFFER_OVERFLOW;

         //IpAddress, Counter32, Gauge32, TimeTicks and
         //Counter64 objects have fixed size
         n = object->valueSize;
      }
   }

   //Object value can be retrieved using a callback function
   if(object->getValue != NULL)
   {
      //Invoke callback function to retrieve object value
      error = object->getValue(object, var->oid, var->oidLen, value, &n);
   }
   //Simple scalar objects can also be attached to a variable
   else if(object->value != NULL)
   {
      //Get the length of the object value
      if(object->valueLen != NULL)
         n = *object->valueLen;

      //Retrieve object value
      memcpy(value, object->value, n);
      //Successful read operation
      error = NO_ERROR;
   }
   else
   {
      //Report an error
      error = ERROR_READ_FAILED;
   }

   //Unable to retrieve object value?
   if(error)
      return error;

   //Check object class
   if(object->class == ASN1_CLASS_UNIVERSAL)
   {
      //Check object type
      if(object->type == ASN1_TYPE_INTEGER)
      {
         //Encode Integer objects using ASN.1 rules
         error = snmpEncodeInt32(value->integer, (uint8_t *) value, &n);
      }
      else
      {
         //No conversion required for OctetString and ObjectIdentifier objects
         error = NO_ERROR;
      }
   }
   else if(object->class == ASN1_CLASS_APPLICATION)
   {
      //Check object type
      if(object->type == MIB_TYPE_COUNTER32 ||
         object->type == MIB_TYPE_GAUGE32 ||
         object->type == MIB_TYPE_TIME_TICKS)
      {
         //Encode Counter32, Gauge32 and TimeTicks objects using ASN.1 rules
         error = snmpEncodeUnsignedInt32(value->counter32, (uint8_t *) value, &n);
      }
      else if(object->type == MIB_TYPE_COUNTER64)
      {
         //Encode Counter64 objects using ASN.1 rules
         error = snmpEncodeUnsignedInt64(value->counter64, (uint8_t *) value, &n);
      }
      else
      {
         //No conversion required for Opaque objects
         error = NO_ERROR;
      }
   }

   //Save object class and type
   var->class = object->class;
   var->type = object->type;

   //Save object value
   var->value = (uint8_t *) value;
   var->valueLen = n;

   //Return status code
   return error;
}


/**
 * @brief Search MIBs for the next object
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] var Variable binding
 * @return Error pointer
 **/

error_t snmpGetNextObject(SnmpAgentContext *context, SnmpVarBind *var)
{
   error_t error;
   uint_t i;
   uint_t j;
   size_t nextOidLen;
   uint8_t *nextOid;
   const MibObject *object;

   //Buffer where to store the next object identifier
   nextOid = context->response.varBindList + context->response.varBindListLen;

   //Loop through MIBs
   for(i = 0; i < context->mibModuleCount; i++)
   {
      //Point the first object of the MIB
      object = context->mibModule[i]->objects;

      //Loop through objects
      for(j = 0; j < context->mibModule[i]->numObjects; j++)
      {
         //Scalar or tabular object?
         if(object->getNext == NULL)
         {
            //Take in account the instance sub-identifier to determine
            //the length of the OID
            nextOidLen = object->oidLen + 1;

            //Make sure the buffer is large enough to hold the entire OID
            if(nextOidLen > context->response.bytesAvailable)
               return ERROR_BUFFER_OVERFLOW;

            //Copy object identifier
            memcpy(nextOid, object->oid, object->oidLen);
            //Append instance sub-identifier
            nextOid[nextOidLen - 1] = 0;

            //Perform lexicographical comparison
            if(oidComp(var->oid, var->oidLen, nextOid, nextOidLen) < 0)
            {
               //Replace the original OID with the name of the next object
               var->oid = nextOid;
               var->oidLen = nextOidLen;

               //Save the length of the OID
               context->response.oidLen = nextOidLen;

               //The specified OID lexicographically precedes the name
               //of the current object
               return NO_ERROR;
            }
         }
         else
         {
            //Maximum acceptable size of the OID
            nextOidLen = context->response.bytesAvailable;
            //Search the MIB for the next object
            error = object->getNext(object, var->oid, var->oidLen, nextOid, &nextOidLen);

            //Check status code
            if(error == NO_ERROR)
            {
               //Replace the original OID with the name of the next object
               var->oid = nextOid;
               var->oidLen = nextOidLen;

               //Save the length of the OID
               context->response.oidLen = nextOidLen;

               //The specified OID lexicographically precedes the name
               //of the current object
               return NO_ERROR;
            }
            if(error != ERROR_OBJECT_NOT_FOUND)
            {
               //Exit immediately
               return error;
            }
         }

         //Point to the next object in the MIB
         object++;
      }
   }

   //The specified OID does not lexicographically precede the
   //name of some object
   return ERROR_OBJECT_NOT_FOUND;
}


/**
 * @brief Search MIBs for the given object
 * @param[in] context Pointer to the SNMP agent context
 * @param[in] oid Object identifier
 * @param[in] oidLen Length of the OID
 * @return Pointer the MIB object descriptor
 **/

const MibObject *snmpFindMibObject(SnmpAgentContext *context,
   const uint8_t *oid, size_t oidLen)
{
   uint_t i;
   uint_t j;
   const MibObject *object;

   //Loop through MIBs
   for(i = 0; i < context->mibModuleCount; i++)
   {
      //Point the first object of the MIB
      object = context->mibModule[i]->objects;

      //Loop through objects
      for(j = 0; j < context->mibModule[i]->numObjects; j++)
      {
         //Scalar or tabular object?
         if(object->getNext == NULL)
         {
            //Check the length of the OID
            if(oidLen == (object->oidLen + 1))
            {
               //Compare object names
               if(!memcmp(oid, object->oid, object->oidLen))
               {
                  //The instance sub-identifier shall be 0 for scalar objects
                  if(oid[oidLen - 1] == 0)
                  {
                     //Return a pointer to the matching object
                     return object;
                  }
               }
            }
         }
         else
         {
            //Check the length of the OID
            if(oidLen > object->oidLen)
            {
               //Compare object identifiers
               if(!memcmp(oid, object->oid, object->oidLen))
               {
                  //Return a pointer to the matching object
                  return object;
               }
            }
         }

         //Point to the next object in the MIB
         object++;
      }
   }

   //No matching object in MIBs...
   return NULL;
}

#endif
