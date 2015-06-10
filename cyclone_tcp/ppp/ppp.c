/**
 * @file ppp.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL PPP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "ppp/ppp.h"
#include "ppp/ppp_hdlc.h"
#include "ppp/ppp_debug.h"
#include "ppp/lcp.h"
#include "ppp/ipcp.h"
#include "ppp/pap.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (PPP_SUPPORT == ENABLED)

//FCS lookup table
static const uint16_t fcsTable[256] =
{
   0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF,
   0x8C48, 0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7,
   0x1081, 0x0108, 0x3393, 0x221A, 0x56A5, 0x472C, 0x75B7, 0x643E,
   0x9CC9, 0x8D40, 0xBFDB, 0xAE52, 0xDAED, 0xCB64, 0xF9FF, 0xE876,
   0x2102, 0x308B, 0x0210, 0x1399, 0x6726, 0x76AF, 0x4434, 0x55BD,
   0xAD4A, 0xBCC3, 0x8E58, 0x9FD1, 0xEB6E, 0xFAE7, 0xC87C, 0xD9F5,
   0x3183, 0x200A, 0x1291, 0x0318, 0x77A7, 0x662E, 0x54B5, 0x453C,
   0xBDCB, 0xAC42, 0x9ED9, 0x8F50, 0xFBEF, 0xEA66, 0xD8FD, 0xC974,
   0x4204, 0x538D, 0x6116, 0x709F, 0x0420, 0x15A9, 0x2732, 0x36BB,
   0xCE4C, 0xDFC5, 0xED5E, 0xFCD7, 0x8868, 0x99E1, 0xAB7A, 0xBAF3,
   0x5285, 0x430C, 0x7197, 0x601E, 0x14A1, 0x0528, 0x37B3, 0x263A,
   0xDECD, 0xCF44, 0xFDDF, 0xEC56, 0x98E9, 0x8960, 0xBBFB, 0xAA72,
   0x6306, 0x728F, 0x4014, 0x519D, 0x2522, 0x34AB, 0x0630, 0x17B9,
   0xEF4E, 0xFEC7, 0xCC5C, 0xDDD5, 0xA96A, 0xB8E3, 0x8A78, 0x9BF1,
   0x7387, 0x620E, 0x5095, 0x411C, 0x35A3, 0x242A, 0x16B1, 0x0738,
   0xFFCF, 0xEE46, 0xDCDD, 0xCD54, 0xB9EB, 0xA862, 0x9AF9, 0x8B70,
   0x8408, 0x9581, 0xA71A, 0xB693, 0xC22C, 0xD3A5, 0xE13E, 0xF0B7,
   0x0840, 0x19C9, 0x2B52, 0x3ADB, 0x4E64, 0x5FED, 0x6D76, 0x7CFF,
   0x9489, 0x8500, 0xB79B, 0xA612, 0xD2AD, 0xC324, 0xF1BF, 0xE036,
   0x18C1, 0x0948, 0x3BD3, 0x2A5A, 0x5EE5, 0x4F6C, 0x7DF7, 0x6C7E,
   0xA50A, 0xB483, 0x8618, 0x9791, 0xE32E, 0xF2A7, 0xC03C, 0xD1B5,
   0x2942, 0x38CB, 0x0A50, 0x1BD9, 0x6F66, 0x7EEF, 0x4C74, 0x5DFD,
   0xB58B, 0xA402, 0x9699, 0x8710, 0xF3AF, 0xE226, 0xD0BD, 0xC134,
   0x39C3, 0x284A, 0x1AD1, 0x0B58, 0x7FE7, 0x6E6E, 0x5CF5, 0x4D7C,
   0xC60C, 0xD785, 0xE51E, 0xF497, 0x8028, 0x91A1, 0xA33A, 0xB2B3,
   0x4A44, 0x5BCD, 0x6956, 0x78DF, 0x0C60, 0x1DE9, 0x2F72, 0x3EFB,
   0xD68D, 0xC704, 0xF59F, 0xE416, 0x90A9, 0x8120, 0xB3BB, 0xA232,
   0x5AC5, 0x4B4C, 0x79D7, 0x685E, 0x1CE1, 0x0D68, 0x3FF3, 0x2E7A,
   0xE70E, 0xF687, 0xC41C, 0xD595, 0xA12A, 0xB0A3, 0x8238, 0x93B1,
   0x6B46, 0x7ACF, 0x4854, 0x59DD, 0x2D62, 0x3CEB, 0x0E70, 0x1FF9,
   0xF78F, 0xE606, 0xD49D, 0xC514, 0xB1AB, 0xA022, 0x92B9, 0x8330,
   0x7BC7, 0x6A4E, 0x58D5, 0x495C, 0x3DE3, 0x2C6A, 0x1EF1, 0x0F78
};


/**
 * @brief Initialize settings with default values
 * @param[out] settings Structure that contains PPP settings
 **/

void pppGetDefaultSettings(PppSettings *settings)
{
   //Use default interface
   settings->interface = NULL;
   //Default MRU
   settings->mru = PPP_DEFAULT_MRU;
   //Default async control character map
   settings->accm = PPP_DEFAULT_ACCM;
}


/**
 * @brief PPP initialization
 * @param[in] context Pointer to the PPP context
 * @param[in] settings PPP specific settings
 * @return Error code
 **/

error_t pppInit(PppContext *context, const PppSettings *settings)
{
   error_t error;
   NetInterface *interface;

   //Debug message
   TRACE_INFO("PPP initialization\r\n");

   //Underlying network interface
   interface = settings->interface;

   //Initialize PPP context
   memset(context, 0, sizeof(PppContext));

   //Save user settings
   context->settings = *settings;

   //Initialize mutex object
   if(!osCreateMutex(&context->mutex))
   {
      //Failed to create mutex
      return ERROR_OUT_OF_RESOURCES;
   }

   //Attach the PPP context to the network interface
   interface->pppContext = context;

   //Initialize structure
   context->interface = interface;
   context->timeout = INFINITE_DELAY;

   //Initialize PPP finite state machine
   context->pppPhase = PPP_PHASE_DEAD;
   context->lcpFsm.state = PPP_STATE_0_INITIAL;
   context->ipcpFsm.state = PPP_STATE_0_INITIAL;
   context->papFsm.state = PAP_STATE_0_INITIAL;

   //Attach PPP HDLC driver
   error = netSetDriver(interface, &pppHdlcDriver);

   //Return status code
   return error;
}


/**
 * @brief Set timeout value for blocking operations
 * @param[in] interface Underlying network interface
 * @param[in] timeout Maximum time to wait
 * @return Error code
 **/

error_t pppSetTimeout(NetInterface *interface, systime_t timeout)
{
   PppContext *context;

   //Check parameters
   if(interface == NULL)
      return ERROR_INVALID_PARAMETER;
   //Make sure PPP has been properly configured
   if(interface->pppContext == NULL)
      return ERROR_NOT_CONFIGURED;

   //Point to the PPP context
   context = interface->pppContext;
   //Enter critical section
   osAcquireMutex(&context->mutex);

   //Set timeout value
   context->timeout = timeout;

   //Leave critical section
   osReleaseMutex(&context->mutex);
   //No error to report
   return NO_ERROR;
}


/**
 * @brief Send AT command
 * @param[in] interface Underlying network interface
 * @param[in] data NULL-terminated string that contains the AT command to be sent
 * @return Error code
 **/

error_t pppSendAtCommand(NetInterface *interface, const char_t *data)
{
   error_t error;
   bool_t status;
   PppContext *context;

   //Check parameters
   if(interface == NULL)
      return ERROR_INVALID_PARAMETER;
   //Make sure PPP has been properly configured
   if(interface->pppContext == NULL)
      return ERROR_NOT_CONFIGURED;

   //Point to the PPP context
   context = interface->pppContext;

   //Wait for the send buffer to be available for writing
   status = osWaitForEvent(&interface->nicTxEvent, context->timeout);

   //Check status
   if(status)
   {
      //Get exclusive access to the device
      osAcquireMutex(&interface->nicDriverMutex);

      //Check current PPP state
      if(context->pppPhase == PPP_PHASE_DEAD)
      {
         //Purge receive buffer
         error = pppHdlcDriverPurgeRxBuffer(context);

         //Send AT command
         if(!error)
            error = pppHdlcDriverSendAtCommand(interface, data);
      }
      else
      {
         //Report an error
         error = ERROR_ALREADY_CONNECTED;
      }

      //Release exclusive access to the device
      osReleaseMutex(&interface->nicDriverMutex);
   }
   else
   {
      //Timeout error
      return ERROR_TIMEOUT;
   }

   //Return status code
   return error;
}


/**
 * @brief Wait for an incoming AT command
 * @param[in] interface Underlying network interface
 * @param[out] data Buffer where to store the incoming AT command
 * @param[in] size Size of the buffer, in bytes
 * @return Error code
 **/

error_t pppReceiveAtCommand(NetInterface *interface, char_t *data, size_t size)
{
   error_t error;
   systime_t time;
   systime_t start;
   PppContext *context;

   //Check parameters
   if(interface == NULL)
      return ERROR_INVALID_PARAMETER;
   //Make sure PPP has been properly configured
   if(interface->pppContext == NULL)
      return ERROR_NOT_CONFIGURED;

   //Point to the PPP context
   context = interface->pppContext;
   //Save current time
   start = osGetSystemTime();

   //Wait for an incoming AT command
   while(1)
   {
      //Get exclusive access to the device
      osAcquireMutex(&interface->nicDriverMutex);

      //Check current PPP state
      if(context->pppPhase == PPP_PHASE_DEAD)
      {
         //Wait for an incoming AT command
         error = pppHdlcDriverReceiveAtCommand(interface, data, size);
      }
      else
      {
         //Report an error
         error = ERROR_ALREADY_CONNECTED;
      }

      //Release exclusive access to the device
      osReleaseMutex(&interface->nicDriverMutex);

      //No data received?
      if(error == ERROR_BUFFER_EMPTY || data[0] == '\0')
      {
         //Get current time
         time = osGetSystemTime();

         //Check whether the timeout period has elapsed
         if(timeCompare(time, start + context->timeout) >= 0)
         {
            //Timeout error
            error = ERROR_TIMEOUT;
            //Exit immediately
            break;
         }
         else
         {
            //Wait for more data to be received
            osDelayTask(PPP_POLLING_INTERVAL);
         }
      }
      else
      {
         //We are done
         break;
      }
   }

   //Return status code
   return error;
}


/**
 * @brief Establish a PPP connection
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t pppConnect(NetInterface *interface)
{
   error_t error;
   systime_t time;
   systime_t start;
   PppContext *context;

   //Check parameters
   if(interface == NULL)
      return ERROR_INVALID_PARAMETER;
   //Make sure PPP has been properly configured
   if(interface->pppContext == NULL)
      return ERROR_NOT_CONFIGURED;

   //Point to the PPP context
   context = interface->pppContext;
   //Save current time
   start = osGetSystemTime();

   //Enter critical section
   osAcquireMutex(&context->mutex);

   //Default PPP phase
   context->pppPhase = PPP_PHASE_DEAD;

   //Initialize LCP FSM
   context->lcpFsm.state = PPP_STATE_0_INITIAL;
   context->lcpFsm.identifier = 0;
   context->lcpFsm.restartCounter = 0;
   context->lcpFsm.failureCounter = 0;

   //Initialize IPCP FSM
   context->ipcpFsm.state = PPP_STATE_0_INITIAL;
   context->ipcpFsm.identifier = 0;
   context->ipcpFsm.restartCounter = 0;
   context->ipcpFsm.failureCounter = 0;

   //Initialize PAP FSM
   context->papFsm.state = PAP_STATE_0_INITIAL;
   context->papFsm.identifier = 0;
   context->papFsm.restartCounter = 0;
   context->papFsm.failureCounter = 0;

   //Default local configuration
   context->localConfig.mru = context->settings.mru;
   context->localConfig.mruRejected = FALSE;
   context->localConfig.accm = context->settings.accm;
   context->localConfig.accmRejected = FALSE;
   context->localConfig.authProtocol = 0;
   context->localConfig.authProtocolRejected = FALSE;
   context->localConfig.magicNumber = PPP_DEFAULT_MAGIC_NUMBER;
   context->localConfig.magicNumberRejected = FALSE;

   //Default peer's configuration
   context->peerConfig.mru = PPP_DEFAULT_MRU;
   context->peerConfig.accm = PPP_DEFAULT_ACCM;
   context->localConfig.authProtocol = 0;
   context->peerConfig.magicNumber = PPP_DEFAULT_MAGIC_NUMBER;

#if (IPV4_SUPPORT == ENABLED)
   //Use default IPv4 addresses
   ipv4GetHostAddr(interface, &context->localConfig.ipAddr);
   context->localConfig.ipAddrRejected = FALSE;
   ipv4GetDefaultGateway(interface, &context->peerConfig.ipAddr);
   context->peerConfig.ipAddrRejected = FALSE;
#endif

   //The link is available for traffic
   error = lcpOpen(context);

   //Leave critical section
   osReleaseMutex(&context->mutex);

   //Any error to report?
   if(error)
      return error;

   //Blocking operation?
   if(context->timeout)
   {
      //Wait for the connection to be established
      while(context->pppPhase == PPP_PHASE_ESTABLISH ||
         context->pppPhase == PPP_PHASE_AUTHENTICATE)
      {
         //Check timeout value
         if(context->timeout != INFINITE_DELAY)
         {
            //Get current time
            time = osGetSystemTime();

            //Check whether the timeout period has elapsed
            if(timeCompare(time, start + context->timeout) >= 0)
               break;
         }

         //Poll the state
         osDelayTask(PPP_POLLING_INTERVAL);
      }

      //Failed to establish connection?
      if(context->pppPhase != PPP_PHASE_NETWORK)
      {
         //Enter critical section
         osAcquireMutex(&context->mutex);

         //Abort the PPP connection
         context->pppPhase = PPP_PHASE_DEAD;
         context->lcpFsm.state = PPP_STATE_0_INITIAL;
         context->ipcpFsm.state = PPP_STATE_0_INITIAL;
         context->papFsm.state = PAP_STATE_0_INITIAL;

         //Leave critical section
         osReleaseMutex(&context->mutex);

         //Report an error
         return ERROR_TIMEOUT;
      }
   }

   //PPP connection succesfully established
   return NO_ERROR;
}


/**
 * @brief Close a PPP connection
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t pppClose(NetInterface *interface)
{
   error_t error;
   systime_t time;
   systime_t start;
   PppContext *context;

   //Check parameters
   if(interface == NULL)
      return ERROR_INVALID_PARAMETER;
   //Make sure PPP has been properly configured
   if(interface->pppContext == NULL)
      return ERROR_NOT_CONFIGURED;

   //Point to the PPP context
   context = interface->pppContext;
   //Save current time
   start = osGetSystemTime();

   //Enter critical section
   osAcquireMutex(&context->mutex);

   //The link is no longer available for traffic
   error = lcpClose(context);

   //Leave critical section
   osReleaseMutex(&context->mutex);

   //Any error to report?
   if(error)
      return error;

   //Blocking operation?
   if(context->timeout)
   {
      //Wait for the connection to be closed
      while(context->pppPhase != PPP_PHASE_DEAD)
      {
         //Check timeout value
         if(context->timeout != INFINITE_DELAY)
         {
            //Get current time
            time = osGetSystemTime();

            //Check whether the timeout period has elapsed
            if(timeCompare(time, start + context->timeout) >= 0)
               break;
         }

         //Poll the state
         osDelayTask(PPP_POLLING_INTERVAL);
      }

      //Failed to properly close the connection?
      if(context->pppPhase != PPP_PHASE_DEAD)
      {
         //Enter critical section
         osAcquireMutex(&context->mutex);

         //Abort the PPP connection
         context->pppPhase = PPP_PHASE_DEAD;
         context->lcpFsm.state = PPP_STATE_0_INITIAL;
         context->ipcpFsm.state = PPP_STATE_0_INITIAL;
         context->papFsm.state = PAP_STATE_0_INITIAL;

         //Leave critical section
         osReleaseMutex(&context->mutex);

         //Report an error
         return ERROR_TIMEOUT;
      }
   }

   //PPP connection has been properly closed
   return NO_ERROR;
}


/**
 * @brief PPP timer handler
 *
 * This routine must be periodically called by the TCP/IP stack to
 * manage retransmissions
 *
 * @param[in] interface Underlying network interface
 **/

void pppTick(NetInterface *interface)
{
   PppContext *context;

   //PPP driver?
   if(interface->nicDriver->type == NIC_TYPE_PPP)
   {
      //Point to the PPP context
      context = interface->pppContext;
      //Enter critical section
      osAcquireMutex(&context->mutex);

      //Handle LCP retransmission timer
      lcpTick(context);
      //Handle IPCP retransmission timer
      ipcpTick(context);
      //Handle PAP retransmission timer
      papTick(context);

      //Leave critical section
      osReleaseMutex(&context->mutex);
   }
}


/**
 * @brief Process an incoming PPP frame
 * @param[in] interface Underlying network interface
 * @param[in] frame Incoming PPP frame to process
 * @param[in] length Total frame length
 **/

void pppProcessFrame(NetInterface *interface, PppFrame *frame, size_t length)
{
   PppContext *context;

   //Point to the PPP context
   context = interface->pppContext;

   //Ensure the length of the incoming frame is valid
   if(length < (sizeof(PppFrame) + PPP_FCS_SIZE))
      return;

   //Debug message
   TRACE_DEBUG("PPP frame received (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump PPP header contents for debugging purpose
   pppDumpFrameHeader(frame);

   //The value of the residue is 0x0F47 when no FCS errors are detected
   if(pppCalcFcs(frame, length) != 0x0F47)
   {
      //Debug message
      TRACE_WARNING("Wrong FCS detected!\r\n");
      //Drop the received frame
      return;
   }

   //Calculate the length of the data payload
   length -= sizeof(PppFrame) + PPP_FCS_SIZE;

   //Enter critical section
   osAcquireMutex(&context->mutex);

   //Check protocol field
   switch(ntohs(frame->protocol))
   {
   //Link control protocol?
   case PPP_PROTOCOL_LCP:
      //Process incoming LCP packet
      lcpProcessPacket(context, (PppPacket *) frame->data, length);
      break;
#if (IPV4_SUPPORT == ENABLED)
   //IP protocol?
   case PPP_PROTOCOL_IP:
      //Process incoming IPv4 packet
      ipv4ProcessPacket(interface, (Ipv4Header *) frame->data, length);
      break;
   //IP control protocol?
   case PPP_PROTOCOL_IPCP:
      //Process incoming IPCP packet
      ipcpProcessPacket(context, (PppPacket *) frame->data, length);
      break;
#endif
#if (IPV6_SUPPORT == ENABLED)
   //IPv6 protocol?
   //case PPP_PROTOCOL_IPV6:
      //break;
   //IPv6 control protocol?
   //case PPP_PROTOCOL_IPV6CP:
      //Process incoming IPV6CP packet
      //ipv6cpProcessPacket(context, frame->data, length);
      //break;
#endif
   //PAP protocol?
   case PPP_PROTOCOL_PAP:
      //Process incoming PAP packet
      papProcessPacket(context, (PppPacket *) frame->data, length);
      break;
   //Unknown protocol field
   default:
      //The peer is attempting to use a protocol which is unsupported
      lcpProcessUnknownProtocol(context, ntohs(frame->protocol), frame->data, length);
      break;
   }

   //Leave critical section
   osReleaseMutex(&context->mutex);
}


/**
 * @brief Send a PPP frame
 * @param[in] interface Underlying network interface
 * @param[in] buffer Multi-part buffer containing the data
 * @param[in] offset Offset to the first data byte
 * @param[in] protocol Protocol field value
 * @return Error code
 **/

error_t pppSendFrame(NetInterface *interface,
   NetBuffer *buffer, size_t offset, uint16_t protocol)
{
   error_t error;
   size_t length;
   uint16_t fcs;
   PppFrame *frame;

   if(protocol == PPP_PROTOCOL_IPV6)
   {
      //Not implemented
      return NO_ERROR;
   }

   //Is there enough space for the PPP header?
   if(offset < sizeof(PppFrame))
      return ERROR_INVALID_PARAMETER;

   //Make room for the PPP header
   offset -= sizeof(PppFrame);
   //Retrieve the length of the frame
   length = netBufferGetLength(buffer) - offset;

   //Point to the beginning of the frame
   frame = netBufferAt(buffer, offset);

   //Format PPP header
   frame->address = 0xFF;
   frame->control = 0x03;
   frame->protocol = htons(protocol);

   //Compute FCS over the header and payload
   fcs = pppCalcFcsEx(buffer, offset, length);
   //The FCS is transmitted least significant octet first
   fcs = htole16(fcs);

   //Append the calculated FCS value
   error = netBufferAppend(buffer, &fcs, sizeof(fcs));
   //Any error to report?
   if(error) return error;

   //Adjust frame length
   length += sizeof(fcs);

   //Debug message
   TRACE_DEBUG("Sending PPP frame (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump PPP header contents for debugging purpose
   pppDumpFrameHeader(frame);

   //Send the resulting frame over the specified link
   return nicSendPacket(interface, buffer, offset);
}


/**
 * @brief FCS calculation
 * @param[in] data Pointer to the data over which to calculate the FCS
 * @param[in] length Number of bytes to process
 * @return Resulting FCS value
 **/

uint16_t pppCalcFcs(const void *data, size_t length)
{
   size_t i;
   uint16_t fcs;

   //Point to the data over which to calculate the FCS
   const uint8_t *p = (uint8_t *) data;

   //FCS preset value
   fcs = 0xFFFF;

   //Loop through data
   for(i = 0; i < length; i++)
   {
      //The message is processed byte by byte
      fcs = (fcs >> 8) ^ fcsTable[(fcs & 0xFF) ^ p[i]];
   }

   //Return 1's complement value
   return ~fcs;
}


/**
 * @brief Calculate FCS over a multi-part buffer
 * @param[in] buffer Pointer to the multi-part buffer
 * @param[in] offset Offset from the beginning of the buffer
 * @param[in] length Number of bytes to process
 * @return Resulting FCS value
 **/

uint16_t pppCalcFcsEx(const NetBuffer *buffer, size_t offset, size_t length)
{
   uint_t i;
   uint_t n;
   uint16_t fcs;
   uint8_t *p;

   //FCS preset value
   fcs = 0xFFFF;

   //Loop through data chunks
   for(i = 0; i < buffer->chunkCount && length > 0; i++)
   {
      //Is there any data to process in the current chunk?
      if(offset < buffer->chunk[i].length)
      {
         //Point to the first data byte
         p = (uint8_t *) buffer->chunk[i].address + offset;
         //Compute the number of bytes to process
         n = MIN(buffer->chunk[i].length - offset, length);
         //Adjust byte counter
         length -= n;

         //Process current chunk
         while(n > 0)
         {
            //The message is processed byte by byte
            fcs = (fcs >> 8) ^ fcsTable[(fcs & 0xFF) ^ *p];

            //Next byte
            p++;
            n--;
         }

         //Process the next block from the start
         offset = 0;
      }
      else
      {
         //Skip the current chunk
         offset -= buffer->chunk[i].length;
      }
   }

   //Return 1's complement value
   return ~fcs;
}


/**
 * @brief Allocate a buffer to hold a PPP frame
 * @param[in] length Desired payload length
 * @param[out] offset Offset to the first byte of the payload
 * @return The function returns a pointer to the newly allocated
 *   buffer. If the system is out of resources, NULL is returned
 **/

NetBuffer *pppAllocBuffer(size_t length, size_t *offset)
{
   NetBuffer *buffer;

   //Allocate a buffer to hold the Ethernet header and the payload
   buffer = netBufferAlloc(length + sizeof(PppFrame));
   //Failed to allocate buffer?
   if(!buffer) return NULL;

   //Offset to the first byte of the payload
   *offset = sizeof(PppFrame);

   //Return a pointer to the freshly allocated buffer
   return buffer;
}

#endif
