#include "VM204.h"


/**
 * @file relay.c
 * @brief Embedded resource management
 *
 * @section License
 *
 * Copyright (C) 2014 Velleman nv. All rights reserved.
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
 * @author Velleman nv (www.velleman.eu)
 * @version 1.0.0
 **/
void reboot() {
    SoftReset();
}

/**
 * Try to load the settings from the Flash.
 * @return the error
 */
char * json;
unsigned char bytes[4];
unsigned int length;

error_t ReadSettingsFromFlash() {

    SPIFlashInit();
    if (!flashIsEmpty()) {
        //root
        ReadSetting(appSettings.CardName, 32);
        ReadSetting(appSettings.CustomJSLink, 128);
        ReadSetting(appSettings.CustomJSLink, 128);
        ReadSetting(appSettings.key, 32);
        //Network
        ReadSetting(&appSettings.NetworkSetting.DhcpEnabled, 1);
        ReadSetting(appSettings.NetworkSetting.address, 16);
        ReadSetting(appSettings.NetworkSetting.Gateway, 16);
        ReadSetting(appSettings.NetworkSetting.SubnetMask, 16);
        ReadSetting(appSettings.NetworkSetting.PrimaryDNS, 16);
        ReadSetting(appSettings.NetworkSetting.SecondaryDNS, 16);
        ReadSetting(appSettings.NetworkSetting.MacAddress, 18);

        appSettings.NetworkSetting.PortWebServer = ReadInt();
        //Relays
        int i = 0;
        for (i = 0; i < 4; i++) {
            ReadSetting(appSettings.IoSettings.relays[i].Name, 32);
            appSettings.IoSettings.relays[i].PulseTime = ReadInt();
        }
        //Inputs
        for (i = 0; i < 4; i++) {
            ReadSetting(appSettings.IoSettings.inputs[i].Name, 32);
        }
        //Analog
        ReadSetting(appSettings.IoSettings.analog.Name, 32);
        ReadSetting(&appSettings.IoSettings.analog.MaxValue, 1);
        ReadSetting(&appSettings.IoSettings.analog.MinValue, 1);
        ReadSetting(&appSettings.IoSettings.analog.AlarmValue, 1);
        //Auth
        ReadSetting(appSettings.AuthSettings.Login, 32);
        ReadSetting(appSettings.AuthSettings.Password, 32);
        //Smtp
        ReadSetting(appSettings.EmailSettings.serverName, 64);

        appSettings.EmailSettings.serverPort = ReadInt();
        ReadSetting(appSettings.EmailSettings.userName, 64);
        ReadSetting(appSettings.EmailSettings.passWord, 64);
        ReadSetting(&appSettings.EmailSettings.useTls, 1);
        //Notifications
        for (i = 0; i < 10; i++) {
            ReadSetting(&appSettings.Notifications[i].enable, 1);
            ReadSetting(appSettings.Notifications[i].mail.recipients, 255);
        }
    }
    else
    {
        return  ERROR_FAILURE;
    }
    //CreateJsonFromSettings();
    return NO_ERROR;
}
int count = 0;
bool_t empty;
char byte = 0;
bool_t flashIsEmpty(void)
{
    unsigned int data[100];

    empty = TRUE;
    memset(data,0,100);
     SPIFlashReadArray(0,data,arraysize(data));

    for(count=0;count<10;count++)
    {
        byte = data[count];
        if(byte!=0xffffffff)
        {
            empty = FALSE;
        }
    }
    return empty;
}

int ReadInt(void) {
    int integer;
    char data[4];
    ReadSetting(data, 4);
    integer = data[3] | ((int) data[2] << 8) | ((int) data[1] << 16) | ((int) data[0] << 24);
    return integer;
}

void WriteInt(int val) {
    char data[4];
    data[0] = (val >> 24) & 0xFF;
    data[1] = (val >> 16) & 0xFF;
    data[2] = (val >> 8) & 0xFF;
    data[3] = val & 0xFF;
    SPIFlashWriteArray(data, 4);
}

void ReadSetting(char* dest, int bytes) {
    static int address = 0;
    if (bytes != 0) {
        SPIFlashReadArray(address, dest, bytes);
        address += bytes;
    } else
        address = 0;
}

error_t EraseSettings() {
    SPIFlashInit();
    SPIFlashEraseAll();
}

/**
 * Saves the settings to the Flash
 * @param file
 * @return error
 */
char* settings;
int lengthsettings;

void WriteSettingsToFlash() {
    SPIFlashInit();
    SPIFlashBeginWrite(0);
    //root
    SPIFlashWriteArray(appSettings.CardName, 32);
    SPIFlashWriteArray(appSettings.CustomJSLink, 128);
    SPIFlashWriteArray(appSettings.CustomJSLink, 128);
    SPIFlashWriteArray(appSettings.key, 32);
    //Network
    SPIFlashWriteArray(&appSettings.NetworkSetting.DhcpEnabled, 1);
    SPIFlashWriteArray(appSettings.NetworkSetting.address, 16);
    SPIFlashWriteArray(appSettings.NetworkSetting.Gateway, 16);
    SPIFlashWriteArray(appSettings.NetworkSetting.SubnetMask, 16);
    SPIFlashWriteArray(appSettings.NetworkSetting.PrimaryDNS, 16);
    SPIFlashWriteArray(appSettings.NetworkSetting.SecondaryDNS, 16);
    SPIFlashWriteArray(appSettings.NetworkSetting.MacAddress, 18);
    WriteInt(appSettings.NetworkSetting.PortWebServer);

    //Relays
    int i = 0;
    for (i = 0; i < 4; i++) {
        SPIFlashWriteArray(appSettings.IoSettings.relays[i].Name, 32);
        WriteInt(appSettings.IoSettings.relays[i].PulseTime);
    }
    //Inputs
    for (i = 0; i < 4; i++) {
        SPIFlashWriteArray(appSettings.IoSettings.inputs[i].Name, 32);
    }
    //Analog
    SPIFlashWriteArray(appSettings.IoSettings.analog.Name, 32);
    SPIFlashWriteArray(&appSettings.IoSettings.analog.MaxValue, 1);
    SPIFlashWriteArray(&appSettings.IoSettings.analog.MinValue, 1);
    SPIFlashWriteArray(&appSettings.IoSettings.analog.AlarmValue, 1);
    //Auth
    SPIFlashWriteArray(appSettings.AuthSettings.Login, 32);
    SPIFlashWriteArray(appSettings.AuthSettings.Password, 32);
    //Smtp
    SPIFlashWriteArray(appSettings.EmailSettings.serverName, 64);

    WriteInt(appSettings.EmailSettings.serverPort);
    SPIFlashWriteArray(appSettings.EmailSettings.userName, 64);
    SPIFlashWriteArray(appSettings.EmailSettings.passWord, 64);
    SPIFlashWriteArray(&appSettings.EmailSettings.useTls, 1);
    //Notifications
    for (i = 0; i < 10; i++) {
        SPIFlashWriteArray(&appSettings.Notifications[i].enable, 1);
        SPIFlashWriteArray(appSettings.Notifications[i].mail.recipients, 255);
    }
    appSettings.defaultSettings = FALSE;
}


static const char* alice = "alice@email.com;trudy@email.com";
static const char* bob = "bob@email.com";

void LoadDefaultSettings(YarrowContext* yarrowContext) {
    int i;
    //CardName
    strcpy(appSettings.CardName, "VM204");
    strcpy(appSettings.CustomJSLink, "");
    strcpy(appSettings.CustomCSSLink, "");
    //Get part of mac address hard coded in the PIC;
    srand(EMAC1SA0);
    gen_random(appSettings.key, 32);
    //NetworkSettings
    appSettings.NetworkSetting.DhcpEnabled = TRUE;
    appSettings.NetworkSetting.PortWebServer = 80;
    strcpy(appSettings.NetworkSetting.address, "192.168.1.204");
    strcpy(appSettings.NetworkSetting.SubnetMask, "255.255.255.0");
    strcpy(appSettings.NetworkSetting.Gateway, "192.168.1.1");
    strcpy(appSettings.NetworkSetting.PrimaryDNS, "8.8.8.8");
    strcpy(appSettings.NetworkSetting.SecondaryDNS, "8.8.4.4");
    //IOSettings
    strcpy(appSettings.IoSettings.inputs[0].Name, "INPUT1");
    strcpy(appSettings.IoSettings.inputs[1].Name, "INPUT2");
    strcpy(appSettings.IoSettings.inputs[2].Name, "INPUT3");
    strcpy(appSettings.IoSettings.inputs[3].Name, "INPUT4");
    strcpy(appSettings.IoSettings.relays[0].Name, "RELAY1");
    strcpy(appSettings.IoSettings.relays[1].Name, "RELAY2");
    strcpy(appSettings.IoSettings.relays[2].Name, "RELAY3");
    strcpy(appSettings.IoSettings.relays[3].Name, "RELAY4");
    appSettings.IoSettings.relays[0].PulseTime = 60;
    appSettings.IoSettings.relays[1].PulseTime = 60;
    appSettings.IoSettings.relays[2].PulseTime = 60;
    appSettings.IoSettings.relays[3].PulseTime = 60;

    strcpy(appSettings.IoSettings.analog.Name, "ANALOG");
    appSettings.IoSettings.analog.AlarmValue = 128;
    appSettings.IoSettings.analog.MinValue = 2147483647;

    //Auth Settings
    strcpy(appSettings.AuthSettings.Login, "admin");
    strcpy(appSettings.AuthSettings.Password, "VM204");

    //Email Settings
    //Auth
    //For EmailSettings check your local ISP or check your mail provider
    strcpy(appSettings.EmailSettings.userName, "email@example.com"); //ex. test@test.com
    strcpy(appSettings.EmailSettings.passWord, "password"); //Password
    appSettings.EmailSettings.serverPort = 587; //
    strcpy(appSettings.EmailSettings.serverName, "smtp.example.com"); //example smtp.live.com or smtp.gmail.com
    appSettings.EmailSettings.useTls = FALSE;
    //Notifications
    strcpy(appSettings.Notifications[NOTIFICATION_BOOT].mail.recipients, alice);
    appSettings.Notifications[NOTIFICATION_BOOT].enable = FALSE;


    for (i = 0; i < 4; i++) {
        //Rising
        strcpy(appSettings.Notifications[i].mail.recipients, alice);
        appSettings.Notifications[i].enable = FALSE;

        //Falling
        strcpy(appSettings.Notifications[i + 4].mail.recipients, alice);
        appSettings.Notifications[i + 4].enable = FALSE;
    }
    //Analog
    strcpy(appSettings.Notifications[NOTIFICATION_ANALOG].mail.recipients, alice);
    appSettings.Notifications[NOTIFICATION_ANALOG].enable = FALSE;
}

void UpdateNetworkSettings() {
    char changed = 0;
    char ip[16];
    if (netGetDefaultInterface()->ipv4Config.addr != 0) {
        strcpy(appSettings.NetworkSetting.address, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.addr, ip));
        changed = 1;
    }
    if (netGetDefaultInterface()->ipv4Config.defaultGateway != 0) {
        strcpy(appSettings.NetworkSetting.Gateway, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.defaultGateway, ip));
        changed = 1;
    }
    if (netGetDefaultInterface()->ipv4Config.subnetMask != 0) {
        strcpy(appSettings.NetworkSetting.SubnetMask, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.subnetMask, ip));
        changed = 1;
    }
    if (netGetDefaultInterface()->ipv4Config.dnsServer[0] != 0) {
        strcpy(appSettings.NetworkSetting.PrimaryDNS, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.dnsServer[0], ip));
        changed = 1;
    }
    if (netGetDefaultInterface()->ipv4Config.dnsServer[1] != 0) {
        strcpy(appSettings.NetworkSetting.SecondaryDNS, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.dnsServer[1], ip));
        changed = 1;
    }
    //if(changed)
    //CreateJsonFromSettings();
}

