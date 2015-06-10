/**
 * @file dns_sd.h
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

#ifndef _DNS_SD_H
#define _DNS_SD_H

//Dependencies
#include "core/net.h"
#include "dns/dns_common.h"

//DNS-SD support
#ifndef DNS_SD_SUPPORT
   #define DNS_SD_SUPPORT DISABLED
#elif (DNS_SD_SUPPORT != ENABLED && DNS_SD_SUPPORT != DISABLED)
   #error DNS_SD_SUPPORT parameter is not valid
#endif

//Maximum length of instance name
#ifndef DNS_SD_MAX_INSTANCE_LEN
   #define DNS_SD_MAX_INSTANCE_LEN 32
#elif (DNS_SD_MAX_INSTANCE_LEN < 1)
   #error DNS_SD_MAX_INSTANCE_LEN parameter is not valid
#endif

//Default TTL value for PTR, SVR and TXT resource records
#ifndef DNS_SD_DEFAULT_RESOURCE_RECORD_TTL
   #define DNS_SD_DEFAULT_RESOURCE_RECORD_TTL 120
#elif (DNS_SD_DEFAULT_RESOURCE_RECORD_TTL < 1)
   #error DNS_SD_DEFAULT_RESOURCE_RECORD_TTL parameter is not valid
#endif


/**
 * @brief DNS-SD service descriptor
 **/

typedef struct
{
   const char_t *name; ///<Service name
   uint16_t priority;  ///<Priority
   uint16_t weight;    ///<Weight
   uint16_t port;      ///<Port number
   const char_t *info; ///<Text data
} DnsSdService;


//DNS-SD related functions
error_t dnsSdInit(NetInterface *interface);

error_t dnsSdSetInstanceName(NetInterface *interface, const char_t *name);

error_t dnsSdRegisterServices(NetInterface *interface,
   const DnsSdService *services, uint_t size);

error_t dnsSdAddPtrResourceRecord(NetInterface *interface, const DnsSdService *service,
   bool_t serviceTypeEnum, DnsHeader *message, size_t *length);

error_t dnsSdAddSrvResourceRecord(NetInterface *interface,
   const DnsSdService *service, DnsHeader *message, size_t *length);

error_t dnsSdAddTxtResourceRecord(NetInterface *interface,
   const DnsSdService *service, DnsHeader *message, size_t *length);

#endif
