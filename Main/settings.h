/* 
 * File:   settings.h
 * Author: bn
 *
 * Created on 26 november 2014, 13:27
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#include "IoDataTypes.h"
#include "core/net.h"
#include "smtp/smtp_client.h"
#include "date_time.h"
#include "yarrow.h"
#ifdef	__cplusplus
extern "C" {
#endif

#define NOTIFICATION_INPUT1_RISING 0
#define NOTIFICATION_INPUT2_RISING 1
#define NOTIFICATION_INPUT3_RISING 2
#define NOTIFICATION_INPUT4_RISING 3
#define NOTIFICATION_INPUT1_FALLING 4
#define NOTIFICATION_INPUT2_FALLING 5
#define NOTIFICATION_INPUT3_FALLING 6
#define NOTIFICATION_INPUT4_FALLING 7
#define NOTIFICATION_BOOT 8
#define NOTIFICATION_ANALOG 9
#define NOTIFICATIONS_SIZE 10
#define SUBJECT_INPUT_RISING "[%s] %s has been activated on %s (UTC)"
#define SUBJECT_INPUT_FALLING "[%s] %s has been deactivated on %s (UTC)"
#define SUBJECT_ANALOG "[%s] %s is currently %s on %s (UTC)"
#define SUBJECT_BOOT "[%s] The Card has booted"

    typedef struct {
        char recipients[256];
    } Vm204Mail;

    typedef struct NetworkSettings {
        bool_t DhcpEnabled;
        char address[16];
        char Gateway[16];
        char SubnetMask[16];
        char PrimaryDNS[16];
        char SecondaryDNS[16];
        char MacAddress[18];
        int PortWebServer;
    } NetworkSettings;

    typedef struct IOSettings {
        //Relays
        Relay_t relays[4];
        //Inputs
        Input_t inputs[4];
        //Analog
        Analog_t analog;
    } IOSettings;

    typedef struct Notification {
        bool_t enable;
        Vm204Mail mail;
    } Notification;

    typedef struct AuthSettings {
        char Login[32];
        char Password[32];
    } AuthSettings;

    typedef struct Vm204SmtpAuthInfo {
        char serverName[64];
        int serverPort;
        char userName[64];
        char passWord[64];
        bool_t useTls;
    } Vm204SmtpAuthInfo;

    typedef struct Settings {
        NetworkSettings NetworkSetting;
        IOSettings IoSettings;
        AuthSettings AuthSettings;
        Vm204SmtpAuthInfo EmailSettings;
        Notification Notifications[10];
        char json[4000];
        char CardName[32];
        char CustomJSLink[128];
        char CustomCSSLink[128];
        DateTime date;
        char key[32];
        YarrowContext yarrowContext;
    } Settings;

#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

