/**
 * @file mib2_impl.c
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

//Mutex preventing simultaneous access to the MIB-II base
static OsMutex mib2Mutex;


/**
 * @brief MIB-II module initialization
 * @return Error code
 **/

error_t mib2Init(void)
{
   //Debug message
   TRACE_INFO("Initializing standard MIB-II base...\r\n");

   //Clear MIB-II base
   memset(&mib2Base, 0, sizeof(mib2Base));

   //sysDescr object
   strcpy(mib2Base.sysGroup.sysDescr, "System Description");
   mib2Base.sysGroup.sysDescrLen = strlen(mib2Base.sysGroup.sysDescr);

   //Create a mutex to prevent simultaneous access to the MIB-II base
   if(!osCreateMutex(&mib2Mutex))
   {
      //Failed to create mutex
      return ERROR_OUT_OF_RESOURCES;
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Lock MIB-II base
 **/

void mib2Lock(void)
{
   //Enter critical section
   osAcquireMutex(&mib2Mutex);
}


/**
 * @brief Unlock MIB-II base
 **/

void mib2Unlock(void)
{
   //Leave critical section
   osReleaseMutex(&mib2Mutex);
}


/**
 * @brief Get sysUpTime object value
 * @param[in] object Pointer to the MIB object descriptor
 * @param[in] oid Object identifier (object name and instance sub-identifier)
 * @param[in] oidLen Length of the OID, in bytes
 * @param[out] value Object value
 * @param[in,out] valueLen Length of the object value, in bytes
 * @return Error code
 **/

error_t mib2GetSysUpTime(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   //Get object value
   value->timeTicks = osGetSystemTime() / 10;
   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Get ifEntry object value
 * @param[in] object Pointer to the MIB object descriptor
 * @param[in] oid Object identifier (object name and instance sub-identifier)
 * @param[in] oidLen Length of the OID, in bytes
 * @param[out] value Object value
 * @param[in,out] valueLen Length of the object value, in bytes
 * @return Error code
 **/

error_t mib2GetIfEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   size_t n;
   uint_t index;
   Mib2IfEntry *entry;

   //Check OID length
   if(oidLen != (object->oidLen + 1))
      return ERROR_INSTANCE_NOT_FOUND;

   //Get index
   index = oid[oidLen - 1];

   //Check index range
   if(index < 1 || index > NET_INTERFACE_COUNT)
      return ERROR_INSTANCE_NOT_FOUND;

   //Point to the interface table entry
   entry = &mib2Base.ifGroup.ifTable[index - 1];

   //ifIndex object?
   if(!strcmp(object->name, "ifIndex"))
   {
      //Get object value
      value->integer = entry->ifIndex;
   }
   //ifDescr object?
   else if(!strcmp(object->name, "ifDescr"))
   {
      //Retrieve the length of the object
      n = entry->ifDescrLen;

      //Make sure the buffer is large enough to hold the entire object
      if(*valueLen < n)
         return ERROR_BUFFER_OVERFLOW;

      //Copy object value
      memcpy(value->octetString, entry->ifDescr, n);
      //Return object length
      *valueLen = n;
   }
   //ifType object?
   else if(!strcmp(object->name, "ifType"))
   {
      //Get object value
      value->integer = entry->ifType;
   }
   //ifMtu object?
   else if(!strcmp(object->name, "ifMtu"))
   {
      //Get object value
      value->integer = entry->ifMtu;
   }
   //ifSpeed object?
   else if(!strcmp(object->name, "ifSpeed"))
   {
      //Get object value
      value->gauge32 = entry->ifSpeed;
   }
   //ifPhysAddress object?
   else if(!strcmp(object->name, "ifPhysAddress"))
   {
      //Retrieve the length of the object
      n = entry->ifPhysAddressLen;

      //Make sure the buffer is large enough to hold the entire object
      if(*valueLen < n)
         return ERROR_BUFFER_OVERFLOW;

      //Copy object value
      memcpy(value->octetString, entry->ifPhysAddress, n);
      //Return object length
      *valueLen = n;
   }
   //ifAdminStatus object?
   else if(!strcmp(object->name, "ifAdminStatus"))
   {
      //Get object value
      value->integer = entry->ifAdminStatus;
   }
   //ifOperStatus object?
   else if(!strcmp(object->name, "ifOperStatus"))
   {
      //Get object value
      value->integer = entry->ifOperStatus;
   }
   //ifLastChange object?
   else if(!strcmp(object->name, "ifLastChange"))
   {
      //Get object value
      value->timeTicks = entry->ifLastChange;
   }
   //ifInOctets object?
   else if(!strcmp(object->name, "ifInOctets"))
   {
      //Get object value
      value->counter32 = entry->ifInOctets;
   }
   //ifInUcastPkts object?
   else if(!strcmp(object->name, "ifInUcastPkts"))
   {
      //Get object value
      value->counter32 = entry->ifInUcastPkts;
   }
   //ifInNUcastPkts object?
   else if(!strcmp(object->name, "ifInNUcastPkts"))
   {
      //Get object value
      value->counter32 = entry->ifInNUcastPkts;
   }
   //ifInDiscards object?
   else if(!strcmp(object->name, "ifInDiscards"))
   {
      //Get object value
      value->counter32 = entry->ifInDiscards;
   }
   //ifInErrors object?
   else if(!strcmp(object->name, "ifInErrors"))
   {
      //Get object value
      value->counter32 = entry->ifInErrors;
   }
   //ifInUnknownProtos object?
   else if(!strcmp(object->name, "ifInUnknownProtos"))
   {
      //Get object value
      value->counter32 = entry->ifInUnknownProtos;
   }
   //ifOutOctets object?
   else if(!strcmp(object->name, "ifOutOctets"))
   {
      //Get object value
      value->counter32 = entry->ifOutOctets;
   }
   //ifOutUcastPkts object?
   else if(!strcmp(object->name, "ifOutUcastPkts"))
   {
      //Get object value
      value->counter32 = entry->ifOutUcastPkts;
   }
   //ifOutNUcastPkts object?
   else if(!strcmp(object->name, "ifOutNUcastPkts"))
   {
      //Get object value
      value->counter32 = entry->ifOutNUcastPkts;
   }
   //ifOutDiscards object?
   else if(!strcmp(object->name, "ifOutDiscards"))
   {
      //Get object value
      value->counter32 = entry->ifOutDiscards;
   }
   //ifOutErrors object?
   else if(!strcmp(object->name, "ifOutErrors"))
   {
      //Get object value
      value->counter32 = entry->ifOutErrors;
   }
   //ifOutQLen object?
   else if(!strcmp(object->name, "ifOutQLen"))
   {
      //Get object value
      value->gauge32 = entry->ifOutQLen;
   }
   //Unknown object?
   else
   {
      //The specified object does not exist
      return ERROR_OBJECT_NOT_FOUND;
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Get next ifEntry object
 * @param[in] object Pointer to the MIB object descriptor
 * @param[in] oid Object identifier
 * @param[in] oidLen Length of the OID, in bytes
 * @param[out] nextOid OID of the next object in the base
 * @param[out] nextOidLen Length of the next object identifier, in bytes
 * @return Error code
 **/

error_t mib2GetNextIfEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, uint8_t *nextOid, size_t *nextOidLen)
{
   uint_t index;

   //Make sure the buffer is large enough to hold the entire OID
   if(*nextOidLen < (object->oidLen + 1))
      return ERROR_BUFFER_OVERFLOW;

   //Copy object identifier
   memcpy(nextOid, object->oid, object->oidLen);

   //Loop through interfaces
   for(index = 1; index <= NET_INTERFACE_COUNT; index++)
   {
      //Select instance
      nextOid[object->oidLen] = index;

      //Compare object identifiers
      if(oidComp(oid, oidLen, nextOid, object->oidLen + 1) < 0)
      {
         //Save the length of the next object identifier
         *nextOidLen = object->oidLen + 1;
         //The specified OID lexicographically precedes the name of the current object
         return NO_ERROR;
      }
   }

   //The specified OID does not lexicographically precede the name of some object
   return ERROR_OBJECT_NOT_FOUND;
}

#endif
