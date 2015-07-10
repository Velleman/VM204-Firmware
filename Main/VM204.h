/**
 * @file pic32_eth_starter_kit.h
 * @brief PIC32 Ethernet Starter Kit
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

#ifndef _PIC32_ETH_START_KIT_H
#define _PIC32_ETH_START_KIT_H

//Dependencies
#include "compiler_port.h"
#include "yarrow.h"
#include "core/net.h"
#include "shared.h"
#include "smtp/smtp_client.h"
#include "http/http_server.h"
//LEDs
#define LED1_MASK (1 << 4)
#define LED2_MASK (1 << 5)
#define LED3_MASK (1 << 6)

//Push buttons
#define SW1_MASK (1 << 0)
#define SW2_MASK (1 << 1)
#define SW3_MASK (1 << 2)
#define SW4_MASK (1 << 3)
#define FACTORY_DEFAULT_MASK (1 << 7)

#define SD_DETECT PORTAbits.RA9

#define FIRMWARE_VERSION "1.0"

#define AUTH_LOGIN "admin"
#define AUTH_PASS "test"

int CreateMailAddressFromString(char * string,SmtpMailAddr* recipients);
error_t sendDebug(HttpConnection* connection);
error_t sendRelayStatus(HttpConnection* connection);
error_t sendIoStatus(HttpConnection *connection);
error_t sendNames(HttpConnection *connection);
error_t processAlarmSettings(HttpConnection *connection);
error_t processEmailSettings(HttpConnection *connection);
error_t sendCardSettings(HttpConnection *connection);
error_t processLogin(HttpConnection *connection);
error_t processNames(HttpConnection* connection);
error_t processNetworkSettings(HttpConnection* connection);
error_t processAuthenticationSettings(HttpConnection* connection);
void LoadDefaultSettings(YarrowContext* yarrowContext);
error_t SaveSettings(void);
error_t EraseSettings(void);
error_t ReadSettingsFromFlash(void);
void WriteSettingsToFlash(void);
void WriteInt(int val);
void ReadSetting(char* dest,int bytes);
void GoToBootLoader(void);
void UpdateNetworkSettings(void);
bool_t checkFalling(bool_t previous,bool_t current);
bool_t checkRising(bool_t previous,bool_t current);
error_t getCurrentTime(void);
void CreateJsonFromSettings(void);
void vTimerCallback(void*  pxTimer );
error_t sendTestMailResponse(HttpConnection* connection);
#endif
