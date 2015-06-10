#include "VM204.h"
//#include "SPIFlash.h"
//#include "SPIFlash.h"
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
    //root
    ReadSetting(appSettings.CardName,32);
    ReadSetting(appSettings.CustomJSLink,128);
    ReadSetting(appSettings.CustomJSLink,128);
    ReadSetting(appSettings.key,32);
    //Network
    ReadSetting(&appSettings.NetworkSetting.DhcpEnabled,1);
    ReadSetting(appSettings.NetworkSetting.address,16);
    ReadSetting(appSettings.NetworkSetting.Gateway,16);
    ReadSetting(appSettings.NetworkSetting.SubnetMask,16);
    ReadSetting(appSettings.NetworkSetting.PrimaryDNS,16);
    ReadSetting(appSettings.NetworkSetting.SecondaryDNS,16);
    ReadSetting(appSettings.NetworkSetting.MacAddress,18);
    char webport[4];
    ReadSetting(webport,4);
    appSettings.NetworkSetting.PortWebServer = webport[3] | ((int) webport[2] << 8) | ((int) webport[1] << 16) | ((int) webport[0] << 24);
    //Relays
    int i=0;
    for(i=0;i<4;i++)
    {
        ReadSetting(appSettings.IoSettings.relays[i].Name,64);
        
    }
    //Inputs
    for(i=0;i<4;i++)
    {
        ReadSetting(appSettings.IoSettings.inputs[i].Name,64);
    }
    //Analog
    ReadSetting(appSettings.IoSettings.analog.Name,64);
    ReadSetting(&appSettings.IoSettings.analog.MaxValue,1);
    ReadSetting(&appSettings.IoSettings.analog.MinValue,1);
    ReadSetting(&appSettings.IoSettings.analog.AlarmValue,1);
    //Auth
    ReadSetting(appSettings.AuthSettings.Login,32);
    ReadSetting(appSettings.AuthSettings.Password,32);
    //Smtp
    ReadSetting(appSettings.EmailSettings.serverName,64);
    char smtpport[4];
    ReadSetting(smtpport,4);
    appSettings.EmailSettings.serverPort = smtpport[3] | ((int) smtpport[2] << 8) | ((int) smtpport[1] << 16) | ((int) smtpport[0] << 24);
    ReadSetting(appSettings.EmailSettings.userName,64);
    ReadSetting(appSettings.EmailSettings.passWord,64);
    ReadSetting(&appSettings.EmailSettings.useTls,1);
    //Notifications
    for(i=0;i<10;i++)
    {
        ReadSetting(&appSettings.Notifications[i].enable,1);
        ReadSetting(appSettings.Notifications[i].mail.recipients,255);
    }
    //CreateJsonFromSettings();
    return NO_ERROR;
}

void ReadSetting(char* dest,int bytes)
{
    static int address = 0;
    if(bytes != 0)
    {
        SPIFlashReadArray(address,dest,bytes);
        address += bytes;
    }
    else
        address = 0;
}

error_t EraseSettings() {
    SPIFlashInit();
    SPIFlashEraseAll();
}


void GoToBootLoader()
{
    SPIFlashInit();
    SPIFlashBeginWrite(4095);
    char_t boot[8]= {1,1,1,1,1,1,1,1};
    SPIFlashWriteArray(boot,8);
    char_t data[8];
    SPIFlashReadArray(4095,data,8);
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
    SPIFlashWriteArray(appSettings.CardName,32);
    SPIFlashWriteArray(appSettings.CustomJSLink,128);
    SPIFlashWriteArray(appSettings.CustomJSLink,128);
    SPIFlashWriteArray(appSettings.key,32);
    //Network
    SPIFlashWriteArray(&appSettings.NetworkSetting.DhcpEnabled,1);
    SPIFlashWriteArray(appSettings.NetworkSetting.address,16);
    SPIFlashWriteArray(appSettings.NetworkSetting.Gateway,16);
    SPIFlashWriteArray(appSettings.NetworkSetting.SubnetMask,16);
    SPIFlashWriteArray(appSettings.NetworkSetting.PrimaryDNS,16);
    SPIFlashWriteArray(appSettings.NetworkSetting.SecondaryDNS,16);
    SPIFlashWriteArray(appSettings.NetworkSetting.MacAddress,18);

    char webserverport[4];
    webserverport[0] = (appSettings.NetworkSetting.PortWebServer >> 24) & 0xFF;
    webserverport[1] = (appSettings.NetworkSetting.PortWebServer >> 16) & 0xFF;
    webserverport[2] = (appSettings.NetworkSetting.PortWebServer >> 8) & 0xFF;
    webserverport[3] = appSettings.NetworkSetting.PortWebServer & 0xFF;
    SPIFlashWriteArray(webserverport,4);

    //Relays
    int i=0;
    for(i=0;i<4;i++)
    {
        SPIFlashWriteArray(appSettings.IoSettings.relays[i].Name,64);
    }
    //Inputs
    for(i=0;i<4;i++)
    {
        SPIFlashWriteArray(appSettings.IoSettings.inputs[i].Name,64);
    }
    //Analog
    SPIFlashWriteArray(appSettings.IoSettings.analog.Name,64);
    SPIFlashWriteArray(&appSettings.IoSettings.analog.MaxValue,1);
    SPIFlashWriteArray(&appSettings.IoSettings.analog.MinValue,1);
    SPIFlashWriteArray(&appSettings.IoSettings.analog.AlarmValue,1);
    //Auth
    SPIFlashWriteArray(appSettings.AuthSettings.Login,32);
    SPIFlashWriteArray(appSettings.AuthSettings.Password,32);
    //Smtp
    SPIFlashWriteArray(appSettings.EmailSettings.serverName,64);

    char smtpport[4];
    smtpport[0] = (appSettings.EmailSettings.serverPort >> 24) & 0xFF;
    smtpport[1] = (appSettings.EmailSettings.serverPort >> 16) & 0xFF;
    smtpport[2] = (appSettings.EmailSettings.serverPort >> 8) & 0xFF;
    smtpport[3] = appSettings.EmailSettings.serverPort & 0xFF;
    SPIFlashWriteArray(smtpport,4);
    SPIFlashWriteArray(appSettings.EmailSettings.userName,64);
    SPIFlashWriteArray(appSettings.EmailSettings.passWord,64);
    SPIFlashWriteArray(&appSettings.EmailSettings.useTls,1);
    //Notifications
    for(i=0;i<10;i++)
    {
        SPIFlashWriteArray(&appSettings.Notifications[i].enable,1);
        SPIFlashWriteArray(appSettings.Notifications[i].mail.recipients,255);
    }
}


static const char* alice = "alice@email.com;trudy@email.com";
static const char* bob = "bob@email.com";
void LoadDefaultSettings(YarrowContext* yarrowContext) {

    //CardName
    strcpy(appSettings.CardName, "VM204");
    strcpy(appSettings.CustomJSLink,"");
    strcpy(appSettings.CustomCSSLink,"");
    //Get part of mac address hard coded in the PIC;
    srand(EMAC1SA0);
    gen_random(appSettings.key,32);
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
    strcpy(appSettings.IoSettings.analog.Name, "ANALOG");
    appSettings.IoSettings.analog.AlarmValue = 128;
    appSettings.IoSettings.analog.MinValue = 2147483647;

    //Auth Settings
    strcpy(appSettings.AuthSettings.Login, "admin");
    strcpy(appSettings.AuthSettings.Password, "VM204");

    //Email Settings
    //Auth
    //For EmailSettings check your local ISP or check your mail provider
    strcpy(appSettings.EmailSettings.userName,"email@example.com"); //ex. test@test.com
    strcpy(appSettings.EmailSettings.passWord,NULL); //Password
    appSettings.EmailSettings.serverPort = 587; //
    strcpy(appSettings.EmailSettings.serverName,"smtp.example.com"); //example smtp.live.com or smtp.gmail.com
    appSettings.EmailSettings.useTls = FALSE;
    //Notifications
    strcpy(appSettings.Notifications[NOTIFICATION_BOOT].mail.recipients,alice);
    appSettings.Notifications[NOTIFICATION_BOOT].enable = FALSE;

    int i;
    for (i = 0; i < 4; i++) {
        //Rising
        strcpy(appSettings.Notifications[i].mail.recipients, alice);        
        appSettings.Notifications[i].enable = FALSE;

        //Falling
        strcpy(appSettings.Notifications[i + 4].mail.recipients,alice);
        appSettings.Notifications[i + 4].enable = FALSE;
    }
    //Analog
    strcpy(appSettings.Notifications[NOTIFICATION_ANALOG].mail.recipients, alice);
    appSettings.Notifications[NOTIFICATION_ANALOG].enable = FALSE;
}

void UpdateNetworkSettings() {
    char changed = 0;
    char ip[16];
    if (netGetDefaultInterface()->ipv4Config.addr != 0)
    {
        strcpy(appSettings.NetworkSetting.address, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.addr, ip));
        changed = 1;
    }
    if (netGetDefaultInterface()->ipv4Config.defaultGateway != 0)
    {
        strcpy(appSettings.NetworkSetting.Gateway, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.defaultGateway, ip));
        changed = 1;
    }
    if (netGetDefaultInterface()->ipv4Config.subnetMask != 0)
    {
        strcpy(appSettings.NetworkSetting.SubnetMask, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.subnetMask, ip));
        changed = 1;
    }
    if (netGetDefaultInterface()->ipv4Config.dnsServer[0] != 0)
    {
        strcpy(appSettings.NetworkSetting.PrimaryDNS, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.dnsServer[0], ip));
        changed = 1;
    }
    if (netGetDefaultInterface()->ipv4Config.dnsServer[1] != 0)
    {
        strcpy(appSettings.NetworkSetting.SecondaryDNS, ipv4AddrToString(netGetDefaultInterface()->ipv4Config.dnsServer[1], ip));
        changed = 1;
    }
    //if(changed)
        //CreateJsonFromSettings();
}


