/**
 * @file oid.c
 * @brief OID (Object Identifier)
 *
 * @section License
 *
 * Copyright (C) 2010-2015 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneCrypto Open.
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
#define TRACE_LEVEL CRYPTO_TRACE_LEVEL

//Dependencies
#include "crypto.h"
#include "oid.h"
#include "debug.h"


/**
 * @brief Compare object identifiers
 * @param[in] oid1 Pointer the the first OID
 * @param[in] n1 Size of the first OID
 * @param[in] oid2 Pointer the the second OID
 * @param[in] n2 Size of the second OID
 * @return Comparison result
 * @retval 0 Objects identifiers are equal
 * @retval -1 The first OID lexicographically precedes the second OID
 * @retval 1 The second OID lexicographically precedes the first OID
 **/

int_t oidComp(const uint8_t *oid1, size_t n1, const uint8_t *oid2, size_t n2)
{
   size_t i;

   //Perform lexicographical comparison
   for(i = 0; i < n1 && i < n2; i++)
   {
      //Compare current byte
      if(oid1[i] < oid2[i])
         return -1;
      else if(oid1[i] > oid2[i])
         return 1;
   }

   //Compare length
   if(n1 < n2)
      return -1;
   else if(n1 > n2)
      return 1;

   //Object identifiers are equal
   return 0;
}


/**
 * @brief Display an object identifier
 * @param[in] oid Pointer to the object identifier
 * @param[in] length Length of the OID, in bytes
 **/

void oidDump(const uint8_t *oid, size_t length)
{
   size_t i;
   uint32_t value;

   //Check
   if(length > 0)
   {
      //Display the first 2 bytes
      TRACE_DEBUG("%" PRIu8 ".%" PRIu8 "", oid[0] / 40, oid[0] % 40);

      //Display the rest of the OID
      for(i = 1, value = 0; i < length; i++)
      {
         //Update the current value
         value = (value << 7) | (oid[i] & 0x7F);

         //Bit b8 is set to zero to indicate the last byte
         if(!(oid[i] & 0x80))
         {
            //Dump current value
            TRACE_DEBUG(".%" PRIu32, value);
            //Prepare to decode the next value
            value = 0;
         }
      }
   }
}
