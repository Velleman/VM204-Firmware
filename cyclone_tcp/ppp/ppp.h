/**
 * @file ppp.h
 * @brief PPP (Point-to-Point Protocol)
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

#ifndef _PPP_H
#define _PPP_H

//Dependencies
#include "core/net.h"

//PPP support
#ifndef PPP_SUPPORT
   #define PPP_SUPPORT DISABLED
#elif (PPP_SUPPORT != ENABLED && PPP_SUPPORT != DISABLED)
   #error PPP_SUPPORT parameter is not valid
#endif

//TX buffer size
#ifndef PPP_TX_BUFFER_SIZE
   #define PPP_TX_BUFFER_SIZE 4096
#elif (PPP_TX_BUFFER_SIZE < 3006)
   #error PPP_TX_BUFFER_SIZE parameter is not valid
#endif

//RX buffer size
#ifndef PPP_RX_BUFFER_SIZE
   #define PPP_RX_BUFFER_SIZE 8192
#elif (PPP_RX_BUFFER_SIZE < 3006)
   #error PPP_RX_BUFFER_SIZE parameter is not valid
#endif

//Maximum user name length
#ifndef PPP_MAX_USERNAME_LEN
   #define PPP_MAX_USERNAME_LEN 31
#elif (PPP_MAX_USERNAME_LEN < 7)
   #error PPP_MAX_USERNAME_LEN parameter is not valid
#endif

//Maximum password length
#ifndef PPP_MAX_PASSWORD_LEN
   #define PPP_MAX_PASSWORD_LEN 31
#elif (PPP_MAX_PASSWORD_LEN < 7)
   #error PPP_MAX_PASSWORD_LEN parameter is not valid
#endif

//PPP tick interval
#ifndef PPP_TICK_INTERVAL
   #define PPP_TICK_INTERVAL 500
#elif (PPP_TICK_INTERVAL < 100)
   #error PPP_TICK_INTERVAL parameter is not valid
#endif

//Polling interval for blocking functions
#ifndef PPP_POLLING_INTERVAL
   #define PPP_POLLING_INTERVAL 50
#elif (PPP_POLLING_INTERVAL < 1)
   #error PPP_POLLING_INTERVAL parameter is not valid
#endif

//Restart timer
#ifndef PPP_RESTART_TIMER
   #define PPP_RESTART_TIMER 3000
#elif (PPP_RESTART_TIMER < 1000)
   #error PPP_RESTART_TIMER parameter is not valid
#endif

//Maximum number of retransmissions for Configure-Requests
#ifndef PPP_MAX_CONFIGURE
   #define PPP_MAX_CONFIGURE 10
#elif (PPP_MAX_CONFIGURE < 1)
   #error PPP_MAX_CONFIGURE parameter is not valid
#endif

//Maximum number of retransmissions for Terminate-Requests
#ifndef PPP_MAX_TERMINATE
   #define PPP_MAX_TERMINATE 2
#elif (PPP_MAX_TERMINATE < 1)
   #error PPP_MAX_TERMINATE parameter is not valid
#endif

//Maximum number of Configure-Nak packets sent
#ifndef PPP_MAX_FAILURE
   #define PPP_MAX_FAILURE 5
#elif (PPP_MAX_FAILURE < 1)
   #error PPP_MAX_FAILURE parameter is not valid
#endif

//PPP special characters
#define PPP_MASK_CHAR 0x20
#define PPP_ESC_CHAR  0x7D
#define PPP_FLAG_CHAR 0x7E

//PPP default MRU
#define PPP_DEFAULT_MRU 1500
//PPP default async control character map
#define PPP_DEFAULT_ACCM 0xFFFFFFFF
//PPP default magic number
#define PPP_DEFAULT_MAGIC_NUMBER 0

//Minimum acceptable value for MRU
#define PPP_MIN_MRU 32
//Maximum acceptable value for MRU
#define PPP_MAX_MRU 1500

//FCS field size
#define PPP_FCS_SIZE 2


/**
 * @brief PPP phases
 **/

typedef enum
{
   PPP_PHASE_DEAD         = 0, ///<Link dead
   PPP_PHASE_ESTABLISH    = 1, ///<Link establishment phase
   PPP_PHASE_AUTHENTICATE = 2, ///<Authentication phase
   PPP_PHASE_NETWORK      = 3, ///<Network-layer protocol phase
   PPP_PHASE_TERMINATE    = 4  ///<Link termination phase
} PppPhase;


/**
 * @brief LCP/NCP states
 **/

typedef enum
{
   PPP_STATE_0_INITIAL  = 0,
   PPP_STATE_1_STARTING = 1,
   PPP_STATE_2_CLOSED   = 2,
   PPP_STATE_3_STOPPED  = 3,
   PPP_STATE_4_CLOSING  = 4,
   PPP_STATE_5_STOPPING = 5,
   PPP_STATE_6_REQ_SENT = 6,
   PPP_STATE_7_ACK_RCVD = 7,
   PPP_STATE_8_ACK_SENT = 8,
   PPP_STATE_9_OPENED   = 9
} PppState;


/**
 * @brief Protocol field values
 **/

typedef enum
{
   PPP_PROTOCOL_IP     = 0x0021, ///<Internet Protocol
   PPP_PROTOCOL_IPV6   = 0x0057, ///<Internet Protocol version 6
   PPP_PROTOCOL_IPCP   = 0x8021, ///<IP Control Protocol
   PPP_PROTOCOL_IPV6CP = 0x8057, ///<IPv6 Control Protocol
   PPP_PROTOCOL_LCP    = 0xC021, ///<Link Control Protocol
   PPP_PROTOCOL_PAP    = 0xC023, ///<Password Authentication Protocol
   PPP_PROTOCOL_LQR    = 0xC025, ///<Link Quality Report
   PPP_PROTOCOL_CHAP   = 0xC223  ///<Challenge Handshake Authentication Protocol
} PppProtocol;


/**
 * @brief Code field values
 **/

typedef enum
{
   PPP_CODE_CONFIGURE_REQ = 1,  ///<Configure-Request
   PPP_CODE_CONFIGURE_ACK = 2,  ///<Configure-Ack
   PPP_CODE_CONFIGURE_NAK = 3,  ///<Configure-Nak
   PPP_CODE_CONFIGURE_REJ = 4,  ///<Configure-Reject
   PPP_CODE_TERMINATE_REQ = 5,  ///<Terminate-Request
   PPP_CODE_TERMINATE_ACK = 6,  ///<Terminate-Ack
   PPP_CODE_CODE_REJ      = 7,  ///<Code-Reject
   PPP_CODE_PROTOCOL_REJ  = 8,  ///<Protocol-Reject
   PPP_CODE_ECHO_REQ      = 9,  ///<Echo-Request
   PPP_CODE_ECHO_REP      = 10, ///<Echo-Reply
   PPP_CODE_DISCARD_REQ   = 11  ///<Discard-Request
} PppCode;


//Win32 compiler?
#if defined(_WIN32)
   #pragma pack(push, 1)
#endif


/**
 * @brief PPP frame header
 **/

typedef __start_packed struct
{
   uint8_t address;   //0
   uint8_t control;   //1
   uint16_t protocol; //2-3
   uint8_t data[];    //4
} __end_packed PppFrame;


/**
 * @brief LCP/NCP packet header
 **/

typedef __start_packed struct
{
   uint8_t code;       //0
   uint8_t identifier; //1
   uint16_t length;    //2-3
   uint8_t data[];     //4
} __end_packed PppPacket;


/**
 * @brief Configure-Request, Configure-Ack, Configure-Nak and Configure-Reject packets
 **/

typedef __start_packed struct
{
   uint8_t code;       //0
   uint8_t identifier; //1
   uint16_t length;    //2-3
   uint8_t options[];  //4
} __end_packed PppConfigurePacket;


/**
 * @brief Terminate-Request and Terminate-Ack packet
 **/

typedef __start_packed struct
{
   uint8_t code;       //0
   uint8_t identifier; //1
   uint16_t length;    //2-3
   uint8_t  data[];    //4
} __end_packed PppTerminatePacket;


/**
 * @brief Code-Reject packet
 **/

typedef __start_packed struct
{
   uint8_t code;              //0
   uint8_t identifier;        //1
   uint16_t length;           //2-3
   uint8_t  rejectedPacket[]; //4
} __end_packed PppCodeRejPacket;


/**
 * @brief Protocol-Reject packet
 **/

typedef __start_packed struct
{
   uint8_t code;              //0
   uint8_t identifier;        //1
   uint16_t length;           //2-3
   uint16_t rejectedProtocol; //4-5
   uint8_t rejectedInfo[];    //6
} __end_packed PppProtocolRejPacket;


/**
 * @brief Echo-Request and Echo-Reply packet
 **/

typedef __start_packed struct
{
   uint8_t code;         //0
   uint8_t identifier;   //1
   uint16_t length;      //2-3
   uint32_t magicNumber; //4-7
   uint8_t data[];       //8
} __end_packed PppEchoPacket;


/**
 * @brief PPP Discard-Request packet
 **/

typedef __start_packed struct
{
   uint8_t code;         //0
   uint8_t identifier;   //1
   uint16_t length;      //2-3
   uint32_t magicNumber; //4-7
   uint8_t data[];       //8
} __end_packed PppDiscardReqPacket;


/**
 * @brief LCP/NCP option
 **/

typedef __start_packed struct
{
   uint8_t type;   //0
   uint8_t length; //1
   uint8_t data[]; //2
} __end_packed PppOption;


//Win32 compiler?
#if defined(_WIN32)
   #pragma pack(pop)
#endif


/**
 * @brief PPP settings
 **/

typedef struct
{
   NetInterface *interface; ///<Underlying network interface
   uint16_t mru;            ///<Default MRU
   uint32_t accm;           ///<default async control character map
} PppSettings;


/**
 * @brief PPP finite state machine
 **/

typedef struct
{
   uint_t state;          ///<FSM state
   uint8_t identifier;    ///<Identifier used to match requests and replies
   uint_t restartCounter; ///<Restart counter
   uint_t failureCounter; ///<Failure counter
   systime_t timestamp;   ///<Timestamp to manage retransmissions
} PppFsm;


/**
 * @brief PPP configuration options
 **/

typedef struct
{
   uint16_t mru;
   bool_t mruRejected;
   uint32_t accm;
   bool_t accmRejected;
   uint16_t authProtocol;
   bool_t authProtocolRejected;
   uint32_t magicNumber;
   bool_t magicNumberRejected;
#if (IPV4_SUPPORT == ENABLED)
   Ipv4Addr ipAddr;
   bool_t ipAddrRejected;
#endif
} PppConfig;


/**
 * @brief PPP context
 **/

typedef struct
{
   PppSettings settings;      ///PPP settings
   NetInterface *interface;   ///<Underlying network interface
   OsMutex mutex;             ///<Mutex preventing simultaneous access to PPP context
   systime_t timeout;         ///<Timeout for blocking operations

   char_t username[PPP_MAX_USERNAME_LEN + 1]; ///<User name
   char_t password[PPP_MAX_PASSWORD_LEN + 1]; ///<Password

   PppPhase pppPhase;         ///<PPP phase
   PppFsm lcpFsm;             ///<LCP finite state machine
   PppFsm ipcpFsm;            ///<IPCP finite state machine
   PppFsm papFsm;             ///<PAP finite state machine
   PppConfig localConfig;     ///<Local configuration options
   PppConfig peerConfig;      ///<Peer configuration options
   bool_t ipRejected;         ///<IPv4 protocol is not supported by the peer
   bool_t ipv6Rejected;       ///<IPv6 protocol is not support by the peer

   uint8_t txBuffer[PPP_TX_BUFFER_SIZE]; ///<Transmit buffer
   uint_t txBufferLen;
   uint_t txWriteIndex;
   uint_t txReadIndex;

   uint8_t rxBuffer[PPP_RX_BUFFER_SIZE]; ///<Receive buffer
   uint_t rxBufferLen;
   uint_t rxWriteIndex;
   uint_t rxReadIndex;
   uint_t rxFrameCount;
} PppContext;


//PPP related functions
void pppGetDefaultSettings(PppSettings *settings);
error_t pppInit(PppContext *context, const PppSettings *settings);

error_t pppSetTimeout(NetInterface *interface, systime_t timeout);

error_t pppSendAtCommand(NetInterface *interface, const char_t *data);
error_t pppReceiveAtCommand(NetInterface *interface, char_t *data, size_t size);

error_t pppConnect(NetInterface *interface);
error_t pppClose(NetInterface *interface);

void pppTick(NetInterface *interface);

void pppProcessFrame(NetInterface *interface, PppFrame *frame, size_t length);

error_t pppSendFrame(NetInterface *interface,
   NetBuffer *buffer, size_t offset, uint16_t protocol);

uint16_t pppCalcFcs(const void *data, size_t length);
uint16_t pppCalcFcsEx(const NetBuffer *buffer, size_t offset, size_t length);

NetBuffer *pppAllocBuffer(size_t length, size_t *offset);

#endif
