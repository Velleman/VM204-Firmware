/**
 * @file pap.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL PPP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "ppp/ppp_debug.h"
#include "ppp/lcp.h"
#include "ppp/ipcp.h"
#include "ppp/pap.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (PPP_SUPPORT == ENABLED)


/**
 * @brief Start PAP authentication
 * @param[in] context PPP context
 * @return Error code
 **/

error_t papStartAuth(PppContext *context)
{
   //Debug message
   TRACE_INFO("\r\nStarting PAP authentication...\r\n");

   //Initialize restart counter
   context->papFsm.restartCounter = PAP_MAX_REQUESTS;
   //Send Authenticate-Request packet
   papSendAuthReq(context);
   //Switch to the Req-Sent state
   context->papFsm.state = PAP_STATE_1_REQ_SENT;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Abort PAP authentication
 * @param[in] context PPP context
 * @return Error code
 **/

error_t papAbortAuth(PppContext *context)
{
   //Debug message
   TRACE_INFO("\r\nAborting PAP authentication...\r\n");

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief PAP timer handler
 *
 * This routine must be periodically called by the TCP/IP stack to
 * manage retransmissions
 *
 * @param[in] context PPP context
 **/

void papTick(PppContext *context)
{
   //Check whether the restart timer is running
   if(context->papFsm.state == PAP_STATE_1_REQ_SENT)
   {
      //Get current time
      systime_t time = osGetSystemTime();

      //Check restart timer
      if((time - context->papFsm.timestamp) >= PAP_RESTART_TIMER)
      {
         //Debug message
         TRACE_INFO("\r\nPAP Timeout event\r\n");

         //Check whether the restart counter is greater than zero
         if(context->papFsm.restartCounter > 0)
         {
            //Retransmit Authenticate-Request packet
            papSendAuthReq(context);
         }
         else
         {
            //Back to the default state
            context->papFsm.state = PAP_STATE_0_INITIAL;
            //Authentication failed
            lcpClose(context);
         }
      }
   }
}


/**
 * @brief Process an incoming PAP packet
 * @param[in] context PPP context
 * @param[in] packet PAP packet received fom the peer
 * @param[in] length Length of the packet, in bytes
 **/

void papProcessPacket(PppContext *context,
   const PppPacket *packet, size_t length)
{
   //Ensure the length of the incoming PAP packet is valid
   if(length < sizeof(PppPacket))
      return;

   //Check the length field
   if(ntohs(packet->length) > length)
      return;
   if(ntohs(packet->length) < sizeof(PppPacket))
      return;

   //Save the length of the PAP packet
   length = ntohs(packet->length);

   //Debug message
   TRACE_INFO("PAP packet received (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump PAP packet contents for debugging purpose
   pppDumpPacket(packet, length, PPP_PROTOCOL_PAP);

   //Check PAP code field
   switch(packet->code)
   {
   //Authenticate-Request packet?
   case PAP_CODE_AUTH_REQ:
      //Process Authenticate-Request packet
      papProcessAuthReq(context, packet, length);
      break;
   //Authenticate-Ack packet?
   case PAP_CODE_AUTH_ACK:
      //Process Authenticate-Ack packet
      papProcessAuthAck(context, packet, length);
      break;
   //Authenticate-Nak packet?
   case PAP_CODE_AUTH_NAK:
      //Process Authenticate-Nak packet
      papProcessAuthNak(context, packet, length);
      break;
   //Unknown code field
   default:
      //Silently drop the incoming packet
      break;
   }
}


/**
 * @brief Process Authenticate-Request packet
 * @param[in] context PPP context
 * @param[in] authReqPacket Packet received from the peer
 * @param[in] length Length of the packet, in bytes
 * @return Error code
 **/

error_t papProcessAuthReq(PppContext *context,
   const PppPacket *authReqPacket, size_t length)
{
   //Debug message
   TRACE_INFO("\r\nPAP Authenticate-Request packet received\r\n");

   //Not implemented
   return ERROR_NOT_IMPLEMENTED;
}


/**
 * @brief Process Authenticate-Ack packet
 * @param[in] context PPP context
 * @param[in] authAckPacket Packet received from the peer
 * @param[in] length Length of the packet, in bytes
 * @return Error code
 **/

error_t papProcessAuthAck(PppContext *context,
   const PppPacket *authAckPacket, size_t length)
{
   //Debug message
   TRACE_INFO("\r\nPAP Authenticate-Ack packet received\r\n");

   //When a packet is received with an invalid Identifier field, the
   //packet is silently discarded without affecting the automaton
   if(authAckPacket->identifier != context->papFsm.identifier)
      return ERROR_WRONG_IDENTIFIER;

   //Switch to the Ack-Rcvd state
   context->papFsm.state = PAP_STATE_2_ACK_RCVD;
   //Advance to the Network phase
   context->pppPhase = PPP_PHASE_NETWORK;
   //IPCP Open event
   ipcpOpen(context);

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Process Authenticate-Nak packet
 * @param[in] context PPP context
 * @param[in] authNakPacket Packet received from the peer
 * @param[in] length Length of the packet, in bytes
 * @return Error code
 **/

error_t papProcessAuthNak(PppContext *context,
   const PppPacket *authNakPacket, size_t length)
{
   //Debug message
   TRACE_INFO("\r\nPAP Authenticate-Nak packet received\r\n");

   //When a packet is received with an invalid Identifier field, the
   //packet is silently discarded without affecting the automaton
   if(authNakPacket->identifier != context->papFsm.identifier)
      return ERROR_WRONG_IDENTIFIER;

   //Switch to the Nak-Rcvd state
   context->papFsm.state = PAP_STATE_3_NAK_RCVD;
   //Authentication failed
   lcpClose(context);

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Send Authenticate-Request packet
 * @param[in] context PPP context
 * @return Error code
 **/

error_t papSendAuthReq(PppContext *context)
{
   error_t error;
   size_t usernameLen;
   size_t passwordLen;
   size_t length;
   size_t offset;
   NetBuffer *buffer;
   PppPacket *authReqPacket;

   //Get the length of the user name
   usernameLen = strlen(context->username);
   //Get the length of the password
   passwordLen = strlen(context->password);

   //Calculate the length of the Authenticate-Request packet
   length = sizeof(PppPacket) + 2 + usernameLen + passwordLen;

   //Allocate a buffer memory to hold the packet
   buffer = pppAllocBuffer(length, &offset);
   //Failed to allocate memory?
   if(!buffer) return ERROR_OUT_OF_MEMORY;

   //Point to the Authenticate-Request packet
   authReqPacket = netBufferAt(buffer, offset);

   //Format packet header
   authReqPacket->code = PAP_CODE_AUTH_REQ;
   authReqPacket->identifier = ++context->papFsm.identifier;
   authReqPacket->length = htons(length);

   //The Peer-ID-Length field indicates the length of Peer-ID field
   authReqPacket->data[0] = usernameLen;
   //Append Peer-ID
   memcpy(authReqPacket->data + 1, context->username, usernameLen);

   //The Passwd-Length field indicates the length of Password field
   authReqPacket->data[usernameLen + 1] = passwordLen;
   //Append Password
   memcpy(authReqPacket->data + usernameLen + 2, context->password, passwordLen);

   //Adjust the length of the multi-part buffer
   netBufferSetLength(buffer, offset + length);

   //Debug message
   TRACE_INFO("Sending PAP Authenticate-Request packet (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump packet contents for debugging purpose
   pppDumpPacket((PppPacket *) authReqPacket, length, PPP_PROTOCOL_PAP);

   //Send PPP frame
   error = pppSendFrame(context->interface, buffer, offset, PPP_PROTOCOL_PAP);

   //The restart counter is decremented each time a Authenticate-Request is sent
   if(context->papFsm.restartCounter > 0)
      context->papFsm.restartCounter--;

   //Save the time at which the packet was sent
   context->papFsm.timestamp = osGetSystemTime();

   //Free previously allocated memory block
   netBufferFree(buffer);
   //Return status code
   return error;
}

#endif
