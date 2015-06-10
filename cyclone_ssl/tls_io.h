/**
 * @file tls_io.h
 * @brief I/O abstraction layer
 *
 * @section License
 *
 * Copyright (C) 2010-2015 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneSSL Open.
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

#ifndef _TLS_IO_H
#define _TLS_IO_H

//Dependencies
#include "tls.h"

//Use BSD socket API?
#if (TLS_BSD_SOCKET_SUPPORT == ENABLED)
   //Windows port?
   #if defined(_WIN32)
      //Undefine conflicting definitions
      #undef htons
      #undef htonl
      #undef ntohs
      #undef ntohl

      //Dependencies
      #include <winsock2.h>
   #else
      //External functions
      extern int_t send(int_t s, const void *data, int_t length, int_t flags);
      extern int_t recv(int_t s, void *data, int_t size, int_t flags);
   #endif
#endif

//I/O abstraction layer
error_t tlsIoWrite(TlsContext *context, const void *data, size_t length);
error_t tlsIoRead(TlsContext *context, void *data, size_t length);

#endif
