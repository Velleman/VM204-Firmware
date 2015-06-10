/**
 * @file http_server_misc.c
 * @brief HTTP server (miscellaneous functions)
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
#define TRACE_LEVEL HTTP_TRACE_LEVEL

//Dependencies
#include <stdlib.h>
#include "core/net.h"
#include "http/http_server.h"
#include "http/http_server_auth.h"
#include "http/http_server_misc.h"
#include "str.h"
#include "path.h"
#include "debug.h"

//Check TCP/IP stack configuration
#if (HTTP_SERVER_SUPPORT == ENABLED)


/**
 * @brief Read HTTP request header and parse its contents
 * @param[in] connection Structure representing an HTTP connection
 * @return Error code
 **/

error_t httpReadHeader(HttpConnection *connection)
{
   error_t error;
   size_t length;
   char_t *token;
   char_t *p;
   char_t *s;

   //Set the maximum time the server will wait for an HTTP
   //request before closing the connection
   error = socketSetTimeout(connection->socket, HTTP_SERVER_IDLE_TIMEOUT);
   //Any error to report?
   if(error) return error;

   //Read the first line of the request
   error = httpReceive(connection, connection->buffer,
      HTTP_SERVER_BUFFER_SIZE - 1, &length, SOCKET_FLAG_BREAK_CRLF);
   //Unable to read any data?
   if(error) return error;

   //Revert to default timeout
   error = socketSetTimeout(connection->socket, HTTP_SERVER_TIMEOUT);
   //Any error to report?
   if(error) return error;

   //Properly terminate the string with a NULL character
   connection->buffer[length] = '\0';
   //Debug message
   TRACE_INFO("%s", connection->buffer);

   //The Request-Line begins with a method token
   token = strtok_r(connection->buffer, " \r\n", &p);
   //Unable to retrieve the method?
   if(!token) return ERROR_INVALID_REQUEST;

   //The Method token indicates the method to be performed on the
   //resource identified by the Request-URI
   error = strSafeCopy(connection->request.method, token, HTTP_SERVER_METHOD_MAX_LEN);
   //Any error to report?
   if(error) return ERROR_INVALID_REQUEST;

   //The Request-URI is following the method token
   token = strtok_r(NULL, " \r\n", &p);
   //Unable to retrieve the Request-URI?
   if(!token) return ERROR_INVALID_REQUEST;

   //Check whether a query string is present
   s = strchr(token, '?');

   //Query string found?
   if(s != NULL)
   {
      //Split the string
      *s = '\0';

      //Save the Request-URI
      error = httpDecodePercentEncodedString(token,
         connection->request.uri, HTTP_SERVER_URI_MAX_LEN);
      //Any error to report?
      if(error)
         return ERROR_INVALID_REQUEST;

      //Check the length of the query string
      if(strlen(s + 1) > HTTP_SERVER_QUERY_STRING_MAX_LEN)
         return ERROR_INVALID_REQUEST;

      //Save the query string
      strcpy(connection->request.queryString, s + 1);
   }
   else
   {
      //Save the Request-URI
      error = httpDecodePercentEncodedString(token,
         connection->request.uri, HTTP_SERVER_URI_MAX_LEN);
      //Any error to report?
      if(error)
         return ERROR_INVALID_REQUEST;

      //No query string
      connection->request.queryString[0] = '\0';
   }

   //Redirect to the default home page if necessary
   if(!strcasecmp(connection->request.uri, "/"))
      strcpy(connection->request.uri, connection->settings->defaultDocument);

   //Clean the resulting path
   pathCanonicalize(connection->request.uri);

   //The protocol version is following the Request-URI
   token = strtok_r(NULL, " \r\n", &p);

   //HTTP version 0.9?
   if(!token)
   {
      //Save version number
      connection->request.version = HTTP_VERSION_0_9;
      //Persistent connections are not supported
      connection->request.keepAlive = FALSE;
   }
   //HTTP version 1.0?
   else if(!strcasecmp(token, "HTTP/1.0"))
   {
      //Save version number
      connection->request.version = HTTP_VERSION_1_0;
      //By default connections are not persistent
      connection->request.keepAlive = FALSE;
   }
   //HTTP version 1.1?
   else if(!strcasecmp(token, "HTTP/1.1"))
   {
      //Save version number
      connection->request.version = HTTP_VERSION_1_1;
      //HTTP 1.1 makes persistent connections the default
      connection->request.keepAlive = TRUE;
   }
   //HTTP version not supported?
   else
   {
      return ERROR_INVALID_REQUEST;
   }

   //Default value for properties
   connection->request.chunkedEncoding = FALSE;
   connection->request.contentLength = 0;

   //HTTP 0.9 does not support Full-Request
   if(connection->request.version >= HTTP_VERSION_1_0)
   {
      //Local variables
      char_t firstChar;
      char_t *separator;
      char_t *name;
      char_t *value;

      //This variable is used to decode header fields that span multiple lines
      firstChar = '\0';

      //Parse the header fields of the HTTP request
      while(1)
      {
         //Decode multiple-line header field
         error = httpReadHeaderField(connection, connection->buffer,
            HTTP_SERVER_BUFFER_SIZE, &firstChar);
         //Any error to report?
         if(error) return error;

         //Debug message
         TRACE_DEBUG("%s", connection->buffer);

         //An empty line indicates the end of the header fields
         if(!strcmp(connection->buffer, "\r\n"))
            break;

         //Check whether a separator is present
         separator = strchr(connection->buffer, ':');

         //Separator found?
         if(separator != NULL)
         {
            //Split the line
            *separator = '\0';

            //Get field name and value
            name = strTrimWhitespace(connection->buffer);
            value = strTrimWhitespace(separator + 1);

            //Connection field found?
            if(!strcasecmp(name, "Connection"))
            {
               //Check whether persistent connections are supported or not
               if(!strcasecmp(value, "keep-alive"))
                  connection->request.keepAlive = TRUE;
               else if(!strcasecmp(value, "close"))
                  connection->request.keepAlive = FALSE;
            }
            //Transfer-Encoding field found?
            else if(!strcasecmp(name, "Transfer-Encoding"))
            {
               //Check whether chunked encoding is used
               if(!strcasecmp(value, "chunked"))
                  connection->request.chunkedEncoding = TRUE;
            }
            //Content-Type field found?
            else if(!strcasecmp(name, "Content-Type"))
            {
               //Parse Content-Type field
               httpParseContentTypeField(connection, value);
            }
            //Content-Length field found?
            else if(!strcasecmp(name, "Content-Length"))
            {
               //Get the length of the body data
               connection->request.contentLength = atoi(value);
            }
            //Authorization field found?
            else if(!strcasecmp(name, "Authorization"))
            {
               //Parse Authorization field
               httpParseAuthField(connection, value);
            }
         }
      }
   }

   //Prepare to read the HTTP request body
   if(connection->request.chunkedEncoding)
   {
      connection->request.byteCount = 0;
      connection->request.firstChunk = TRUE;
      connection->request.lastChunk = FALSE;
   }
   else
   {
      connection->request.byteCount = connection->request.contentLength;
   }

   //The request header has been successfully parsed
   return NO_ERROR;
}


/**
 * @brief Read multiple-line header field
 * @param[in] connection Structure representing an HTTP connection
 * @param[out] buffer Buffer where to store the header field
 * @param[in] size Size of the buffer, in bytes
 * @param[in,out] firstChar Leading character of the header line
 * @return Error code
 **/

error_t httpReadHeaderField(HttpConnection *connection,
   char_t *buffer, size_t size, char_t *firstChar)
{
   error_t error;
   size_t n;
   size_t length;

   //This is the actual length of the header field
   length = 0;

   //The process of moving from a multiple-line representation of a header
   //field to its single line representation is called unfolding
   do
   {
      //Check the length of the header field
      if((length + 1) >= size)
      {
         //Report an error
         error = ERROR_INVALID_REQUEST;
         //Exit immediately
         break;
      }

      //NULL character found?
      if(*firstChar == '\0')
      {
         //Prepare to decode the first header field
         length = 0;
      }
      //LWSP character found?
      else if(*firstChar == ' ' || *firstChar == '\t')
      {
         //Unfolding is accomplished by regarding CRLF immediately
         //followed by a LWSP as equivalent to the LWSP character
         buffer[length] = *firstChar;
         //The current header field spans multiple lines
         length++;
      }
      //Any other character?
      else
      {
         //Restore the very first character of the header field
         buffer[0] = *firstChar;
         //Prepare to decode a new header field
         length = 1;
      }

      //Read data until a CLRF character is encountered
      error = httpReceive(connection, buffer + length,
         size - 1 - length, &n, SOCKET_FLAG_BREAK_CRLF);
      //Any error to report?
      if(error) break;

      //Update the length of the header field
      length += n;
      //Properly terminate the string with a NULL character
      buffer[length] = '\0';

      //An empty line indicates the end of the header fields
      if(!strcmp(buffer, "\r\n"))
         break;

      //Read the next character to detect if the CRLF is immediately
      //followed by a LWSP character
      error = httpReceive(connection, firstChar,
         sizeof(char_t), &n, SOCKET_FLAG_WAIT_ALL);
      //Any error to report?
      if(error) break;

      //LWSP character found?
      if(*firstChar == ' ' || *firstChar == '\t')
      {
         //CRLF immediately followed by LWSP as equivalent to the LWSP character
         if(length >= 2)
         {
            if(buffer[length - 2] == '\r' || buffer[length - 1] == '\n')
            {
               //Remove trailing CRLF sequence
               length -= 2;
               //Properly terminate the string with a NULL character
               buffer[length] = '\0';
            }
         }
      }

      //A header field may span multiple lines...
   } while(*firstChar == ' ' || *firstChar == '\t');

   //Return status code
   return error;
}


/**
 * @brief Parse Content-Type field
 * @param[in] connection Structure representing an HTTP connection
 * @param[in] value Content-Type field value
 **/

void httpParseContentTypeField(HttpConnection *connection, char_t *value)
{
#if (HTTP_SERVER_MULTIPART_TYPE_SUPPORT == ENABLED)
   size_t n;
   char_t *p;
   char_t *token;

   //Retrieve type
   token = strtok_r(value, "/", &p);
   //Any parsing error?
   if(token == NULL) return;

   //The boundary parameter makes sense only for the multipart content-type
   if(!strcasecmp(token, "multipart"))
   {
      //Skip subtype
      token = strtok_r(NULL, ";", &p);
      //Any parsing error?
      if(token == NULL) return;

      //Retrieve parameter name
      token = strtok_r(NULL, "=", &p);
      //Any parsing error?
      if(token == NULL) return;

      //Trim whitespace characters
      token = strTrimWhitespace(token);

      //Check parameter name
      if(!strcasecmp(token, "boundary"))
      {
         //Retrieve parameter value
         token = strtok_r(NULL, ";", &p);
         //Any parsing error?
         if(token == NULL) return;

         //Trim whitespace characters
         token = strTrimWhitespace(token);
         //Get the length of the boundary string
         n = strlen(token);

         //Check the length of the boundary string
         if(n < HTTP_SERVER_BOUNDARY_MAX_LEN)
         {
            //Copy the boundary string
            strncpy(connection->request.boundary, token, n);
            //Properly terminate the string
            connection->request.boundary[n] = '\0';

            //Save the length of the boundary string
            connection->request.boundaryLength = n;
         }
      }
   }
#endif
}


/**
 * @brief Read chunk-size field from the input stream
 * @param[in] connection Structure representing an HTTP connection
 **/

error_t httpReadChunkSize(HttpConnection *connection)
{
   error_t error;
   size_t n;
   char_t *end;
   char_t s[8];

   //First chunk to be received?
   if(connection->request.firstChunk)
   {
      //Clear the flag
      connection->request.firstChunk = FALSE;
   }
   else
   {
      //Read the CRLF that follows the previous chunk-data field
      error = httpReceive(connection, s, sizeof(s) - 1, &n, SOCKET_FLAG_BREAK_CRLF);
      //Any error to report?
      if(error) return error;

      //Properly terminate the string with a NULL character
      s[n] = '\0';

      //The chunk data must be terminated by CRLF
      if(strcmp(s, "\r\n"))
         return ERROR_WRONG_ENCODING;
   }

   //Read the chunk-size field
   error = httpReceive(connection, s, sizeof(s) - 1, &n, SOCKET_FLAG_BREAK_CRLF);
   //Any error to report?
   if(error) return error;

   //Properly terminate the string with a NULL character
   s[n] = '\0';
   //Remove extra whitespaces
   strRemoveTrailingSpace(s);

   //Retrieve the size of the chunk
   connection->request.byteCount = strtoul(s, &end, 16);

   //No valid conversion could be performed?
   if(end == s || *end != '\0')
      return ERROR_WRONG_ENCODING;

   //Any chunk whose size is zero terminates the data transfer
   if(!connection->request.byteCount)
   {
      //The end of the HTTP request body has been reached
      connection->request.lastChunk = TRUE;

      //Skip the trailer
      while(1)
      {
         //Read a complete line
         error = httpReceive(connection, s, sizeof(s) - 1, &n, SOCKET_FLAG_BREAK_CRLF);
         //Unable to read any data?
         if(error) return error;

         //Properly terminate the string with a NULL character
         s[n] = '\0';

         //The trailer is terminated by an empty line
         if(!strcmp(s, "\r\n"))
            break;
      }
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Send data to the client
 * @param[in] connection Structure representing an HTTP connection
 * @param[in] data Pointer to a buffer containing the data to be transmitted
 * @param[in] length Number of bytes to be transmitted
 * @param[in] flags Set of flags that influences the behavior of this function
 **/

error_t httpSend(HttpConnection *connection,
   const void *data, size_t length, uint_t flags)
{
   error_t error;

#if (HTTP_SERVER_TLS_SUPPORT == ENABLED)
   //Check whether a secure connection is being used
   if(connection->tlsContext != NULL)
   {
      //Use SSL/TLS to transmit data to the client
      error = tlsWrite(connection->tlsContext, data, length, flags);
   }
   else
#endif
   {
      //Transmit data to the client
      error = socketSend(connection->socket, data, length, NULL, flags);
   }

   //Return status code
   return error;
}


/**
 * @brief Receive data from the client
 * @param[in] connection Structure representing an HTTP connection
 * @param[out] data Buffer into which received data will be placed
 * @param[in] size Maximum number of bytes that can be received
 * @param[out] received Actual number of bytes that have been received
 * @param[in] flags Set of flags that influences the behavior of this function
 * @return Error code
 **/

error_t httpReceive(HttpConnection *connection,
   void *data, size_t size, size_t *received, uint_t flags)
{
   error_t error;

#if (HTTP_SERVER_TLS_SUPPORT == ENABLED)
   //Check whether a secure connection is being used
   if(connection->tlsContext != NULL)
   {
      //Use SSL/TLS to receive data from the client
      error = tlsRead(connection->tlsContext, data, size, received, flags);
   }
   else
#endif
   {
      //Receive data from the client
      error = socketReceive(connection->socket, data, size, received, flags);
   }

   //Return status code
   return error;
}


/**
 * @brief Retrieve the full pathname to the specified resource
 * @param[in] connection Structure representing an HTTP connection
 * @param[in] relative String containing the relative path to the resource
 * @param[out] absolute Resulting string containing the absolute path
 * @param[in] maxLen Maximum acceptable path length
 **/

void httpGetAbsolutePath(HttpConnection *connection,
   const char_t *relative, char_t *absolute, size_t maxLen)
{
   //Copy the root directory
   strcpy(absolute, connection->settings->rootDirectory);

   //Append the specified path
   pathCombine(absolute, relative, maxLen);

   //Clean the resulting path
   pathCanonicalize(absolute);
}


/**
 * @brief Compare filename extension
 * @param[in] filename Filename whose extension is to be checked
 * @param[in] extension String defining the extension to be checked
 * @return TRUE is the filename matches the given extension, else FALSE
 **/

bool_t httpCompExtension(const char_t *filename, const char_t *extension)
{
   uint_t n;
   uint_t m;

   //Get the length of the specified filename
   n = strlen(filename);
   //Get the length of the extension
   m = strlen(extension);

   //Check the length of the filename
   if(n < m)
      return FALSE;

   //Compare extensions
   if(!strncasecmp(filename + n - m, extension, m))
      return TRUE;
   else
      return FALSE;
}


/**
 * @brief Decode a percent-encoded string
 * @param[in] input NULL-terminated string to be decoded
 * @param[out] output NULL-terminated string resulting from the decoding process
 * @param[in] outputSize Size of the output buffer in bytes
 * @return Error code
 **/

error_t httpDecodePercentEncodedString(const char_t *input,
   char_t *output, size_t outputSize)
{
   size_t i;
   char_t buffer[3];

   //Check parameters
   if(input == NULL || output == NULL)
      return ERROR_INVALID_PARAMETER;

   //Decode the percent-encoded string
   for(i = 0; *input != '\0' && i < outputSize; i++)
   {
      //Check current character
      if(*input == '+')
      {
         //Replace '+' characters with spaces
         output[i] = ' ';
         //Advance data pointer
         input++;
      }
      else if(input[0] == '%' && input[1] != '\0' && input[2] != '\0')
      {
         //Process percent-encoded characters
         buffer[0] = input[1];
         buffer[1] = input[2];
         buffer[2] = '\0';
         //String to integer conversion
         output[i] = strtoul(buffer, NULL, 16);
         //Advance data pointer
         input += 3;
      }
      else
      {
         //Copy any other characters
         output[i] = *input;
         //Advance data pointer
         input++;
      }
   }

   //Check whether the output buffer runs out of space
   if(i >= outputSize)
      return ERROR_FAILURE;

   //Properly terminate the resulting string
   output[i] = '\0';
   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Convert byte array to hex string
 * @param[in] input Point to the byte array
 * @param[in] inputLength Length of the byte array
 * @param[out] output NULL-terminated string resulting from the conversion
 * @return Error code
 **/

void httpConvertArrayToHexString(const uint8_t *input,
   size_t inputLength, char_t *output)
{
   size_t i;

   //Hex conversion table
   static const char_t hexDigit[] =
   {
      '0', '1', '2', '3', '4', '5', '6', '7',
      '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
   };

   //Process byte array
   for(i = 0; i < inputLength; i++)
   {
      //Convert upper nibble
      output[i * 2] = hexDigit[(input[i] >> 4) & 0x0F];
      //Then convert lower nibble
      output[i * 2 + 1] = hexDigit[input[i] & 0x0F];
   }

   //Properly terminate the string with a NULL character
   output[i * 2] = '\0';
}

#endif
