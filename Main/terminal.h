/**
 * @file echo.h
 * @brief Echo protocol
 *
 * @section License
 *
 * Copyright (C) 2010-2014 Oryx Embedded. All rights reserved.
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
 * @author Oryx Embedded (www.oryx-embedded.com)
 * @version 1.4.2
 **/

#ifndef _TERMINAL_H
#define _TERMINAL_H

//Dependencies
#include "tcp_ip_stack.h"
#include "socket.h"
#include "shared.h"
#include "debug.h"
#include "IoDataTypes.h"
#include "relays.h"
#include "inputs.h"
#include "analog.h"
//Stack size required to run the echo service
#ifndef TERMINAL_SERVICE_STACK_SIZE
#define TERMINAL_SERVICE_STACK_SIZE 600
#elif (TERMINAL_SERVICE_STACK_SIZE < 1)
#error TERMINAL_SERVICE_STACK_SIZE parameter is not valid
#endif

//Priority at which the echo service should run
#ifndef TERMINAL_SERVICE_PRIORITY
#define TERMINAL_SERVICE_PRIORITY 1
#elif (TERMINAL_SERVICE_PRIORITY < 0)
#error TERMINAL_SERVICE_PRIORITY parameter is not valid
#endif

//Size of the buffer for input/output operations
#ifndef TERMINAL_BUFFER_SIZE
#define TERMINAL_BUFFER_SIZE 1500
#elif (TERMINAL_BUFFER_SIZE < 1)
#error TERMINAL_BUFFER_SIZE parameter is not valid
#endif

//Maximum time the TCP echo server will wait before closing the connection
#ifndef TERMINAL_TIMEOUT
#define TERMINAL_TIMEOUT 60000
#elif (TERMINAL_TIMEOUT < 1)
#error TERMINAL_TIMEOUT parameter is not valid
#endif

//Echo service port
#define TERMINAL_PORT appSettings.NetworkSetting.PortTerminal

/**
 * @brief TERMINAL service context
 **/

typedef struct {
    Socket *socket;
    char_t buffer[TERMINAL_BUFFER_SIZE];
} TerminalServiceContext;


//TCP terminal service related functions
error_t tcpTerminalStart(void);
void tcpTerminalListenerTask(void *param);
void tcpTerminalConnectionTask(void *param);

//
error_t sendAuthRequired(TerminalServiceContext *context);
error_t sendAuthFailed(TerminalServiceContext *context);
error_t sendOK(TerminalServiceContext *context);
error_t sendCommandNotFound(TerminalServiceContext *context);
#endif
