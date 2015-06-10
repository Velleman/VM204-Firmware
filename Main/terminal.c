/**
 * @file Terminal.c
 * @brief Terminal protocol
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
 * @section Description
 *
 * The Terminal is a service which the user can control the relay card VM204
 * 
 *
 * @author Oryx Embedded (www.oryx-embedded.com)
 * @version 1.4.2
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL STD_SERVICES_TRACE_LEVEL

//Dependencies
#include "terminal.h"
//Check TCP/IP stack configuration
#if (TCP_IP_STATIC_OS_RESOURCES == ENABLED)

//UDP Terminal service
static OsTask udpTerminalTaskStruct;
static uint_t udpTerminalTaskStack[Terminal_SERVICE_STACK_SIZE];

#endif

/**
 * @brief Start TCP Terminal service
 * @return Error code
 **/

error_t tcpTerminalStart(void) {
    error_t error;
    Socket *socket;
    OsTask *task;

    //Debug message
    TRACE_INFO("Starting TCP Terminal service...\r\n");

    //Open a TCP socket
    socket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_PROTOCOL_TCP);
    //Failed to open socket?
    if (!socket) return ERROR_OPEN_FAILED;

    //Start of exception handling block
    do {
        //Bind the newly created socket to port 6000
        error = socketBind(socket, &IP_ADDR_ANY, appSettings.NetworkSetting.PortTerminal);
        //Failed to bind the socket to the desired port?
        if (error) break;

        //Place the socket into listening mode
        error = socketListen(socket);
        //Any error to report?
        if (error) break;

        //Create a task to handle incoming connection requests
        task = osTaskCreate("TCP Terminal Listener", tcpTerminalListenerTask,
                socket, TERMINAL_SERVICE_STACK_SIZE, TERMINAL_SERVICE_PRIORITY);

        //Unable to create the task?
        if (task == OS_INVALID_HANDLE) {
            //Report an error to the calling function
            error = ERROR_OUT_OF_RESOURCES;
            break;
        }

        //End of exception handling block
    } while (0);

    //Any error to report?
    if (error) {
        //Clean up side effects...
        socketClose(socket);
    }

    //Return status code
    return error;
}

/**
 * @brief Task handling connection requests
 * @param[in] param Pointer to the Terminal service context
 **/

void tcpTerminalListenerTask(void *param) {
    error_t error;
    uint16_t clientPort;
    IpAddr clientIpAddr;
    Socket *serverSocket;
    Socket *clientSocket;
    TerminalServiceContext *context;
    OsTask *task;

    //Point to the listening socket
    serverSocket = (Socket *) param;

    //Main loop
    while (1) {
        //Accept an incoming connection
        clientSocket = socketAccept(serverSocket, &clientIpAddr, &clientPort);
        //Check whether a valid connection request has been received
        if (!clientSocket) continue;

        //Debug message
        TRACE_INFO("Terminal service: connection established with client %s port %" PRIu16 "\r\n",
                ipAddrToString(&clientIpAddr, NULL), clientPort);

        //The socket operates in non-blocking mode
        error = socketSetTimeout(clientSocket, 0);

        //Any error to report?
        if (error) {
            //Close socket
            socketClose(clientSocket);
            //Wait for an incoming connection attempt
            continue;
        }

        //Allocate resources for the new connection
        context = osMemAlloc(sizeof (TerminalServiceContext));

        //Failed to allocate memory?
        if (!context) {
            //Close socket
            socketClose(clientSocket);
            //Wait for an incoming connection attempt
            continue;
        }

        //Record the handle of the newly created socket
        context->socket = clientSocket;

        //Create a task to service the current connection
        task = osTaskCreate("TCP Terminal Connection", tcpTerminalConnectionTask,
                context, TERMINAL_SERVICE_STACK_SIZE, TERMINAL_SERVICE_PRIORITY);

        //Did we encounter an error?
        if (task == OS_INVALID_HANDLE) {
            //Close socket
            socketClose(clientSocket);
            //Release resources
            osMemFree(context);
        }
    }
}

/**
 * @brief TCP Terminal service implementation
 * @param[in] param Pointer to the Terminal service context
 **/
bool_t isLoggedIn = FALSE;
char * command;
size_t n;
size_t writeIndex;
size_t readIndex;
size_t bufferLength;
size_t bytesToWrite;
int diff;
TerminalServiceContext *context;

void tcpTerminalConnectionTask(void *param) {
    error_t error;

    size_t rxByteCount;
    size_t txByteCount;
    systime_t startTime;
    systime_t duration;
    SocketEventDesc eventDesc;

    NetInterface *interface;

    //Get a pointer to the context
    context = (TerminalServiceContext *) param;
    //Get current time
    startTime = osGetTickCount();

    //Initialize variables
    writeIndex = 0;
    readIndex = 0;
    bufferLength = 0;
    rxByteCount = 0;
    txByteCount = 0;
    bytesToWrite;
    bool_t firstConnection = FALSE;

    eventDesc.socket = context->socket;
    eventDesc.eventMask = SOCKET_EVENT_RX_READY | SOCKET_EVENT_TX_READY;
    //Main loop
    while (1) {

        //Wait for an event to be fired
        error = socketPoll(&eventDesc, 1, NULL, TERMINAL_TIMEOUT);
        //Timeout error or any other exception to report?
        if (error) break;

        //The socket is available for reading
        if (eventDesc.eventFlags & SOCKET_EVENT_RX_READY) {
            //Read as much data as possible
            n = min(TERMINAL_BUFFER_SIZE - writeIndex, TERMINAL_BUFFER_SIZE - bufferLength);

            //Read incoming data
            error = socketReceive(context->socket, context->buffer, 100, &n, 0);
            //Any error to report?
            if (error) break;

            //Increment write index
            writeIndex += n;
            //Wrap around if necessary
            if (writeIndex >= TERMINAL_BUFFER_SIZE)
                writeIndex = 0;

            //Increment buffer length
            bufferLength += n;
            //Total number of bytes received
            rxByteCount += n;
        }

        //The socket is available for writing?
        if (eventDesc.eventFlags & SOCKET_EVENT_TX_READY) {

            n = min(TERMINAL_BUFFER_SIZE - readIndex, bufferLength);

            command = strtok(context->buffer, " ");
            if (command) {
                if (strcmp(command, "STATUS") == 0) {
                    if (isLoggedIn) {
                        command = strtok(NULL, " ");
                        if (command) {
                            if (strcmp(command, "outputs") >= 0) {
                                strcpy(context->buffer, "OUTPUTS: \r\n1 ");
                                strcat(context->buffer, READRY1 ? "ON \r\n" : "OFF \r\n");
                                strcat(context->buffer, "2 ");
                                strcat(context->buffer, READRY2 ? "ON \r\n" : "OFF \r\n");
                                strcat(context->buffer, "3 ");
                                strcat(context->buffer, READRY3 ? "ON \r\n" : "OFF \r\n");
                                strcat(context->buffer, "4 ");
                                strcat(context->buffer, READRY4 ? "ON \r\n" : "OFF \r\n");
                                strcat(context->buffer, "END\r\n");
                                bytesToWrite = strlen(context->buffer);
                                error = socketSend(context->socket, context->buffer, bytesToWrite, &n, 0);
                                memset(context->buffer, 0, sizeof (context->buffer));
                            } else if (!strcmp(command, "inputs")) {
                                char string[100];

                                strcpy(string, "INPUTS: \r\n1 ");
                                strcat(string, READIN1 ? "ON \r\n" : "OFF \r\n");
                                strcat(string, "2 ");
                                strcat(string, READIN2 ? "ON \r\n" : "OFF \r\n");
                                strcat(string, "3 ");
                                strcat(string, READIN3 ? "ON \r\n" : "OFF \r\n");
                                strcat(string, "4 ");
                                strcat(string, READIN4 ? "ON \r\n" : "OFF \r\n");
                                strcat(string, "END\r\n");
                                bytesToWrite = strlen(string);
                                strcpy(context->buffer, string);
                                error = socketSend(context->socket, context->buffer, bytesToWrite, &n, 0);
                                memset(context->buffer, 0, sizeof (context->buffer));

                            } else if (!strcmp(command, "analog")) {
                                //memset(context->buffer, 0, sizeof (context->buffer));
                                strcpy(context->buffer, "\r\nAnalog Value: ");
                                char buffer[10];
                                getAnalogInputInString(buffer);
                                strcat(context->buffer, buffer);
                                strcat(context->buffer, "V\r\n");
                                strcat(context->buffer, "END\r\n");
                                bytesToWrite = strlen(context->buffer);
                                error = socketSend(context->socket, context->buffer + readIndex, bytesToWrite, &n, 0);

                            } else {
                                sendCommandNotFound(context);
                            }
                        }else
                            sendCommandNotFound(context);
                    } else {
                        sendAuthRequired(context);
                    }
                } else if (strcmp(command, "OUTPUT") == 0) {
                    if (isLoggedIn) {
                        command = strtok(NULL, " ");
                        if (command) {
                            if (!strcmp(command, "1")) {
                                command = strtok(NULL, " ");
                                if (command) {
                                    if (!strcmp(command, "ON")) {
                                        error = 200;
                                        RY1 = 1;
                                    } else if (!strcmp(command, "OFF")) {
                                        error = 200;
                                        RY1 = 0;
                                    } else if (!strcmp(command, "TOGGLE")) {
                                        error = 200;
                                        RY1 = !RY1;
                                    } else {
                                        error = 404;
                                    }
                                }else
                                    error = 404;

                            } else if (!strcmp(command, "2")) {
                                command = strtok(NULL, " ");
                                if (command) {
                                    if (!strcmp(command, "ON")) {
                                        error = 200;
                                        RY2 = 1;
                                    } else if (!strcmp(command, "OFF")) {
                                        error = 200;
                                        RY2 = 0;
                                    } else if (!strcmp(command, "TOGGLE")) {
                                        error = 200;
                                        RY2 = !RY2;
                                    } else {
                                        error = 404;
                                    }
                                }else
                                    error = 404;
                            } else if (!strcmp(command, "3")) {
                                command = strtok(NULL, " ");
                                if (command) {
                                    if (!strcmp(command, "ON")) {
                                        error = 200;
                                        RY3 = 1;
                                    } else if (!strcmp(command, "OFF")) {
                                        error = 200;
                                        RY3 = 0;
                                    } else if (!strcmp(command, "TOGGLE")) {
                                        error = 200;
                                        RY3 = !RY3;
                                    } else {
                                        error = 404;
                                    }
                                }else
                                    error = 404;
                            } else if (!strcmp(command, "4")) {
                                command = strtok(NULL, " ");
                                if (command) {
                                    if (!strcmp(command, "ON")) {
                                        error = 200;
                                        RY4 = 1;
                                    } else if (!strcmp(command, "OFF")) {
                                        error = 200;
                                        RY4 = 0;
                                    } else if (!strcmp(command, "TOGGLE")) {
                                        error = 200;
                                        RY4 = !RY4;
                                    } else {
                                        error = 404;
                                    }
                                }
                                else
                                    error = 404;
                            } else {
                                error = 404;
                            }
                        }
                        if (error == 200) {
                            error = 0;
                            sendOK(context);
                            memset(context->buffer, 0, sizeof (context->buffer));
                            saveRelays();

                        } else {
                            if (error = 404)
                                sendCommandNotFound(context);
                            memset(context->buffer, 0, sizeof (context->buffer));
                            error = 0;
                            n = 0;
                        }
                    } else {
                        sendAuthRequired(context);
                    }
                } else if (strcmp(command, "QUIT") == 0) {
                    strcpy(context->buffer, "\r\nBYE!!!");

                    error = socketSend(context->socket, context->buffer + readIndex, n, &n, 0);
                    //Adjust timeout value
                    socketSetTimeout(context->socket, TERMINAL_TIMEOUT);
                    //Graceful shutdown
                    socketShutdown(context->socket, SOCKET_SD_BOTH);
                } else if (!strcmp(command, "AUTH")) {
                    command = strtok(NULL, " ");
                    if (command) {
                        if (!strcmp(command, appSettings.AuthSettings.Login)) {
                            command = strtok(NULL, " ");
                            if (command) {
                                if (!strcmp(command, appSettings.AuthSettings.Password)) {
                                    isLoggedIn = TRUE;
                                    error = sendOK(context);
                                    memset(context->buffer, 0, sizeof (context->buffer));
                                } else {
                                    error = sendAuthFailed(context);
                                    memset(context->buffer, 0, sizeof (context->buffer));
                                }
                            } else {
                                error = sendAuthFailed(context);
                                memset(context->buffer, 0, sizeof (context->buffer));
                            }
                        } else {
                            error = sendAuthFailed(context);
                            memset(context->buffer, 0, sizeof (context->buffer));
                        }
                    } else {
                        error = sendAuthFailed(context);
                        memset(context->buffer, 0, sizeof (context->buffer));
                    }
                } else if (!strcmp(command, "REBOOT")) {
                    if (isLoggedIn)
                    {
                        reboot();
                        Nop();
                        Nop();
                        Nop();
                        Nop();
                    }
                    else {
                        sendAuthRequired(context);
                        memset(context->buffer, 0, sizeof (context->buffer));
                    }

                } else {
                    sendCommandNotFound(context);
                    memset(context->buffer, 0, sizeof (context->buffer));
                }
            }
            //Any error to report?
            if (error && error != ERROR_TIMEOUT) {
                Nop();
                osDelay(200);
                break;
            }

            //Increment read index
            readIndex += n;
            //Wrap around if necessary
            if (readIndex >= TERMINAL_BUFFER_SIZE)
                readIndex = 0;

            //Update buffer length

            bufferLength -= n;
            //Total number of bytes sent
            txByteCount += n;
            //("txByteCount =%"PRIuSIZE,txByteCount);

        }
    }

    //Adjust timeout value
    socketSetTimeout(context->socket, TERMINAL_TIMEOUT);
    //Graceful shutdown
    socketShutdown(context->socket, SOCKET_SD_BOTH);
    //Compute total duration
    duration = osGetTickCount() - startTime;

    //Debug message
    TRACE_INFO("Terminal service: %" PRIuSIZE " bytes received, %" PRIuSIZE " bytes sent in %" PRIu32 " ms\r\n",
            rxByteCount, txByteCount, duration);

    //Close socket
    socketClose(context->socket);
    //Release previously allocated memory
    osMemFree(context);

    //Kill ourselves
    osTaskDelete(NULL);
}

error_t sendAuthRequired(TerminalServiceContext *context) {

    memset(context->buffer, 0, sizeof (context->buffer));
    strcpy(context->buffer, "301 Authentication Required\r\n");

    return socketSend(context->socket, context->buffer + readIndex, bytesToWrite, &n, 0);
}

error_t sendAuthFailed(TerminalServiceContext *context) {


    memset(context->buffer, 0, sizeof (context->buffer));
    strcpy(context->buffer, "302 Authentication Failed\r\n");
    bytesToWrite = strlen(context->buffer);
    return socketSend(context->socket, context->buffer, bytesToWrite, &n, 0);
}

error_t sendOK(TerminalServiceContext *context) {

    strcpy(context->buffer, "200 OK\r\n");
    bytesToWrite = strlen(context->buffer);
    return socketSend(context->socket, context->buffer, bytesToWrite, &n, 0);
}

error_t sendCommandNotFound(TerminalServiceContext *context) {

    memset(context->buffer, 0, sizeof (context->buffer));
    strcpy(context->buffer, "404 Command Not Found\r\n");
    bytesToWrite = strlen(context->buffer);
    return socketSend(context->socket, context->buffer, bytesToWrite, &n, 0);
}

