/**
 * @file dns_common.c
 * @brief Common DNS routines
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
#define TRACE_LEVEL DNS_TRACE_LEVEL

//Dependencies
#include <string.h>
#include <ctype.h>
#include "core/net.h"
#include "dns/dns_client.h"
#include "dns/dns_common.h"
#include "mdns/mdns_client.h"
#include "mdns/mdns_responder.h"
#include "mdns/mdns_common.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (DNS_CLIENT_SUPPORT == ENABLED || MDNS_CLIENT_SUPPORT == ENABLED || \
   MDNS_RESPONDER_SUPPORT == ENABLED)


/**
 * @brief Encode a domain name using the DNS name notation
 * @param[in] src Pointer to the domain name to encode
 * @param[out] dest Pointer to the encoded domain name (optional parameter)
 * @return Length of the encoded domain name
 **/

size_t dnsEncodeName(const char_t *src, uint8_t *dest)
{
   uint_t i = 0;
   size_t length = 0;

   //Parse input name
   while(1)
   {
      //End of string detected?
      if(src[i] == '\0')
      {
         //Check label length
         if(i < 1 || i > DNS_LABEL_MAX_SIZE)
            return 0;

         //Save label length
         if(dest != NULL)
         {
            dest[0] = i;
            dest[i + 1] = 0;
         }

         //Adjust the length of the resulting string
         length += i + 2;

         //Stop parsing the input string
         return length;
      }
      //Separator detected?
      else if(src[i] == '.')
      {
         //Check label length
         if(i < 1 || i > DNS_LABEL_MAX_SIZE)
            return 0;

         //Save label length
         if(dest != NULL)
            dest[0] = i;

         //Adjust the length of the resulting string
         length += i + 1;

         //Advance write pointer
         if(dest != NULL)
            dest += i + 1;

         //Prepare to decode the next label
         src += i + 1;
         i = 0;
      }
      //Valid character detected?
      else if(isalnum((uint8_t) src[i]) || src[i] == '-' || src[i] == '_' || src[i] == ' ')
      {
         //Copy current character
         if(dest != NULL)
            dest[i + 1] = src[i];

         //Point to the next character
         i++;
      }
      //Invalid character detected?
      else
      {
         //Stop parsing the input string
         return 0;
      }
   }
}


/**
 * @brief Decode a domain name that uses the DNS name encoding
 * @param[in] message Pointer to the DNS message
 * @param[in] length Length of the DNS message
 * @param[in] pos Offset of the name to decode
 * @param[out] dest Pointer to the decoded name (optional)
 * @param[in] level Current level of recursion
 * @return The position of the resource record that immediately follows the domain name
 **/

size_t dnsParseName(const DnsHeader *message,
   size_t length, size_t pos, char_t *dest, uint_t level)
{
   size_t n;
   size_t pointer;
   uint8_t *src;

   //Recursion limit exceeded?
   if(level >= DNS_NAME_MAX_RECURSION)
      return 0;

   //Cast the input DNS message to byte array
   src = (uint8_t *) message;

   //Parse encoded domain name
   while(pos < length)
   {
      //End marker found?
      if(src[pos] == 0)
      {
         //Properly terminate the string
         if(dest != NULL)
            *dest = '\0';

         //Return the position of the resource record that
         //is immediately following the domain name
         return (pos + 1);
      }
      //Compression tag found?
      if(src[pos] >= DNS_COMPRESSION_TAG)
      {
         //Malformed DNS message?
         if((pos + 1) >= length)
            return 0;

         //Read the most significant byte of the pointer
         pointer = (src[pos] & ~DNS_COMPRESSION_TAG) << 8;
         //Read the least significant byte of the pointer
         pointer |= src[pos + 1];

         //Decode the remaining part of the domain name
         if(!dnsParseName(message, length, pointer, dest, level + 1))
         {
            //Domain name decoding failed
            return 0;
         }

         //Return the position of the resource record that
         //is immediately following the domain name
         return (pos + 2);
      }
      //Valid label length?
      else if(src[pos] < DNS_LABEL_MAX_SIZE)
      {
         //Get the length of the current label
         n = src[pos++];

         //Malformed DNS message?
         if((pos + n) > length)
            return 0;

         //The last parameter is optional
         if(dest != NULL)
         {
            //Copy current label
            memcpy(dest, src + pos, n);

            //Advance read pointer
            pos += n;
            //Advance write pointer
            dest += n;

            //Append a separator if necessary
            if(pos < length && src[pos] != '\0')
               *(dest++) = '.';
         }
         else
         {
            //Advance read pointer
            pos += n;
         }
      }
      //Invalid label length?
      else
      {
         //Properly terminate the string
         if(dest != NULL)
            *dest = '\0';
         //Domain name decoding failed
         return 0;
      }
   }

   //Domain name decoding failed
   return 0;
}


/**
 * @brief Compare domain names
 * @param[in] message Pointer to the DNS message
 * @param[in] length Length of the DNS message
 * @param[in] pos Offset of the encoded domain name
 * @param[in] name NULL-terminated string that holds a domain name
 * @param[in] level Current level of recursion
 * @return TRUE if the domain names match, else FALSE
 **/

bool_t dnsCompareName(const DnsHeader *message,
   size_t length, size_t pos, const char_t *name, uint_t level)
{
   size_t n;
   size_t pointer;
   uint8_t *src;

   //Recursion limit exceeded?
   if(level >= DNS_NAME_MAX_RECURSION)
      return FALSE;

   //Cast the input DNS message to byte array
   src = (uint8_t *) message;

   //Parse encoded domain name
   while(pos < length)
   {
      //End marker found?
      if(src[pos] == 0)
      {
         //Return comparison result
         return (*name == '\0') ? TRUE : FALSE;
      }
      //Compression tag found?
      if(src[pos] >= DNS_COMPRESSION_TAG)
      {
         //Malformed DNS message?
         if((pos + 1) >= length)
            return FALSE;

         //Read the most significant byte of the pointer
         pointer = (src[pos] & ~DNS_COMPRESSION_TAG) << 8;
         //Read the least significant byte of the pointer
         pointer |= src[pos + 1];

         //Compare the remaining part of the domain name
         return dnsCompareName(message, length, pointer, name, level + 1);
      }
      //Valid label length?
      else if(src[pos] < DNS_LABEL_MAX_SIZE)
      {
         //Get the length of the current label
         n = src[pos++];

         //Malformed DNS message?
         if((pos + n) > length)
            return FALSE;
         //Compare current label
         if(strncasecmp((char_t *) src + pos, name, n))
            return FALSE;

         //Advance data pointer
         pos += n;
         name += n;

         //Any separator?
         if(*name == '.')
            name++;
      }
      //Invalid label length?
      else
      {
         //Comparison failed
         return FALSE;
      }
   }

   //Comparison failed
   return FALSE;
}

#endif
