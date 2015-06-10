/**
 * @file http_server.c
 * @brief HTTP server (HyperText Transfer Protocol)
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
 * @section Description
 *
 * Using the HyperText Transfer Protocol, the HTTP server delivers web pages
 * to browsers as well as other data files to web-based applications. Refers
 * to the following RFCs for complete details:
 * - RFC 1945: Hypertext Transfer Protocol - HTTP/1.0
 * - RFC 2616: Hypertext Transfer Protocol - HTTP/1.1
 * - RFC 2617: HTTP Authentication: Basic and Digest Access Authentication
 * - RFC 2818: HTTP Over TLS
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.6.0
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL HTTP_TRACE_LEVEL

//Dependencies
#include <stdlib.h>
#include <limits.h>
#include "core/net.h"
#include "http/http_server.h"
#include "http/http_server_auth.h"
#include "http/http_server_misc.h"
#include "http/mime.h"
#include "http/ssi.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (HTTP_SERVER_SUPPORT == ENABLED)


/**
 * @brief HTTP status codes
 **/

static const HttpStatusCodeDesc statusCodeList[] =
{
   //Success
   {200, "OK"},
   {201, "Created"},
   {202, "Accepted"},
   {204, "No Content"},
   //Redirection
   {301, "Moved Permanently"},
   {302, "Found"},
   {304, "Not Modified"},
   //Client error
   {400, "Bad Request"},
   {401, "Unauthorized"},
   {403, "Forbidden"},
   {404, "Not Found"},
   //Server error
   {500, "Internal Server Error"},
   {501, "Not Implemented"},
   {502, "Bad Gateway"},
   {503, "Service Unavailable"}
};


/**
 * @brief Initialize settings with default values
 * @param[out] settings Structure that contains HTTP server settings
 **/

void httpServerGetDefaultSettings(HttpServerSettings *settings)
{
   //Use default interface
   settings->interface = NULL;
   //Listen to port 80
   settings->port = HTTP_PORT;
   //Maximum length of the pending connection queue
   settings->backlog = HTTP_SERVER_BACKLOG;
   //Client connections
   settings->maxConnections = 0;
   settings->connections = NULL;
   //Specify the server's root directory
   strcpy(settings->rootDirectory, "/");
   //Set default home page
   strcpy(settings->defaultDocument, "index.htm");

#if (HTTP_SERVER_DIGEST_AUTH_SUPPORT == ENABLED)
   //Pseudo-random number generator
   settings->prngAlgo = NULL;
   settings->prngContext = NULL;
#endif

#if (HTTP_SERVER_TLS_SUPPORT == ENABLED)
   //SSL/TLS initialization callback function
   settings->tlsInitCallback = NULL;
#endif

#if (HTTP_SERVER_BASIC_AUTH_SUPPORT == ENABLED || HTTP_SERVER_DIGEST_AUTH_SUPPORT == ENABLED)
   //HTTP authentication callback function
   settings->authCallback = NULL;
#endif

   //CGI callback function
   settings->cgiCallback = NULL;
   //URI not found callback function
   settings->uriNotFoundCallback = NULL;
}


/**
 * @brief HTTP server initialization
 * @param[in] context Pointer to the HTTP server context
 * @param[in] settings HTTP server specific settings
 * @return Error code
 **/

error_t httpServerInit(HttpServerContext *context, const HttpServerSettings *settings)
{
   error_t error;
   uint_t i;

   //Debug message
   TRACE_INFO("Initializing HTTP server...\r\n");

   //Ensure the parameters are valid
   if(!context || !settings)
      return ERROR_INVALID_PARAMETER;

   //Check user settings
   if(settings->maxConnections == 0 || settings->connections == NULL)
      return ERROR_INVALID_PARAMETER;

   //Clear the HTTP server context
   memset(context, 0, sizeof(HttpServerContext));

   //Save user settings
   context->settings = *settings;
   //Client connections
   context->connections = settings->connections;

   //Create a semaphore to limit the number of simultaneous connections
   if(!osCreateSemaphore(&context->semaphore, context->settings.maxConnections))
      return ERROR_OUT_OF_RESOURCES;

   //Loop through client connections
   for(i = 0; i < context->settings.maxConnections; i++)
   {
      //Create an event object to manage connection lifetime
      if(!osCreateEvent(&context->connections[i].startEvent))
         return ERROR_OUT_OF_RESOURCES;
   }

#if (HTTP_SERVER_DIGEST_AUTH_SUPPORT == ENABLED)
   //Create a mutex to prevent simultaneous access to the nonce cache
   if(!osCreateMutex(&context->nonceCacheMutex))
      return ERROR_OUT_OF_RESOURCES;
#endif

   //Open a TCP socket
   context->socket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);
   //Failed to open socket?
   if(!context->socket) return ERROR_OPEN_FAILED;

   //Set timeout for blocking functions
   error = socketSetTimeout(context->socket, INFINITE_DELAY);
   //Any error to report?
   if(error) return error;

   //Associate the socket with the relevant interface
   error = socketBindToInterface(context->socket, settings->interface);
   //Unable to bind the socket to the desired interface?
   if(error) return error;

   //Bind newly created socket to port 80
   error = socketBind(context->socket, &IP_ADDR_ANY, settings->port);
   //Failed to bind socket to port 80?
   if(error) return error;

   //Place socket in listening state
   error = socketListen(context->socket, settings->backlog);
   //Any failure to report?
   if(error) return error;

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief Start HTTP server
 * @param[in] context Pointer to the HTTP server context
 * @return Error code
 **/

error_t httpServerStart(HttpServerContext *context)
{
   uint_t i;
   OsTask *task;

   //Debug message
   TRACE_INFO("Starting HTTP server...\r\n");

   //Loop through client connections
   for(i = 0; i < context->settings.maxConnections; i++)
   {
      //Create a task to service a given HTTP client connection
      task = osCreateTask("HTTP Connection", httpConnectionTask,
         &context->connections[i], HTTP_SERVER_STACK_SIZE, HTTP_SERVER_PRIORITY);

      //Unable to create the task?
      if(task == OS_INVALID_HANDLE)
         return ERROR_OUT_OF_RESOURCES;
   }

   //Create the HTTP server listener task
   task = osCreateTask("HTTP Listener", httpListenerTask,
      context, HTTP_SERVER_STACK_SIZE, HTTP_SERVER_PRIORITY);

   //Unable to create the task?
   if(task == OS_INVALID_HANDLE)
      return ERROR_OUT_OF_RESOURCES;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief HTTP server listener task
 * @param[in] param Pointer to the HTTP server context
 **/

void httpListenerTask(void *param)
{
   uint_t i;
   uint_t counter;
   uint16_t clientPort;
   IpAddr clientIpAddr;
   HttpServerContext *context;
   HttpConnection* connection;
   Socket *socket;

   //Retrieve the HTTP server context
   context = (HttpServerContext *) param;

   //Process incoming connections to the server
   for(counter = 1; ; counter++)
   {
      //Debug message
      TRACE_INFO("Ready to accept a new connection...\r\n");

      //Limit the number of simultaneous connections to the HTTP server
      osWaitForSemaphore(&context->semaphore, INFINITE_DELAY);

      //Loop through available client connections
      for(i = 0; i < context->settings.maxConnections; i++)
      {
         //Point to the current connection
         connection = &context->connections[i];

         //Ready to service the client request?
         if(!connection->running)
         {
            //Accept an incoming connection
            socket = socketAccept(context->socket, &clientIpAddr, &clientPort);

            //Make sure the socket handle is valid
            if(socket != NULL)
            {
               //Debug message
               TRACE_INFO("Connection #%u established with client %s port %" PRIu16 "...\r\n",
                  counter, ipAddrToString(&clientIpAddr, NULL), clientPort);

               //Reference to the HTTP server settings
               connection->settings = &context->settings;
               //Reference to the HTTP server context
               connection->serverContext = context;
               //Reference to the new socket
               connection->socket = socket;

               //Set timeout for blocking functions
               socketSetTimeout(connection->socket, HTTP_SERVER_TIMEOUT);

               //The client connection task is now running...
               connection->running = TRUE;
               //Service the current connection request
               osSetEvent(&connection->startEvent);

               //We are done
               break;
            }
         }
      }
   }
}


/**
 * @brief Task that services requests from an active connection
 * @param[in] param Structure representing an HTTP connection with a client
 **/

void httpConnectionTask(void *param)
{
   error_t error;
   uint_t counter;
   HttpConnection *connection;

   //Point to the structure representing the HTTP connection
   connection = (HttpConnection *) param;

   //Endless loop
   while(1)
   {
      //Wait for an incoming connection attempt
      osWaitForEvent(&connection->startEvent, INFINITE_DELAY);

      //Initialize status code
      error = NO_ERROR;

#if (HTTP_SERVER_TLS_SUPPORT == ENABLED)
      //Use SSL/TLS to secure the connection?
      if(connection->settings->useTls)
      {
         //Debug message
         TRACE_INFO("Initializing SSL/TLS session...\r\n");

         //Start of exception handling block
         do
         {
            //Allocate SSL/TLS context
            connection->tlsContext = tlsInit();
            //Initialization failed?
            if(connection->tlsContext == NULL)
            {
               //Report an error
               error = ERROR_OUT_OF_MEMORY;
               //Exit immediately
               break;
            }

            //Select server operation mode
            error = tlsSetConnectionEnd(connection->tlsContext, TLS_CONNECTION_END_SERVER);
            //Any error to report?
            if(error) break;

            //Bind TLS to the relevant socket
            error = tlsSetSocket(connection->tlsContext, connection->socket);
            //Any error to report?
            if(error) break;

            //Invoke user-defined callback, if any
            if(connection->settings->tlsInitCallback != NULL)
            {
               //Perform SSL/TLS related initialization
               error = connection->settings->tlsInitCallback(connection, connection->tlsContext);
               //Any error to report?
               if(error) break;
            }

            //Establish a secure session
            error = tlsConnect(connection->tlsContext);
            //Any error to report?
            if(error) break;

            //End of exception handling block
         } while(0);
      }
      else
      {
         //Do not use SSL/TLS
         connection->tlsContext = NULL;
      }
#endif

      //Check status code
      if(!error)
      {
         //Process incoming requests
         for(counter = 0; counter < HTTP_SERVER_MAX_REQUESTS; counter++)
         {
            //Debug message
            TRACE_INFO("Waiting for request...\r\n");

            //Clear request header
            memset(&connection->request, 0, sizeof(HttpRequest));
            //Clear response header
            memset(&connection->response, 0, sizeof(HttpResponse));

            //Read the HTTP request header and parse its contents
            error = httpReadHeader(connection);
            //Any error to report?
            if(error)
            {
               //Debug message
               TRACE_INFO("No HTTP request received or parsing error...\r\n");
               break;
            }

#if (HTTP_SERVER_BASIC_AUTH_SUPPORT == ENABLED || HTTP_SERVER_DIGEST_AUTH_SUPPORT == ENABLED)
            //No Authorization header found?
            if(!connection->request.auth.found)
            {
               //Invoke user-defined callback, if any
               if(connection->settings->authCallback != NULL)
               {
                  //Check whether the access to the specified URI is authorized
                  connection->status = connection->settings->authCallback(connection,
                     connection->request.auth.user, connection->request.uri);
               }
               else
               {
                  //Access to the specified URI is allowed
                  connection->status = HTTP_ACCESS_ALLOWED;
               }
            }

            //Check access status
            if(connection->status == HTTP_ACCESS_ALLOWED)
            {
               //Access to the specified URI is allowed
               error = NO_ERROR;
            }
            else if(connection->status == HTTP_ACCESS_BASIC_AUTH_REQUIRED)
            {
               //Basic access authentication is required
               connection->response.auth.mode = HTTP_AUTH_MODE_BASIC;
               //Report an error
               error = ERROR_AUTH_REQUIRED;
            }
            else if(connection->status == HTTP_ACCESS_DIGEST_AUTH_REQUIRED)
            {
               //Digest access authentication is required
               connection->response.auth.mode = HTTP_AUTH_MODE_DIGEST;
               //Report an error
               error = ERROR_AUTH_REQUIRED;
            }
            else
            {
               //Access to the specified URI is denied
               error = ERROR_NOT_FOUND;
            }
#endif

            //Debug message
            TRACE_INFO("Sending HTTP response to the client...\r\n");

            //Check status code
            if(!error)
            {
               //Default HTTP header fields
               connection->response.version = connection->request.version;
               connection->response.noCache = FALSE;

#if (HTTP_SERVER_PERSISTENT_CONN_SUPPORT == ENABLED)
               //Persistent connections are accepted
               connection->response.keepAlive = connection->request.keepAlive;
#else
               //Connections are not persistent by default
               connection->response.keepAlive = FALSE;
#endif

#if (HTTP_SERVER_SSI_SUPPORT == ENABLED)
               //Use server-side scripting to dynamically generate HTML code?
               if(httpCompExtension(connection->request.uri, ".stm") ||
                  httpCompExtension(connection->request.uri, ".shtm") ||
                  httpCompExtension(connection->request.uri, ".shtml"))
               {
                  //SSI processing (Server Side Includes)
                  error = ssiExecuteScript(connection, connection->request.uri, 0);
               }
               else
#endif
               {
                  //Send the contents of the requested page
                  error = httpSendResponse(connection, connection->request.uri);
               }

               //The requested resource is not available?
               if(error == ERROR_NOT_FOUND)
               {
                  //Default HTTP header fields
                  connection->response.version = connection->request.version;
                  connection->response.statusCode = 200;
                  connection->response.keepAlive = connection->request.keepAlive;
                  connection->response.noCache = FALSE;
                  connection->response.location = NULL;
                  connection->response.contentType = mimeGetType(connection->request.uri);
                  connection->response.chunkedEncoding = TRUE;

                  //Invoke user-defined callback, if any
                  if(connection->settings->uriNotFoundCallback != NULL)
                  {
                     error = connection->settings->uriNotFoundCallback(connection,
                        connection->request.uri);
                  }
               }
            }

            //Bad request?
            if(error == ERROR_INVALID_REQUEST)
            {
               //Send an error 400 and close the connection immediately
               httpSendErrorResponse(connection, 400,
                  "The request is badly formed");
            }
            //Authorization required?
            else if(error == ERROR_AUTH_REQUIRED)
            {
               //Send an error 401 and keep the connection alive
               error = httpSendErrorResponse(connection, 401,
                  "Authorization required");
            }
            //Page not found?
            else if(error == ERROR_NOT_FOUND)
            {
               //Send an error 404 and keep the connection alive
               error = httpSendErrorResponse(connection, 404,
                  "The requested page could not be found");
            }

            //Internal error?
            if(error)
            {
               //Close the connection immediately
               break;
            }

            //Check whether the connection is persistent or not
            if(!connection->request.keepAlive || !connection->response.keepAlive)
            {
               //Close the connection immediately
               break;
            }
         }
      }

#if (HTTP_SERVER_TLS_SUPPORT == ENABLED)
      //Valid SSL/TLS context?
      if(connection->tlsContext != NULL)
      {
         //Debug message
         TRACE_INFO("Closing SSL/TLS session...\r\n");

         //Gracefully close SSL/TLS session
         tlsShutdown(connection->tlsContext);
         //Release context
         tlsFree(connection->tlsContext);
      }
#endif

      //Debug message
      TRACE_INFO("Graceful shutdown...\r\n");
      //Graceful shutdown
      socketShutdown(connection->socket, SOCKET_SD_BOTH);

      //Debug message
      TRACE_INFO("Closing socket...\r\n");
      //Close socket
      socketClose(connection->socket);

      //Ready to serve the next connection request...
      connection->running = FALSE;
      //Release semaphore
      osReleaseSemaphore(&connection->serverContext->semaphore);
   }
}


/**
 * @brief Send HTTP response header
 * @param[in] connection Structure representing an HTTP connection
 * @return Error code
 **/

error_t httpWriteHeader(HttpConnection *connection)
{
   error_t error;
   uint_t i;
   char_t *p;

   //HTTP version 0.9?
   if(connection->response.version == HTTP_VERSION_0_9)
   {
      //Enforce default parameters
      connection->response.keepAlive = FALSE;
      connection->response.chunkedEncoding = FALSE;
      //The size of the response body is not limited
      connection->response.byteCount = UINT_MAX;
      //We are done since HTTP 0.9 does not support Full-Response format
      return NO_ERROR;
   }

   //When generating dynamic web pages with HTTP 1.0, the only way to
   //signal the end of the body is to close the connection
   if(connection->response.version == HTTP_VERSION_1_0 &&
      connection->response.chunkedEncoding)
   {
      //Make the connection non persistent
      connection->response.keepAlive = FALSE;
      connection->response.chunkedEncoding = FALSE;
      //The size of the response body is not limited
      connection->response.byteCount = UINT_MAX;
   }
   else
   {
      //Limit the size of the response body
      connection->response.byteCount = connection->response.contentLength;
   }

   //Point to the beginning of the buffer
   p = connection->buffer;

   //The first line of a response message is the Status-Line, consisting
   //of the protocol version followed by a numeric status code and its
   //associated textual phrase
   p += sprintf(p, "HTTP/%u.%u %u ", MSB(connection->response.version),
      LSB(connection->response.version), connection->response.statusCode);

   //Retrieve the Reason-Phrase that corresponds to the Status-Code
   for(i = 0; i < arraysize(statusCodeList); i++)
   {
      //Check the status code
      if(statusCodeList[i].value == connection->response.statusCode)
      {
         //Append the textual phrase to the Status-Line
         p += sprintf(p, statusCodeList[i].message);
         //Break the loop and continue processing
         break;
      }
   }

   //Properly terminate the Status-Line
   p += sprintf(p, "\r\n");
   //The Server response-header field contains information about the
   //software used by the origin server to handle the request
   p += sprintf(p, "Server: Oryx Embedded HTTP Server\r\n");

   //Format Location field?
   if(connection->response.location != NULL)
   {
      //Set Location field
      p += sprintf(p, "Location: %s\r\n", connection->response.location);
   }

   //Persistent connection?
   if(connection->response.keepAlive)
   {
      //Set Connection field
      p += sprintf(p, "Connection: keep-alive\r\n");

      //Set Keep-Alive field
      p += sprintf(p, "Keep-Alive: timeout=%u, max=%u\r\n",
         HTTP_SERVER_TIMEOUT / 1000, HTTP_SERVER_MAX_REQUESTS);
   }
   else
   {
      //Set Connection field
      p += sprintf(p, "Connection: close\r\n");
   }

   //Prevent the client from using cache?
   if(connection->response.noCache)
   {
      //Set Pragma field
      p += sprintf(p, "Pragma: no-cache\r\n");
      //Set Cache-Control field
      p += sprintf(p, "Cache-Control: no-store, no-cache, must-revalidate\r\n");
      p += sprintf(p, "Cache-Control: post-check=0, pre-check=0\r\n");
   }

#if (HTTP_SERVER_BASIC_AUTH_SUPPORT == ENABLED)
   //Use basic access authentication?
   if(connection->response.auth.mode == HTTP_AUTH_MODE_BASIC)
   {
      //Set WWW-Authenticate field
      p += sprintf(p, "WWW-Authenticate: Basic realm=\"Protected Area\"\r\n");
   }
#endif
#if (HTTP_SERVER_DIGEST_AUTH_SUPPORT == ENABLED)
   //Use digest access authentication?
   if(connection->response.auth.mode == HTTP_AUTH_MODE_DIGEST)
   {
      size_t n;
      uint8_t opaque[16];

      //Set WWW-Authenticate field
      p += sprintf(p, "WWW-Authenticate: Digest\r\n");
      p += sprintf(p, "  realm=\"Protected Area\",\r\n");
      p += sprintf(p, "  qop=\"auth\",\r\n");
      p += sprintf(p, "  nonce=\"");

      //A server-specified data string which should be uniquely generated
      //each time a 401 response is made
      error = httpGenerateNonce(connection->serverContext, p, &n);
      //Any error to report?
      if(error) return error;

      //Advance pointer
      p += n;
      //Properly terminate the nonce string
      p += sprintf(p, "\",\r\n");

      //Format opaque parameter
      p += sprintf(p, "  opaque=\"");

      //Generate a random value
      error = connection->settings->prngAlgo->read(
         connection->settings->prngContext, opaque, 16);
      //Random number generation failed?
      if(error) return error;

      //Convert the byte array to hex string
      httpConvertArrayToHexString(opaque, 16, p);

      //Advance pointer
      p += 32;
      //Properly terminate the opaque string
      p += sprintf(p, "\"");

      //The STALE flag indicates that the previous request from the client
      //was rejected because the nonce value was stale
      if(connection->response.auth.stale)
         p += sprintf(p, ",\r\n  stale=TRUE");

      //Properly terminate the WWW-Authenticate field
      p += sprintf(p, "\r\n");
   }
#endif

   //Content type
   p += sprintf(p, "Content-Type: %s\r\n", connection->response.contentType);

   //Use chunked encoding transfer?
   if(connection->response.chunkedEncoding)
   {
      //Set Transfer-Encoding field
      p += sprintf(p, "Transfer-Encoding: chunked\r\n");
   }
   //Persistent connection?
   else if(connection->response.keepAlive)
   {
      //Set Content-Length field
      p += sprintf(p, "Content-Length: %" PRIuSIZE "\r\n", connection->response.contentLength);
   }

   //Terminate the header with an empty line
   p += sprintf(p, "\r\n");

   //Debug message
   TRACE_DEBUG("HTTP response header:\r\n%s", connection->buffer);

   //Send HTTP response header to the client
   error = httpSend(connection, connection->buffer,
      strlen(connection->buffer), HTTP_FLAG_DELAY);

   //Return status code
   return error;
}


/**
 * @brief Read data from client request
 * @param[in] connection Structure representing an HTTP connection
 * @param[out] data Buffer where to store the incoming data
 * @param[in] size Maximum number of bytes that can be received
 * @param[out] received Number of bytes that have been received
 * @param[in] flags Set of flags that influences the behavior of this function
 * @return Error code
 **/

error_t httpReadStream(HttpConnection *connection, void *data, size_t size, size_t *received, uint_t flags)
{
   error_t error;
   size_t n;

   //No data has been read yet
   *received = 0;

   //Chunked encoding transfer is used?
   if(connection->request.chunkedEncoding)
   {
      //Point to the output buffer
      char_t *p = data;

      //Read as much data as possible
      while(*received < size)
      {
         //End of HTTP request body?
         if(connection->request.lastChunk)
            return ERROR_END_OF_STREAM;

         //Acquire a new chunk when the current chunk
         //has been completely consumed
         if(connection->request.byteCount == 0)
         {
            //The size of each chunk is sent right before the chunk itself
            error = httpReadChunkSize(connection);
            //Failed to decode the chunk-size field?
            if(error) return error;

            //Any chunk whose size is zero terminates the data transfer
            if(!connection->request.byteCount)
            {
               //The user must be satisfied with data already on hand
               return (*received > 0) ? NO_ERROR : ERROR_END_OF_STREAM;
            }
         }

         //Limit the number of bytes to read at a time
         n = MIN(size - *received, connection->request.byteCount);

         //Read data
         error = httpReceive(connection, p, n, &n, flags);
         //Any error to report?
         if(error) return error;

         //Total number of data that have been read
         *received += n;
         //Remaining data still available in the current chunk
         connection->request.byteCount -= n;

         //The HTTP_FLAG_BREAK_CHAR flag causes the function to stop reading
         //data as soon as the specified break character is encountered
         if(flags & HTTP_FLAG_BREAK_CRLF)
         {
            //Check whether a break character has been received
            if(p[n - 1] == LSB(flags)) break;
         }
         //The HTTP_FLAG_WAIT_ALL flag causes the function to return
         //only when the requested number of bytes have been read
         else if(!(flags & HTTP_FLAG_WAIT_ALL))
         {
            break;
         }

         //Advance data pointer
         p += n;
      }
   }
   //Default encoding?
   else
   {
      //Return immediately if the end of the request body has been reached
      if(!connection->request.byteCount)
         return ERROR_END_OF_STREAM;

      //Limit the number of bytes to read
      n = MIN(size, connection->request.byteCount);

      //Read data
      error = httpReceive(connection, data, n, received, flags);
      //Any error to report
      if(error) return error;

      //Decrement the count of remaining bytes to read
      connection->request.byteCount -= *received;
   }

   //Successful read operation
   return NO_ERROR;
}


/**
 * @brief Write data to the client
 * @param[in] connection Structure representing an HTTP connection
 * @param[in] data Buffer containing the data to be transmitted
 * @param[in] length Number of bytes to be transmitted
 * @return Error code
 **/

error_t httpWriteStream(HttpConnection *connection, const void *data, size_t length)
{
   error_t error;
   uint_t n;

   //Use chunked encoding transfer?
   if(connection->response.chunkedEncoding)
   {
      //Any data to send?
      if(length > 0)
      {
         char_t s[8];

         //The chunk-size field is a string of hex digits
         //indicating the size of the chunk
         n = sprintf(s, "%X\r\n", length);

         //Send the chunk-size field
         error = httpSend(connection, s, n, HTTP_FLAG_DELAY);
         //Failed to send data?
         if(error) return error;

         //Send the chunk-data
         error = httpSend(connection, data, length, HTTP_FLAG_DELAY);
         //Failed to send data?
         if(error) return error;

         //Terminate the chunk-data by CRLF
         error = httpSend(connection, "\r\n", 2, HTTP_FLAG_DELAY);
      }
      else
      {
         //Any chunk whose size is zero may terminate the data
         //transfer and must be discarded
         error = NO_ERROR;
      }
   }
   //Default encoding?
   else
   {
      //The length of the body shall not exceed the value
      //specified in the Content-Length field
      length = MIN(length, connection->response.byteCount);

      //Send user data
      error = httpSend(connection, data, length, HTTP_FLAG_DELAY);

      //Decrement the count of remaining bytes to be transferred
      connection->response.byteCount -= length;
   }

   //Return status code
   return error;
}


/**
 * @brief Close output stream
 * @param[in] connection Structure representing an HTTP connection
 * @return Error code
 **/

error_t httpCloseStream(HttpConnection *connection)
{
   error_t error;

   //Use chunked encoding transfer?
   if(connection->response.chunkedEncoding)
   {
      //The chunked encoding is ended by any chunk whose size is zero
      error = httpSend(connection, "0\r\n\r\n", 5, HTTP_FLAG_NO_DELAY);
   }
   else
   {
      //Flush the send buffer
      error = httpSend(connection, "", 0, HTTP_FLAG_NO_DELAY);
   }

   //Return status code
   return error;
}


/**
 * @brief Send HTTP response
 * @param[in] connection Structure representing an HTTP connection
 * @param[in] uri NULL-terminated string containing the file to be sent in response
 * @return Error code
 **/

error_t httpSendResponse(HttpConnection *connection, const char_t *uri)
{
#if (HTTP_SERVER_FS_SUPPORT == ENABLED)
   error_t error;
   uint32_t length;
   size_t n;
   FsFile *file;

   //Retrieve the full pathname
   httpGetAbsolutePath(connection, uri,
      connection->buffer, HTTP_SERVER_BUFFER_SIZE);

   //Retrieve the size of the specified file
   error = fsGetFileSize(connection->buffer, &length);
   //The specified URI cannot be found?
   if(error) return ERROR_NOT_FOUND;

   //Open the file for reading
   file = fsOpenFile(connection->buffer, FS_FILE_MODE_READ);
   //Failed to open the file?
   if(!file) return ERROR_NOT_FOUND;
#else
   error_t error;
   size_t length;
   uint8_t *data;

   //Retrieve the full pathname
   httpGetAbsolutePath(connection, uri,
      connection->buffer, HTTP_SERVER_BUFFER_SIZE);

   //Get the resource data associated with the URI
   error = resGetData(connection->buffer, &data, &length);
   //The specified URI cannot be found?
   if(error) return error;
#endif

   //Format HTTP response header
   connection->response.statusCode = 200;
   connection->response.contentType = mimeGetType(uri);
   connection->response.chunkedEncoding = FALSE;
   connection->response.contentLength = length;

   //Send the header to the client
   error = httpWriteHeader(connection);
   //Any error to report?
   if(error)
   {
#if (HTTP_SERVER_FS_SUPPORT == ENABLED)
      //Close the file
      fsCloseFile(file);
#endif
      //Return status code
      return error;
   }

#if (HTTP_SERVER_FS_SUPPORT == ENABLED)
   //Send response body
   while(length > 0)
   {
      //Limit the number of bytes to read at a time
      n = MIN(length, HTTP_SERVER_BUFFER_SIZE);

      //Read data from the specified file
      error = fsReadFile(file, connection->buffer, n, &n);
      //End of input stream?
      if(error) break;

      //Send data to the client
      error = httpWriteStream(connection, connection->buffer, n);
      //Any error to report?
      if(error) break;

      //Decrement the count of remaining bytes to be transferred
      length -= n;
   }

   //Close the file
   fsCloseFile(file);

   //Successful file transfer?
   if(length == 0 && error == ERROR_END_OF_STREAM)
   {
      //Properly close the output stream
      error = httpCloseStream(connection);
   }
#else
   //Send response body
   error = httpWriteStream(connection, data, length);
   //Any error to report?
   if(error) return error;

   //Properly close output stream
   error = httpCloseStream(connection);
#endif

   //Return status code
   return error;
}


/**
 * @brief Send error response to the client
 * @param[in] connection Structure representing an HTTP connection
 * @param[in] statusCode HTTP status code
 * @param[in] message User message
 * @return Error code
 **/

error_t httpSendErrorResponse(HttpConnection *connection, uint_t statusCode, const char_t *message)
{
   error_t error;
   size_t length;

   //HTML response template
   static const char_t template[] =
      "<!doctype html>\r\n"
      "<html>\r\n"
      "<head><title>Error %03d</title></head>\r\n"
      "<body>\r\n"
      "<h2>Error %03d</h2>\r\n"
      "<p>%s</p>\r\n"
      "</body>\r\n"
      "</html>\r\n";

   //Compute the length of the response
   length = strlen(template) + strlen(message) - 4;

   //Format HTTP response header
   connection->response.version = connection->request.version;
   connection->response.statusCode = statusCode;
   connection->response.contentType = mimeGetType(".htm");
   connection->response.chunkedEncoding = FALSE;
   connection->response.contentLength = length;

   //Send the header to the client
   error = httpWriteHeader(connection);
   //Any error to report?
   if(error) return error;

   //Format HTML response
   sprintf(connection->buffer, template, statusCode, statusCode, message);

   //Send response body
   error = httpWriteStream(connection, connection->buffer, length);
   //Any error to report?
   if(error) return error;

   //Properly close output stream
   error = httpCloseStream(connection);
   //Return status code
   return error;
}


/**
 * @brief Send redirect response to the client
 * @param[in] connection Structure representing an HTTP connection
 * @param[in] statusCode HTTP status code (301 for permanent redirects)
 * @param[in] uri NULL-terminated string containing the redirect URI
 * @return Error code
 **/

error_t httpSendRedirectResponse(HttpConnection *connection, uint_t statusCode, const char_t *uri)
{
   error_t error;
   size_t length;

   //HTML response template
   static const char_t template[] =
      "<!doctype html>\r\n"
      "<html>\r\n"
      "<head><title>Moved</title></head>\r\n"
      "<body>\r\n"
      "<h2>Moved</h2>\r\n"
      "<p>This page has moved to <a href=\"%s\">%s</a>.</p>"
      "</body>\r\n"
      "</html>\r\n";

   //Compute the length of the response
   length = strlen(template) + 2 * strlen(uri) - 4;

   //Format HTTP response header
   connection->response.statusCode = statusCode;
   connection->response.location = uri;
   connection->response.contentType = mimeGetType(".htm");
   connection->response.chunkedEncoding = FALSE;
   connection->response.contentLength = length;

   //Send the header to the client
   error = httpWriteHeader(connection);
   //Any error to report?
   if(error) return error;

   //Format HTML response
   sprintf(connection->buffer, template, uri, uri);

   //Send response body
   error = httpWriteStream(connection, connection->buffer, length);
   //Any error to report?
   if(error) return error;

   //Properly close output stream
   error = httpCloseStream(connection);
   //Return status code
   return error;
}

#endif
