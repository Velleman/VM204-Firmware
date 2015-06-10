/**
 * @file pap.h
 * @brief PAP (Password Authentication Protocol)
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

#ifndef _PAP_H
#define _PAP_H

//Dependencies
#include "core/net.h"
#include "ppp/ppp.h"

//Restart timer
#ifndef PAP_RESTART_TIMER
   #define PAP_RESTART_TIMER 3000
#elif (PAP_RESTART_TIMER < 1000)
   #error PAP_RESTART_TIMER parameter is not valid
#endif

//Maximum number of retransmissions for Authenticate-Requests
#ifndef PAP_MAX_REQUESTS
   #define PAP_MAX_REQUESTS 5
#elif (PAP_MAX_REQUESTS < 1)
   #error PAP_MAX_REQUESTS parameter is not valid
#endif


/**
 * @brief PAP states
 **/

typedef enum
{
   PAP_STATE_0_INITIAL  = 0,
   PAP_STATE_1_REQ_SENT = 1,
   PAP_STATE_2_ACK_RCVD = 2,
   PAP_STATE_3_NAK_RCVD = 3
} PapState;


/**
 * @brief Code field values
 **/

typedef enum
{
   PAP_CODE_AUTH_REQ = 1, ///<Authenticate-Request
   PAP_CODE_AUTH_ACK = 2, ///<Authenticate-Ack
   PAP_CODE_AUTH_NAK = 3  ///<Authenticate-Nak
} PapCode;


//PAP related functions
error_t papStartAuth(PppContext *context);
error_t papAbortAuth(PppContext *context);

void papTick(PppContext *context);

void papProcessPacket(PppContext *context,
   const PppPacket *packet, size_t length);

error_t papProcessAuthReq(PppContext *context,
   const PppPacket *authReqPacket, size_t length);

error_t papProcessAuthAck(PppContext *context,
   const PppPacket *authAckPacket, size_t length);

error_t papProcessAuthNak(PppContext *context,
   const PppPacket *authNakPacket, size_t length);

error_t papSendAuthReq(PppContext *context);

#endif
