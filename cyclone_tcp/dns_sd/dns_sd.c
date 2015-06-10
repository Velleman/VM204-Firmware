/**
 * @file dns_sd.c
 * @brief DNS-SD (DNS-Based Service Discovery)
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
#define TRACE_LEVEL DNS_SD_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "dns_sd/dns_sd.h"
#include "mdns/mdns_common.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (DNS_SD_SUPPORT == ENABLED)


/**
 * @brief DNS-DS related initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t dnsSdInit(NetInterface *interface)
{
   //Clear instance name
   strcpy(interface->instanceName, "");
   //The list of registered services is empty
   interface->numServices = 0;

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief Set instance name
 * @param[in] interface Pointer to the desired network interface
 * @param[in] name NULL-terminated string that contains the instance name
 * @return Error code
 **/

error_t dnsSdSetInstanceName(NetInterface *interface, const char_t *name)
{
   size_t n;

   //Check parameters
   if(interface == NULL || name == NULL)
      return ERROR_INVALID_PARAMETER;

   //Get the length of the string
   n = strlen(name);
   //Limit the number of characters to be copied
   n = MIN(n, DNS_SD_MAX_INSTANCE_LEN - 1);

   //Set instance name
   strncpy(interface->instanceName, name, n);
   //Properly terminate the string with a NULL character
   interface->instanceName[n] = '\0';

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Register DNS-SD services
 * @param[in] interface Pointer to the desired network interface
 * @param[in] services List of services to be registered
 * @param[in] size Number of services in the list
 * @return Error code
 **/

error_t dnsSdRegisterServices(NetInterface *interface,
   const DnsSdService *services, uint_t size)
{
   //Check parameters
   if(interface == NULL)
      return ERROR_INVALID_PARAMETER;
   if(services == NULL && size != 0)
      return ERROR_INVALID_PARAMETER;

   //Register DNS-SD services
   interface->services = services;
   interface->numServices = size;

   //Services successfully registred
   return NO_ERROR;
}


/**
 * @brief Add PTR record to a DNS message
 * @param[in] interface Underlying network interface
 * @param[in] service Pointer to a DNS-SD service
 * @param[in] serviceTypeEnum This flag tells whether the PTR record is sent
 *   in response to a service type enumeration meta-query
 * @param[in,out] message Pointer to the DNS message
 * @param[in,out] length Actual length of the DNS message
 * @return Error code
 **/

error_t dnsSdAddPtrResourceRecord(NetInterface *interface, const DnsSdService *service,
   bool_t serviceTypeEnum, DnsHeader *message, size_t *length)
{
   size_t n;
   size_t offset;
   DnsResourceRecord *resourceRecord;

   //Set the position to the end of the buffer
   offset = *length;

   //Check whether the PTR record is sent in response to a
   //service type enumeration meta-query
   if(serviceTypeEnum)
   {
      //The first pass calculates the length of the DNS encoded service name
      n = mdnsEncodeName("", "_services._dns-sd._udp", ".local", NULL);

      //Check the length of the resulting mDNS message
      if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
         return ERROR_MESSAGE_TOO_LONG;

      //The second pass encodes the service name using the DNS name notation
      offset += mdnsEncodeName("", "_services._dns-sd._udp",
         ".local", (uint8_t *) message + offset);
   }
   else
   {
      //The first pass calculates the length of the DNS encoded service name
      n = mdnsEncodeName("", service->name, ".local", NULL);

      //Check the length of the resulting mDNS message
      if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
         return ERROR_MESSAGE_TOO_LONG;

      //Encode the service name using the DNS name notation
      offset += mdnsEncodeName("", service->name,
         ".local", (uint8_t *) message + offset);
   }

   //Consider the length of the resource record itself
   if((offset + sizeof(DnsResourceRecord)) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //Point to the corresponding resource record
   resourceRecord = DNS_GET_RESOURCE_RECORD(message, offset);

   //Fill in resource record
   resourceRecord->rtype = HTONS(DNS_RR_TYPE_PTR);
   resourceRecord->rclass = HTONS(DNS_RR_CLASS_IN);
   resourceRecord->ttl = HTONL(DNS_SD_DEFAULT_RESOURCE_RECORD_TTL);

   //Advance write index
   offset += sizeof(DnsResourceRecord);

   //Check whether the PTR record is sent in response to a
   //service type enumeration meta-query
   if(serviceTypeEnum)
   {
      //The first pass calculates the length of the DNS encoded service name
      n = mdnsEncodeName("", service->name, ".local", NULL);

      //Check the length of the resulting mDNS message
      if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
         return ERROR_MESSAGE_TOO_LONG;

      //The second pass encodes the service name using DNS notation
      n = mdnsEncodeName("", service->name,
         ".local", resourceRecord->rdata);
   }
   else
   {
      //The first pass calculates the length of the DNS encoded instance name
      n = mdnsEncodeName(interface->instanceName, service->name, ".local", NULL);

      //Check the length of the resulting mDNS message
      if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
         return ERROR_MESSAGE_TOO_LONG;

      //The second pass encodes the instance name using DNS notation
      n = mdnsEncodeName(interface->instanceName,
         service->name, ".local", resourceRecord->rdata);
   }

   //Convert length field to network byte order
   resourceRecord->rdlength = htons(n);

   //Number of resource records in the answer section
   message->ancount++;

   //Update the length of the DNS message
   *length = offset + n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Add SRV record to a DNS message
 * @param[in] interface Underlying network interface
 * @param[in] service Pointer to a DNS-SD service
 * @param[in,out] message Pointer to the DNS message
 * @param[in,out] length Actual length of the DNS message
 * @return Error code
 **/

error_t dnsSdAddSrvResourceRecord(NetInterface *interface,
   const DnsSdService *service, DnsHeader *message, size_t *length)
{
   size_t n;
   size_t offset;
   DnsSrvResourceRecord *resourceRecord;

   //Set the position to the end of the buffer
   offset = *length;

   //The first pass calculates the length of the DNS encoded instance name
   n = mdnsEncodeName(interface->instanceName, service->name, ".local", NULL);

   //Check the length of the resulting mDNS message
   if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //The second pass encodes the instance name using DNS notation
   offset += mdnsEncodeName(interface->instanceName,
      service->name, ".local", (uint8_t *) message + offset);

   //Consider the length of the resource record itself
   if((offset + sizeof(DnsSrvResourceRecord)) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //Point to the corresponding resource record
   resourceRecord = (DnsSrvResourceRecord *) DNS_GET_RESOURCE_RECORD(message, offset);

   //Fill in resource record
   resourceRecord->rtype = HTONS(DNS_RR_TYPE_SRV);
   resourceRecord->rclass = HTONS(DNS_RR_CLASS_IN);
   resourceRecord->ttl = HTONL(DNS_SD_DEFAULT_RESOURCE_RECORD_TTL);
   resourceRecord->priority = htons(service->priority);
   resourceRecord->weight = htons(service->weight);
   resourceRecord->port = htons(service->port);

   //Advance write index
   offset += sizeof(DnsSrvResourceRecord);

   //The first pass calculates the length of the DNS encoded target name
   n = mdnsEncodeName("", interface->hostname, ".local", NULL);

   //Check the length of the resulting mDNS message
   if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //The second pass encodes the target name using DNS notation
   n = mdnsEncodeName("", interface->hostname,
      ".local", resourceRecord->target);

   //Calculate data length
   resourceRecord->rdlength = htons(sizeof(DnsSrvResourceRecord) -
      sizeof(DnsResourceRecord) + n);

   //Number of resource records in the answer section
   message->ancount++;

   //Update the length of the DNS message
   *length = offset + n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Add TXT record to a DNS message
 * @param[in] interface Underlying network interface
 * @param[in] service Pointer to a DNS-SD service
 * @param[in,out] message Pointer to the DNS message
 * @param[in,out] length Actual length of the DNS message
 * @return Error code
 **/

error_t dnsSdAddTxtResourceRecord(NetInterface *interface,
   const DnsSdService *service, DnsHeader *message, size_t *length)
{
   size_t i;
   size_t j;
   size_t k;
   size_t n;
   size_t offset;
   DnsResourceRecord *resourceRecord;

   //Set the position to the end of the buffer
   offset = *length;

   //The first pass calculates the length of the DNS encoded instance name
   n = mdnsEncodeName(interface->instanceName, service->name, ".local", NULL);

   //Check the length of the resulting mDNS message
   if((offset + n) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //The second pass encodes the instance name using DNS notation
   offset += mdnsEncodeName(interface->instanceName,
      service->name, ".local", (uint8_t *) message + offset);

   //Consider the length of the resource record itself
   if((offset + sizeof(DnsResourceRecord)) > MDNS_MESSAGE_MAX_SIZE)
      return ERROR_MESSAGE_TOO_LONG;

   //Point to the corresponding resource record
   resourceRecord = DNS_GET_RESOURCE_RECORD(message, offset);

   //Fill in resource record
   resourceRecord->rtype = HTONS(DNS_RR_TYPE_TXT);
   resourceRecord->rclass = HTONS(DNS_RR_CLASS_IN);
   resourceRecord->ttl = HTONL(DNS_SD_DEFAULT_RESOURCE_RECORD_TTL);
   resourceRecord->rdlength = 0;

   //Advance write index
   offset += sizeof(DnsResourceRecord);

   //Point to the beginning of the information string
   i = 0;
   j = 0;

   //Point to the beginning of the resulting TXT record data
   k = 0;

   //Format TXT record
   while(1)
   {
      //End of text data?
      if(service->info[i] == '\0' || service->info[i] == ';')
      {
         //Calculate the length of the text data
         n = MIN(i - j, 255);

         //Check the length of the resulting mDNS message
         if((offset + resourceRecord->rdlength + n + 1) > MDNS_MESSAGE_MAX_SIZE)
            return ERROR_MESSAGE_TOO_LONG;

         //Write length field
         resourceRecord->rdata[k] = n;
         //Write text data
         memcpy(resourceRecord->rdata + k + 1, service->info + j, n);

         //Jump to the next text data
         j = i + 1;
         //Advance write index
         k += n + 1;

         //Update the length of the TXT record
         resourceRecord->rdlength += n + 1;

         //End of string detected?
         if(service->info[i] == '\0')
            break;
      }

      //Advance read index
      i++;
   }

   //Empty TXT record?
   if(!resourceRecord->rdlength)
   {
      //Sanity check
      if((offset + 1) > MDNS_MESSAGE_MAX_SIZE)
         return ERROR_MESSAGE_TOO_LONG;

      //An empty TXT record shall contain a single zero byte
      resourceRecord->rdata[0] = 0;
      resourceRecord->rdlength = 1;
   }

   //Get the length of the TXT record
   n = resourceRecord->rdlength;
   //Convert length field to network byte order
   resourceRecord->rdlength = htons(n);

   //Number of resource records in the answer section
   message->ancount++;

   //Update the length of the DNS message
   *length = offset + n;

   //Successful processing
   return NO_ERROR;
}

#endif
