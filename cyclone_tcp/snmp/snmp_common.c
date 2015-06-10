/**
 * @file snmp_common.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL SNMP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "snmp/snmp_agent.h"
#include "snmp/snmp_common.h"
#include "crypto.h"
#include "asn1.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (SNMP_AGENT_SUPPORT == ENABLED)


/**
 * @brief Encode a 32-bit signed integer
 * @param[in] value Integer value
 * @param[out] dest Buffer where to encode the integer
 * @param[out] length Total number of bytes that have been written
 * @return Error code
 **/

error_t snmpEncodeInt32(int32_t value, uint8_t *dest, size_t *length)
{
   size_t i;
   size_t j;
   uint8_t *src;

   //Check parameters
   if(dest == NULL || length == NULL)
      return ERROR_INVALID_PARAMETER;

   //The integer is encoded MSB first
   value = htobe32(value);
   //Cast the integer to byte array
   src = (uint8_t *) &value;

   //An integer value is always encoded in the smallest possible number of octets
   for(i = 0; i < 3; i++)
   {
      //The upper 9 bits shall not have the same value (all 0 or all 1)
      if((src[i] != 0x00 || (src[i + 1] & 0x80) != 0x00) &&
         (src[i] != 0xFF || (src[i + 1] & 0x80) != 0x80))
      {
         break;
      }
   }

   //Point to the beginning of the output buffer
   j = 0;

   //Copy integer value
   while(i < 4)
      dest[j++] = src[i++];

   //Total number of bytes that have been written
   *length = j;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Encode a 32-bit unsigned integer
 * @param[in] value Integer value
 * @param[out] dest Buffer where to encode the integer
 * @param[out] length Total number of bytes that have been written
 * @return Error code
 **/

error_t snmpEncodeUnsignedInt32(uint32_t value, uint8_t *dest, size_t *length)
{
   size_t i;
   size_t j;
   uint8_t *src;

   //Check parameters
   if(dest == NULL || length == NULL)
      return ERROR_INVALID_PARAMETER;

   //The integer is encoded MSB first
   value = htobe32(value);
   //Cast the integer to byte array
   src = (uint8_t *) &value;

   //An integer value is always encoded in the smallest possible number of octets
   for(i = 0; i < 3; i++)
   {
      //Check the upper 8 bits
      if(src[i] != 0x00)
         break;
   }

   //Point to the beginning of the output buffer
   j = 0;

   //Check the most significant bit
   if(src[i] & 0x80)
      dest[j++] = 0;

   //Copy integer value
   while(i < 4)
      dest[j++] = src[i++];

   //Total number of bytes that have been written
   *length = j;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Encode a 64-bit unsigned integer
 * @param[in] value Integer value
 * @param[out] dest Buffer where to encode the integer
 * @param[out] length Total number of bytes that have been written
 * @return Error code
 **/

error_t snmpEncodeUnsignedInt64(uint64_t value, uint8_t *dest, size_t *length)
{
   size_t i;
   size_t j;
   uint8_t *src;

   //Check parameters
   if(dest == NULL || length == NULL)
      return ERROR_INVALID_PARAMETER;

   //The integer is encoded MSB first
   value = htobe32(value);
   //Cast the integer to byte array
   src = (uint8_t *) &value;

   //An integer value is always encoded in the smallest possible number of octets
   for(i = 0; i < 7; i++)
   {
      //Check the upper 8 bits
      if(src[i] != 0x00)
         break;
   }

   //Point to the beginning of the output buffer
   j = 0;

   //Check the most significant bit
   if(src[i] & 0x80)
      dest[j++] = 0;

   //Copy integer value
   while(i < 8)
      dest[j++] = src[i++];

   //Total number of bytes that have been written
   *length = j;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Decode a 32-bit signed integer
 * @param[in] src Buffer that contains the encoded value
 * @param[in] length Number of bytes to be processed
 * @param[out] value Resulting integer value
 * @return Error code
 **/

error_t snmpDecodeInt32(const uint8_t *src, size_t length, int32_t *value)
{
   size_t i;

   //Check parameters
   if(src == NULL || value == NULL)
      return ERROR_INVALID_PARAMETER;
   if(length < 1)
      return ERROR_INVALID_PARAMETER;

   //The contents octets shall be a two's complement binary
   //number equal to the integer value
   *value = (src[0] & 0x80) ? -1 : 0;

   //Process contents octets
   for(i = 0; i < length; i++)
   {
      //Rotate left operation
      *value <<= 8;
      //Reconstruct integer value
      *value |= src[i];
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Decode a 32-bit unsigned integer
 * @param[in] src Buffer that contains the encoded value
 * @param[in] length Number of bytes to be processed
 * @param[out] value Resulting integer value
 * @return Error code
 **/

error_t snmpDecodeUnsignedInt32(const uint8_t *src, size_t length, uint32_t *value)
{
   size_t i;

   //Check parameters
   if(src == NULL || value == NULL)
      return ERROR_INVALID_PARAMETER;
   if(length < 1)
      return ERROR_INVALID_PARAMETER;

   //Only accept non-negative numbers
   if(src[0] & 0x80)
      return ERROR_FAILURE;

   //Initialize integer value
   *value = 0;

   //Process contents octets
   for(i = 0; i < length; i++)
   {
      //Rotate left operation
      *value <<= 8;
      //Reconstruct integer value
      *value |= src[i];
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Decode a 64-bit unsigned integer
 * @param[in] src Buffer that contains the encoded value
 * @param[in] length Number of bytes to be processed
 * @param[out] value Resulting integer value
 * @return Error code
 **/

error_t snmpDecodeUnsignedInt64(const uint8_t *src, size_t length, uint64_t *value)
{
   size_t i;

   //Check parameters
   if(src == NULL || value == NULL)
      return ERROR_INVALID_PARAMETER;
   if(length < 1)
      return ERROR_INVALID_PARAMETER;

   //Only accept non-negative numbers
   if(src[0] & 0x80)
      return ERROR_FAILURE;

   //Initialize integer value
   *value = 0;

   //Process contents octets
   for(i = 0; i < length; i++)
   {
      //Rotate left operation
      *value <<= 8;
      //Reconstruct integer value
      *value |= src[i];
   }

   //Successful processing
   return NO_ERROR;
}

#endif
