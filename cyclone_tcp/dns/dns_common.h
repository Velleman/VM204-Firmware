/**
 * @file dns_common.h
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

#ifndef _DNS_COMMON_H
#define _DNS_COMMON_H

//Dependencies
#include "core/net.h"

//Maximum recursion limit when parsing domain names
#ifndef DNS_NAME_MAX_RECURSION
   #define DNS_NAME_MAX_RECURSION 4
#elif (DNS_NAME_MAX_RECURSION < 1 || DNS_NAME_MAX_RECURSION > 8)
   #error DNS_NAME_MAX_RECURSION parameter is not valid
#endif

//Maximum size of DNS messages
#define DNS_MESSAGE_MAX_SIZE 512
//Maximum size of names
#define DNS_NAME_MAX_SIZE 255
//Maximum size of labels
#define DNS_LABEL_MAX_SIZE 63

//DNS port number
#define DNS_PORT 53

//Label compression tag
#define DNS_COMPRESSION_TAG 0xC0

//Macro definition
#define DNS_GET_QUESTION(message, offset) (DnsQuestion *) ((uint8_t *) message + offset)
#define DNS_GET_RESOURCE_RECORD(message, offset) (DnsResourceRecord *) ((uint8_t *) message + offset)


/**
 * @brief DNS opcodes
 **/

typedef enum
{
   DNS_OPCODE_QUERY         = 0,
   DNS_OPCODE_INVERSE_QUERY = 1,
   DNS_OPCODE_STATUS        = 2,
   DNS_OPCODE_NOTIFY        = 4,
   DNS_OPCODE_UPDATE        = 5
} DnsOpcode;


/**
 * @brief DNS return codes
 **/

typedef enum
{
   DNS_RCODE_NO_ERROR        = 0,
   DNS_RCODE_FORMAT_ERROR    = 1,
   DNS_RCODE_SERVER_FAILURE  = 2,
   DNS_RCODE_NAME_ERROR      = 3,
   DNS_RCODE_NOT_IMPLEMENTED = 4,
   DNS_RCODE_QUERY_REFUSED   = 5
}DnsReturnCode;


/**
 * @brief DNS resource record types
 **/

typedef enum
{
   DNS_RR_TYPE_A     = 1,  ///<Host address
   DNS_RR_TYPE_NS    = 2,  ///<Authoritative name server
   DNS_RR_TYPE_CNAME = 5,  ///<Canonical name for an alias
   DNS_RR_TYPE_PTR   = 12, ///<Domain name pointer
   DNS_RR_TYPE_HINFO = 13, ///<Host information
   DNS_RR_TYPE_MX    = 15, ///<Mail exchange
   DNS_RR_TYPE_TXT   = 16, ///<Text strings
   DNS_RR_TYPE_AAAA  = 28, ///<IPv6 address
   DNS_RR_TYPE_NB    = 32, ///<NetBIOS name service
   DNS_RR_TYPE_SRV   = 33, ///<Server selection
   DNS_RR_TYPE_ANY   = 255
} DnsResourceRecordType;


/**
 * @brief DNS resource record classes
 **/

typedef enum
{
   DNS_RR_CLASS_IN  = 1, ///<Internet
   DNS_RR_CLASS_CH  = 3, ///<Chaos
   DNS_RR_CLASS_HS  = 4, ///<Hesiod
   DNS_RR_CLASS_ANY = 255
} DnsResourceRecordClass;


//Win32 compiler?
#if defined(_WIN32)
   #pragma pack(push, 1)
#endif


/**
 * @brief DNS message header
 **/

typedef __start_packed struct
{
   uint16_t id;         //0-1
#ifdef _BIG_ENDIAN
   uint16_t qr : 1;     //2
   uint16_t opcode : 4;
   uint16_t aa : 1;
   uint16_t tc : 1;
   uint16_t rd : 1;
   uint16_t ra : 1;     //3
   uint16_t z : 3;
   uint16_t rcode : 4;
#else
   uint16_t rd : 1;     //2
   uint16_t tc : 1;
   uint16_t aa : 1;
   uint16_t opcode : 4;
   uint16_t qr : 1;
   uint16_t rcode : 4;  //3
   uint16_t z : 3;
   uint16_t ra : 1;
#endif
   uint16_t qdcount;    //4-5
   uint16_t ancount;    //6-7
   uint16_t nscount;    //8-9
   uint16_t arcount;    //10-11
   uint8_t questions[]; //12
} __end_packed DnsHeader;


/**
 * @brief Question format
 **/

typedef __start_packed struct
{
   uint16_t qtype;
   uint16_t qclass;
} __end_packed DnsQuestion;


/**
 * @brief Resource record format
 **/

typedef __start_packed struct
{
   uint16_t rtype;    //0-1
   uint16_t rclass;   //2-3
   uint32_t ttl;      //4-7
   uint16_t rdlength; //8-9
   uint8_t rdata[];   //10
} __end_packed DnsResourceRecord;


/**
 * @brief SRV resource record format
 **/

typedef __start_packed struct
{
   uint16_t rtype;    //0-1
   uint16_t rclass;   //2-3
   uint32_t ttl;      //4-7
   uint16_t rdlength; //8-9
   uint16_t priority; //10-11
   uint16_t weight;   //12-13
   uint16_t port;     //14-15
   uint8_t target[];  //16
} __end_packed DnsSrvResourceRecord;


//Win32 compiler?
#if defined(_WIN32)
   #pragma pack(pop)
#endif


//DNS related functions
size_t dnsEncodeName(const char_t *src, uint8_t *dest);

size_t dnsParseName(const DnsHeader *message,
   size_t length, size_t pos, char_t *dest, uint_t level);

bool_t dnsCompareName(const DnsHeader *message,
   size_t length, size_t pos, const char_t *name, uint_t level);

#endif
