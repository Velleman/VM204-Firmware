/**
 * @file main.c
 * @brief Main routine
 *
 * @section License
 *
 * Copyright (C) 2010-2014 Velleman nv. All rights reserved.
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
 * @author Brecht Nuyttens (www.velleman.eu)
 * @version 1.0.0
 **/

//Application configuration

//Dependencies
#include <stdlib.h>
#include <p32xxxx.h>
#include <plib.h>
#include "main.h"
#include "FreeRTOS.h"
#include "os_port.h"
#include "core/net.h"
#include "drivers/pic32mx_eth.h"
#include "dhcp/dhcp_client.h"
#include "VM204.h"
#include "HardwareProfile.h"
#include "ext_int_driver.h"
#include "http/http_server.h"
#include "sntp/sntp_client.h"
#include "error.h"
#include "debug.h"
#include "echo.h"
#include "discovery.h"
#include "SPIMACEEPROM.h"
#include "adc10.h"
#include "timers.h"
#include "path.h"
#include "analog.h"
#include "AlarmSetting.h"
#include "relays.h"
#include "inputs.h"
#include "IoDataTypes.h"
#include "alarmSetting.h"
#include "SPIFlash.h"
#include "core/net.h"
#include "drivers/lan8720.h"
#include "p32xxxx.h"

//Number of simultaneous client connections
#define APP_HTTP_MAX_CONNECTIONS 2
#define NUM_TIMERS 5

/* An array to hold handles to the created timers. */
 TimerHandle_t xTimers[ NUM_TIMERS ];

//Global variables
HttpServerContext httpServerContext;
HttpConnection httpConnections[APP_HTTP_MAX_CONNECTIONS]; 

//Forward declaration of functions
error_t httpServerCgiCallback(HttpConnection *connection, const char_t *param);
error_t httpServerUriNotFoundCallback(HttpConnection *connection,const char_t *uri);
HttpAccessStatus httpServerAuthCallback(HttpConnection *connection,const char_t *user, const char_t *uri);

//Global variables
DhcpClientSettings dhcpClientSettings;
DhcpClientCtx dhcpClientContext;
uint8_t seed[32];
HttpServerSettings httpServerSettings;
HttpServerContext httpServerContext;

////PIC32 onfiguration settings
#pragma config FSRSSEL = PRIORITY_7
#pragma config FMIIEN = OFF
#pragma config FETHIO = OFF
#pragma config FUSBIDIO = OFF
#pragma config FVBUSONIO = OFF
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL = MUL_20
#pragma config UPLLIDIV = DIV_1
#pragma config UPLLEN = OFF
#pragma config FPLLODIV = DIV_1
#pragma config FNOSC = PRIPLL
#pragma config FSOSCEN = OFF
#pragma config IESO = ON
#pragma config POSCMOD = XT
#pragma config OSCIOFNC = OFF
#pragma config FPBDIV = DIV_2
#pragma config FCKSM = CSDCMD
#pragma config WDTPS = PS1048576
#pragma config FWDTEN = OFF
//#pragma config DEBUG = ON
#pragma config ICESEL = ICS_PGx1
#pragma config PWP = OFF
#pragma config BWP = OFF
#pragma config CP = OFF

//External 3 interrupt service routine
void __attribute__((interrupt(ipl1), vector(_EXTERNAL_3_VECTOR))) ext3IrqWrapper(void);
//Ethernet interrupt service routine
void __attribute__((interrupt(ipl1), vector(_ETH_VECTOR))) ethIrqWrapper(void);

NetInterface *interface;
Settings appSettings;

//	Exception handler:
  static enum {
  	EXCEP_IRQ = 0,			// interrupt
  	EXCEP_AdEL = 4,			// address error exception (load or ifetch)
  	EXCEP_AdES,				// address error exception (store)
  	EXCEP_IBE,				// bus error (ifetch)
  	EXCEP_DBE,				// bus error (load/store)
  	EXCEP_Sys,				// syscall
  	EXCEP_Bp,				// breakpoint
  	EXCEP_RI,				// reserved instruction
  	EXCEP_CpU,				// coprocessor unusable
  	EXCEP_Overflow,			// arithmetic overflow
  	EXCEP_Trap,				// trap (possible divide by zero)
  	EXCEP_IS1 = 16,			// implementation specfic 1
  	EXCEP_CEU,				// CorExtend Unuseable
  	EXCEP_C2E				// coprocessor 2
  } _excep_code;

  static unsigned int _epc_code;
  static unsigned int _excep_addr;

  // this function overrides the normal _weak_ generic handler
  void _general_exception_handler(void)
  {
  	asm volatile("mfc0 %0,$13" : "=r" (_excep_code));
  	asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

  	_epc_code = (_excep_code & 0x0000007C) >> 2;
  	 	while (1) {
  		// Examine _excep_code to identify the type of exception
  		// Examine _excep_addr to find the address that caused the exception
  		Nop();
  		Nop();
  		Nop();
                Nop();

   	}
  }//	End of exception handler

  /**
 * @brief System initialization
 **/

void systemInit(void)
{
   //DDPCONbits.JTAGEN = 0;

   //Enable optimal performance
   SYSTEMConfigPerformance(80000000);

   //Configures peripheral bus divisor
   OSCSetPBDIV(OSC_PB_DIV_2);

   //Enable multi-vectored mode
   INTEnableSystemMultiVectoredInt();
}

/*
 * Random generator
*/
void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int i;
    for (i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

/**
 * @brief Main entry point
 * @return Unused value
 **/
error_t error;
char* settings;
int lengthsettings;
int_t main(void) {
    
    MacAddr macAddr;
    Ipv4Addr ipv4Addr;
    Ipv6Addr ipv6Addr;
    BYTE mac[6];
    OsTask *task;    
    
    //System initialization
   systemInit();

   //Initialize kernel
   osInitKernel();
   //Configure debug UART
   debugInit(115200);

    //Start-up message
    TRACE_INFO("\r\n");
    TRACE_INFO("***********************************\r\n");
    TRACE_INFO("*** VM204 Firmwawre ***\r\n");
    TRACE_INFO("***********************************\r\n");
    TRACE_INFO("Copyright: 2015 Velleman nv\r\n");
    TRACE_INFO("Compiled: %s %s\r\n", __DATE__, __TIME__);
    TRACE_INFO("Target: PIC32MX695F512H\r\n");
    TRACE_INFO("\r\n");

    //IO configuration
    ioInit();

    //PRNG initialization
    error = yarrowInit(&appSettings.yarrowContext);
    //Any error to report?
    if (error) {
        //Debug message
        TRACE_ERROR("Error: PRNG initialization failed (%d)\r\n", error);
        //Exit immediately
        return ERROR_FAILURE;
    }

    //Generate a random seed

    //Properly seed the PRNG
    error = yarrowSeed(&appSettings.yarrowContext, seed, sizeof (seed));
    //Any error to report?
    if (error) {
        //Debug message
        TRACE_ERROR("Failed to seed PRNG!\r\n");
    }

    

    //TCP/IP stack initialization
    error = tcpIpStackInit();
    //Any error to report?
    if (error) {
        //Debug message
        TRACE_ERROR("Failed to initialize TCP/IP stack!\r\n");
    }

#if defined(SPIFLASH_CS_TRIS)
    char rest = READFACTORYDEFAULT;
    if(!READFACTORYDEFAULT)
    {
        EraseSettings();
        LoadDefaultSettings(&appSettings.yarrowContext);
        WriteSettingsToFlash();
    }
    else
    {
        LoadDefaultSettings(&appSettings.yarrowContext);
        error = ReadSettingsFromFlash();
        if(error)
        {
            reboot();
        }
    }
#endif



    //Configure the first Ethernet interface
    interface = &netInterface[0];

    //Set interface name
    netSetInterfaceName(interface, "eth0");
    //Set host name
    netSetHostname(interface, appSettings.CardName);
    //Select the relevant network adapter
    netSetDriver(interface, &pic32mxEthDriver);
    netSetPhyDriver(interface, &lan8720PhyDriver);
    //Set host MAC address

    //Initialize network interface
    error = netConfigInterface(interface);
    //Any error to report?
    if (error) {
        //Debug message
        TRACE_ERROR("Failed to configure interface %s!\r\n", interface->name);
    }
    //Update mac address
    netGetMacAddr(interface,&macAddr);
    macAddrToString(&macAddr,appSettings.NetworkSetting.MacAddress);
   
#if (IPV4_SUPPORT == ENABLED)

    if(appSettings.NetworkSetting.DhcpEnabled == TRUE)
    {
    //Get default settings
    dhcpClientGetDefaultSettings(&dhcpClientSettings);
    //Set the network interface to be configured by DHCP
    dhcpClientSettings.interface = interface;
    //Disable rapid commit option
    dhcpClientSettings.rapidCommit = FALSE;

    //DHCP client initialization
    error = dhcpClientInit(&dhcpClientContext, &dhcpClientSettings);
    //Failed to initialize DHCP client?
    if (error) {
        //Debug message
        TRACE_ERROR("Failed to initialize DHCP client!\r\n");
    }

    //Start DHCP client
    error = dhcpClientStart(&dhcpClientContext);
    //Failed to start DHCP client?
    if (error) {
        //Debug message
        TRACE_ERROR("Failed to start DHCP client!\r\n");
    }
    }
    else
    {
    //Set IPv4 host address
    ipv4StringToAddr(appSettings.NetworkSetting.address, &ipv4Addr);
    ipv4SetHostAddr(interface, ipv4Addr);

    //Set subnet mask
    ipv4StringToAddr(appSettings.NetworkSetting.SubnetMask, &ipv4Addr);
    ipv4SetSubnetMask(interface, ipv4Addr);

    //Set default gateway
    ipv4StringToAddr(appSettings.NetworkSetting.Gateway, &ipv4Addr);
    ipv4SetDefaultGateway(interface, ipv4Addr);

    //Set primary and secondary DNS servers
    ipv4StringToAddr(appSettings.NetworkSetting.PrimaryDNS, &ipv4Addr);
    ipv4SetDnsServer(interface, 0, ipv4Addr);
    ipv4StringToAddr(appSettings.NetworkSetting.SecondaryDNS, &ipv4Addr);
    ipv4SetDnsServer(interface, 1, ipv4Addr);
    }
#endif

#if (IPV6_SUPPORT == ENABLED)
    //Set link-local address
    ipv6StringToAddr("fe80::00ab:cdef:0795", &ipv6Addr);
    ipv6SetLinkLocalAddr(interface, &ipv6Addr);
#endif

    error = udpDiscoveryStart();
    if (error) {
        TRACE_ERROR("Failed to init Discovery Service!\r\n");
    }
#if (HTTP_SERVER_SUPPORT == ENABLED)
    //Get default settings
    httpServerGetDefaultSettings(&httpServerSettings);
    //Bind HTTP server to the desired interface
    httpServerSettings.interface = &netInterface[0];
    //Listen to port 80
    httpServerSettings.port = appSettings.NetworkSetting.PortWebServer;
    //Specify the server's root directory
    strcpy(httpServerSettings.rootDirectory, "/www/");
    //Client Connections
    httpServerSettings.maxConnections = APP_HTTP_MAX_CONNECTIONS;
    httpServerSettings.connections = httpConnections;
    //Set default home page
#if(HTTP_SERVER_FS_SUPPORT == ENABLED)
    strcpy(httpServerSettings.defaultDocument, "index.stm");
#else
    strcpy(httpServerSettings.defaultDocument, "/index.shtml");
#endif
    //Callback functions
    httpServerSettings.cgiCallback = httpServerCgiCallback;
    httpServerSettings.uriNotFoundCallback = httpServerUriNotFoundCallback;
    httpServerSettings.authCallback = httpServerAuthCallback;
    //HTTP server initialization
    error = httpServerInit(&httpServerContext, &httpServerSettings);
    //Failed to initialize HTTP server?
    if (error) {
        //Debug message
        TRACE_ERROR("Failed to initialize HTTP server!\r\n");
    }

    //Start HTTP server
    error = httpServerStart(&httpServerContext);
    //Failed to start HTTP server?
    if (error) {
        //Debug message
        TRACE_ERROR("Failed to start HTTP server!\r\n");
    }

#endif

    //Create user task
    task = osCreateTask("blink Task", blinkTask, NULL, 400, 2);
    //Failed to create the task?
   if (task == OS_INVALID_HANDLE) {
        //Debug message
        TRACE_ERROR("Failed to create blink task!\r\n");
    }

//     //Create user task
//    task = osCreateTask("pulse Task", pulseTask, NULL, 400, 2);
//    //Failed to create the task?
//    if (task == OS_INVALID_HANDLE) {
//        //Debug message
//        TRACE_ERROR("Failed to create pulse task!\r\n");
//    }

    //Create user task
    task = osCreateTask("update Task", updateTask, NULL, 500, 2);
    //Failed to create the task?
   if (task == OS_INVALID_HANDLE) {
        //Debug message
        TRACE_ERROR("Failed to create task!\r\n");
    }

    /* Create then start some timers.  Starting the timers before the RTOS scheduler
     has been started means the timers will start running immediately that
     the RTOS scheduler starts. */
     int x;
     for( x = 0; x < NUM_TIMERS; x++ )
     {
         xTimers[ x ] = xTimerCreate
		          (  /* Just a text name, not used by the RTOS kernel. */
                     "Timer",
                     /* The timer period in ticks. */
                     ( 100 * x ),
                     /* The timers will auto-reload themselves when they expire. */
                     pdFALSE,
                     /* Assign each timer a unique id equal to its array index. */
                     ( void * ) x,
                     /* Each timer calls the same callback when it expires. */
                     vTimerCallback
                   );

         if( xTimers[ x ] == NULL )
         {
             /* The timer was not created. */
         }
         else
         {
            
         }
     }

    //Start the execution of tasks
    osStartKernel();

    //This function should never return
    return 0;
}

/* Define a callback function that will be used by multiple timer instances.
 The callback function does nothing but count the number of times the
 associated timer expires, and stop the timer once the timer has expired
 10 times. */
 void vTimerCallback( TimerHandle_t pxTimer )
 {
     long lArrayIndex;

     /* Optionally do something if the pxTimer parameter is NULL. */
     configASSERT( pxTimer );

     /* Which timer expired? */
     lArrayIndex = ( long ) pvTimerGetTimerID( pxTimer );
     setRelayValue(lArrayIndex,FALSE);
     appSettings.IoSettings.relays[lArrayIndex-1].PulseActive = FALSE;
 }

void ioInit(void) {

    initAnalog();

    //Configure RD0, RD1 and RD2 as outputs
    TRISECLR = LED1_MASK | LED2_MASK | LED3_MASK;
    LATECLR = LED1_MASK | LED2_MASK | LED3_MASK;

    TRISDCLR = RY1_MASK | RY2_MASK | RY3_MASK | RY4_MASK;
    LATDCLR = RY1_MASK | RY3_MASK ;
    LATDCLR = RY2_MASK | RY4_MASK;

    //Configure RD6, RD7 and RD13 as inputs
    TRISESET = SW1_MASK | SW2_MASK | SW3_MASK | SW4_MASK | FACTORY_DEFAULT_MASK;
    //Enable pull-ups on CN15 (RD6), CN16 (RD7) and CN19 (RD13)
   // CNPUESET = _CNPUE_CNPUE15_MASK | _CNPUE_CNPUE16_MASK | _CNPUE_CNPUE19_MASK;

    TRISDCLR = 0x3D;

    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 0;
    LATDbits.LATD4 = 0;
    LATDbits.LATD5 = 0;
}




void blinkTask(void *parameters){
    while(TRUE)
    {
        LATESET = LED1_MASK;
        osDelayTask(100);
        LATECLR = LED1_MASK;
        osDelayTask(900);
        LATESET = LED2_MASK;
        osDelayTask(100);
        LATECLR = LED2_MASK;
        osDelayTask(900);
        LATESET = LED3_MASK;
        osDelayTask(100);
        LATECLR = LED3_MASK;
        osDelayTask(900);
        
    }
}

void updateTask(void *parameters) {
     error_t error;
    int isMailSent=0;
    bool_t previousState[4];
    int i=0;
    //load first states
    for(i=0; i<4;i++)
    {
        previousState[i] = getInputStatus(i);
    }

    while (netGetDefaultInterface()->ipv4Config.addr == 0) {
        osDelayTask(100);
    }
    

    if(appSettings.Notifications[NOTIFICATION_BOOT].enable)
    {
        TRACE_INFO("BOOT ALARM BEING SENT\r\n");
        error = sendBootMail();
        if(error)
        {
            TRACE_INFO("FAILED TO SEND BOOT ALARM\r\n");
        }
        else
            TRACE_INFO("SUCCESSFULLY SENT THE BOOT ALARM \r\n");
    }
    while(1)
    {
       
        getAnalogValue();
       //Check if current analog value is greater than maxvalue;
        if(appSettings.IoSettings.analog.Value > appSettings.IoSettings.analog.MaxValue)
            appSettings.IoSettings.analog.MaxValue = appSettings.IoSettings.analog.Value;
        //Check if current analog value is greater than minvalue;
        if(appSettings.IoSettings.analog.Value < appSettings.IoSettings.analog.MinValue)
            appSettings.IoSettings.analog.MinValue = appSettings.IoSettings.analog.Value;

        //Check if current value is greater than the alarmvalue;
        if((appSettings.IoSettings.analog.Value >= appSettings.IoSettings.analog.AlarmValue) && (isMailSent == 0))
        {
            TRACE_INFO("ALARM DETECTED\r\n");
            sendAlarmMail();
            TRACE_INFO("ALARM MAIL SENT\r\n");
            isMailSent = 1;
            Nop();
        }
        if(appSettings.IoSettings.analog.Value <appSettings.IoSettings.analog.AlarmValue)
        {
            isMailSent =0;
        }

        for(i = 0; i< 4;i++)
        {

            if(checkFalling(previousState[i],getInputStatus(i)))
            {
                previousState[i] = getInputStatus(i);
                sendMail(i,FALLING);
            }else if(checkRising(previousState[i],getInputStatus(i)))
            {
                previousState[i] = getInputStatus(i);
                sendMail(i,RISING);
            }
            else
            {
                previousState[i] = getInputStatus(i);
            }
        }
        UpdateNetworkSettings();
        osDelayTask(200);
    }
}

bool_t checkFalling(bool_t previous,bool_t current)
{
    if(previous == TRUE && current == FALSE)
    {
        return TRUE;
    }
    else
        return FALSE;
}

bool_t checkRising(bool_t previous,bool_t current)
{
    if(previous == FALSE && current == TRUE)
    {
        return TRUE;
    }
    else
        return FALSE;
}

error_t getCurrentTime(void)
{
   error_t error;
   time_t unixTime;
   IpAddr ipAddr;
   NtpTimestamp timestamp;


   //Debug message
   //TRACE_INFO("\r\n\r\nResolving server name...\r\n");
   //Resolve SNTP server name
   error = getHostByName(NULL, "0.be.pool.ntp.org", &ipAddr, 0);

   //Any error to report?
   if(error)
   {
      //Debug message
      //TRACE_INFO("Failed to resolve server name!\r\n");
      //Exit immediately
      return error;
   }

   //Debug message
   //TRACE_INFO("Requesting time from SNTP server %s\r\n", ipAddrToString(&ipAddr, NULL));
   //Retrieve current time from NTP server using SNTP protocol
   error = sntpClientGetTimestamp(NULL, &ipAddr, &timestamp);

   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_INFO("Failed to retrieve NTP timestamp!\r\n");
   }
   else
   {
      //Unix time starts on January 1st, 1970
      unixTime = timestamp.seconds - 2208988800;
      //Convert Unix timestamp to date
      convertUnixTimeToDate(unixTime, &appSettings.date);

      //Debug message
      //TRACE_INFO("Current date/time: %s UTC\r\n", formatDate(&appSettings.date, NULL));

   }

   //Return status code
   return error;
}


#if (HTTP_SERVER_SUPPORT == ENABLED)

/**
 * @brief HTTP authentication callback
 * @param[in] connection Handle referencing a client connection
 * @param[in] user NULL-terminated string specifying the user name
 * @param[in] uri NULL-terminated string containing the path to the requested resource
 * @return Access status (HTTP_ACCESS_ALLOWED, HTTP_ACCESS_DENIED,
 *   HTTP_BASIC_AUTH_REQUIRED or HTTP_DIGEST_AUTH_REQUIRED)
 **/

HttpAccessStatus httpServerAuthCallback(HttpConnection *connection,
   const char_t *user, const char_t *uri)
{
   HttpAccessStatus status;

   if(!pathMatch(uri, "/api/*"))
   {
      //Only the administrator can access this directory
      if(!strcmp(user, appSettings.AuthSettings.Login))
      {
         //Check the administrator password
         if(httpCheckPassword(connection, appSettings.AuthSettings.Password, HTTP_AUTH_MODE_BASIC))
            status = HTTP_ACCESS_ALLOWED;
         else
            status = HTTP_ACCESS_BASIC_AUTH_REQUIRED;
      }
      else
      {
         //Users other than administrator cannot access this directory
         status = HTTP_ACCESS_BASIC_AUTH_REQUIRED;
      }
   }
   else
   {
      //No restriction for other directories
      status = HTTP_ACCESS_ALLOWED;
   }

   //Return access status
   return status;
}

/**
 * @brief CGI callback function
 **/
static const char* String_true = "true";
static const char* String_false = "false";
static const char* r1 = "r1";
static const char* r2 = "r2";
static const char* r3 = "r3";
static const char* r4 = "r4";
static const char* p1 = "p1";
static const char* p2 = "p2";
static const char* p3 = "p3";
static const char* p4 = "p4";
static const char* i1 = "i1";
static const char* i2 = "i2";
static const char* i3 = "i3";
static const char* i4 = "i4";
static const char* an = "an";
static const char* js = "js";
static const char* css = "css";
static const char* cardname = "cardname";
static const char* login = "LOGIN";
static const char* password = "PASSWORD";
static const char* api_key = "API_KEY";
static const char* nameR1 = "NAME_R1";
static const char* nameR2 = "NAME_R2";
static const char* nameR3 = "NAME_R3";
static const char* nameR4 = "NAME_R4";
static const char* timeR1 = "TIME_R1";
static const char* timeR2 = "TIME_R2";
static const char* timeR3 = "TIME_R3";
static const char* timeR4 = "TIME_R4";
static const char* nameI1 = "NAME_I1";
static const char* nameI2 = "NAME_I2";
static const char* nameI3 = "NAME_I3";
static const char* nameI4 = "NAME_I4";
static const char* nameAn = "NAME_AN";
static const char* nameAnAlarm = "AN_ALARM_VAL";
static const char* dhcp = "DHCP_ON";
static const char* webport = "WEB_PORT";
static const char* localip = "LOCAL_IP";
static const char* gateway = "GATEWAY";
static const char* subnetmask = "SUBNETMASK";
static const char* primarydns = "PRIMARY_DNS";
static const char* secondarydns = "SECONDARY_DNS";
static const char* smtpserver = "SMTP_SERVER";
static const char* smtpport = "SMTP_PORT";
static const char* usetls = "SMTP_TLS";
static const char* smtpuser = "SMTP_USER";
static const char* smtppass = "SMTP_PASS";
static const char* notif1on = "NOTIF_1_ON";
static const char* notif2on = "NOTIF_2_ON";
static const char* notif3on = "NOTIF_3_ON";
static const char* notif4on = "NOTIF_4_ON";
static const char* notif5on = "NOTIF_5_ON";
static const char* notif6on = "NOTIF_6_ON";
static const char* notif7on = "NOTIF_7_ON";
static const char* notif8on = "NOTIF_8_ON";
static const char* notif9on = "NOTIF_9_ON";
static const char* notif10on = "NOTIF_10_ON";
static const char* notif1addr = "NOTIF_1_ADDR";
static const char* notif2addr = "NOTIF_2_ADDR";
static const char* notif3addr = "NOTIF_3_ADDR";
static const char* notif4addr = "NOTIF_4_ADDR";
static const char* notif5addr = "NOTIF_5_ADDR";
static const char* notif6addr = "NOTIF_6_ADDR";
static const char* notif7addr = "NOTIF_7_ADDR";
static const char* notif8addr = "NOTIF_8_ADDR";
static const char* notif9addr = "NOTIF_9_ADDR";
static const char* notif10addr = "NOTIF_10_ADDR";
error_t httpServerCgiCallback(HttpConnection *connection, const char_t *param) {
    static uint_t pageCounter = 0;
    uint_t length;

    //Underlying network interface
    NetInterface *interface = connection->socket->interface;

    //Check parameter name
    if (!strcasecmp(param, "PAGE_COUNTER")) {
        pageCounter++;
        sprintf(connection->buffer, "%u time%s", pageCounter, (pageCounter >= 2) ? "s" : "");
    } else if (!strcasecmp(param, "BOARD_NAME")) {
       strcpy(connection->buffer, appSettings.CardName);
    } else if (!strcasecmp(param, api_key)) {
       strcpy(connection->buffer, appSettings.key);
    } else if (!strcasecmp(param, "SYSTEM_TIME")) {
        systime_t time = osGetSystemTime();
        formatSystemTime(time, connection->buffer);
    } else if (!strcasecmp(param, "MAC_ADDR")) {
        macAddrToString(&interface->macAddr, connection->buffer);
    } else if (!strcasecmp(param, "AN_MAX")){
        itoa(connection->buffer,appSettings.IoSettings.analog.MaxValue,10);
    } else if (!strcasecmp(param, "AN_MIN")){
        itoa(connection->buffer,appSettings.IoSettings.analog.MinValue,10);
    } else if (!strcasecmp(param, "FIRMWARE_VERSION")){
        strcpy(connection->buffer,FIRMWARE_VERSION);
    }else if (!strcasecmp(param, "CUSTOM_JS")){
        strcpy(connection->buffer,appSettings.CustomJSLink);
    }else if (!strcasecmp(param, "CUSTOM_CSS")){
        strcpy(connection->buffer,appSettings.CustomCSSLink);
    }else if (!strcasecmp(param, r1)){
        strcpy(connection->buffer,bool2str(READRY1));
    }else if (!strcasecmp(param, r2)){
        strcpy(connection->buffer,bool2str(READRY2));
    }else if (!strcasecmp(param, r3)){
        strcpy(connection->buffer,bool2str(READRY3));
    }else if (!strcasecmp(param, r4)){
        strcpy(connection->buffer,bool2str(READRY4));
    }else if (!strcasecmp(param, i1)){
        strcpy(connection->buffer,bool2str(getInputStatus(0)));
    }else if (!strcasecmp(param, i2)){
        strcpy(connection->buffer,bool2str(getInputStatus(1)));
    }else if (!strcasecmp(param, i3)){
        strcpy(connection->buffer,bool2str(getInputStatus(2)));
    }else if (!strcasecmp(param, i4)){
        strcpy(connection->buffer,bool2str(getInputStatus(3)));
    }else if (!strcasecmp(param, an)){
        ltoa(connection->buffer,appSettings.IoSettings.analog.Value,10);
    }else if (!strcasecmp(param,login)){
        strcpy(connection->buffer,appSettings.AuthSettings.Login);
    }else if (!strcasecmp(param,password)){
        strcpy(connection->buffer,appSettings.AuthSettings.Password);
    }else if (!strcasecmp(param,nameR1)){
        strcpy(connection->buffer,appSettings.IoSettings.relays[0].Name);
    }else if (!strcasecmp(param,nameR2)){
        strcpy(connection->buffer,appSettings.IoSettings.relays[1].Name);
    }else if (!strcasecmp(param,nameR3)){
        strcpy(connection->buffer,appSettings.IoSettings.relays[2].Name);
    }else if (!strcasecmp(param,nameR4)){
        strcpy(connection->buffer,appSettings.IoSettings.relays[3].Name);
    }else if (!strcasecmp(param,timeR1)){
        ltoa(connection->buffer,appSettings.IoSettings.relays[0].PulseTime,10);
    }else if (!strcasecmp(param,timeR2)){
        ltoa(connection->buffer,appSettings.IoSettings.relays[1].PulseTime,10);
    }else if (!strcasecmp(param,timeR3)){
        ltoa(connection->buffer,appSettings.IoSettings.relays[2].PulseTime,10);
    }else if (!strcasecmp(param,timeR4)){
        ltoa(connection->buffer,appSettings.IoSettings.relays[3].PulseTime,10);
    }else if (!strcasecmp(param,nameI1)){
        strcpy(connection->buffer,appSettings.IoSettings.inputs[0].Name);
    }else if (!strcasecmp(param,nameI2)){
        strcpy(connection->buffer,appSettings.IoSettings.inputs[1].Name);
    }else if (!strcasecmp(param,nameI3)){
        strcpy(connection->buffer,appSettings.IoSettings.inputs[2].Name);
    }else if (!strcasecmp(param,nameI4)){
        strcpy(connection->buffer,appSettings.IoSettings.inputs[3].Name);
    }else if (!strcasecmp(param,nameAn)){
        strcpy(connection->buffer,appSettings.IoSettings.analog.Name);
    }else if (!strcasecmp(param,nameAnAlarm)){
        ltoa(connection->buffer,appSettings.IoSettings.analog.AlarmValue,10);
    }else if (!strcasecmp(param,dhcp)){
        strcpy(connection->buffer,bool2str(appSettings.NetworkSetting.DhcpEnabled));
    }else if (!strcasecmp(param,webport)){
        ltoa(connection->buffer,appSettings.NetworkSetting.PortWebServer,10);
    }else if (!strcasecmp(param,localip)){
        strcpy(connection->buffer,appSettings.NetworkSetting.address);
    }else if (!strcasecmp(param,gateway)){
        strcpy(connection->buffer,appSettings.NetworkSetting.Gateway);
    }else if (!strcasecmp(param,subnetmask)){
        strcpy(connection->buffer,appSettings.NetworkSetting.SubnetMask);
    }else if (!strcasecmp(param,primarydns)){
        strcpy(connection->buffer,appSettings.NetworkSetting.PrimaryDNS);
    }else if (!strcasecmp(param,secondarydns)){
        strcpy(connection->buffer,appSettings.NetworkSetting.SecondaryDNS);
    }else if (!strcasecmp(param,smtpserver)){
        strcpy(connection->buffer,appSettings.EmailSettings.serverName);
    }else if (!strcasecmp(param,smtpport)){
        ltoa(connection->buffer,appSettings.EmailSettings.serverPort,10);
    }else if (!strcasecmp(param,usetls)){
       strcpy(connection->buffer,bool2str(appSettings.EmailSettings.useTls));
    }else if (!strcasecmp(param,smtpuser)){
        strcpy(connection->buffer,appSettings.EmailSettings.userName);
    }else if (!strcasecmp(param,smtppass)){
        strcpy(connection->buffer,appSettings.EmailSettings.passWord);
    }else if (!strcasecmp(param,notif1on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_INPUT1_RISING].enable));
    }else if (!strcasecmp(param,notif2on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_INPUT2_RISING].enable));
    }else if (!strcasecmp(param,notif3on)){
       strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_INPUT3_RISING].enable));
    }else if (!strcasecmp(param,notif4on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_INPUT4_RISING].enable));
    }else if (!strcasecmp(param,notif5on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_INPUT1_FALLING].enable));
    }else if (!strcasecmp(param,notif6on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_INPUT2_FALLING].enable));
    }else if (!strcasecmp(param,notif7on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_INPUT3_FALLING].enable));
    }else if (!strcasecmp(param,notif8on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_INPUT4_FALLING].enable));
    }else if (!strcasecmp(param,notif9on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_BOOT].enable));
    }else if (!strcasecmp(param,notif10on)){
        strcpy(connection->buffer,bool2str(appSettings.Notifications[NOTIFICATION_ANALOG].enable));
    }else if (!strcasecmp(param,notif1addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_INPUT1_RISING].mail.recipients);
    }else if (!strcasecmp(param,notif2addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_INPUT2_RISING].mail.recipients);
    }else if (!strcasecmp(param,notif3addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_INPUT3_RISING].mail.recipients);
    }else if (!strcasecmp(param,notif4addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_INPUT4_RISING].mail.recipients);
    }else if (!strcasecmp(param,notif5addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_INPUT1_FALLING].mail.recipients);
    }else if (!strcasecmp(param,notif6addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_INPUT2_FALLING].mail.recipients);
    }else if (!strcasecmp(param,notif7addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_INPUT3_FALLING].mail.recipients);
    }else if (!strcasecmp(param,notif8addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_INPUT4_FALLING].mail.recipients);
    }else if (!strcasecmp(param,notif9addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_BOOT].mail.recipients);
    }else if (!strcasecmp(param,notif10addr)){
        strcpy(connection->buffer,appSettings.Notifications[NOTIFICATION_ANALOG].mail.recipients);
    }else {
        return ERROR_INVALID_TAG;
    }
    //Get the length of the resulting string
    length = strlen(connection->buffer);
    
    //Send the contents of the specified environment variable
    return httpWriteStream(connection, connection->buffer, length);
}

/**
 * @brief URI not found callback
 **/

error_t httpServerUriNotFoundCallback(HttpConnection *connection, const char_t *uri) {
    if(strstr(connection->request.uri,"/api"))
    {
        char firstParameter[32];
        char secondParameter[32];
        char relays[32];
        char * tokenPointer;
        bool_t authorized;
        char requestUri[HTTP_SERVER_URI_MAX_LEN];
        strcpy(requestUri,connection->request.uri);
        strtok(requestUri,"/");
        tokenPointer = strtok(NULL,"/");
        if(tokenPointer)        
            strcpy(firstParameter,tokenPointer);
        tokenPointer = strtok(NULL,"/");
        if(tokenPointer)
            strcpy(secondParameter,tokenPointer);
        authorized = FALSE;
        if(!strcmp(firstParameter,"relay"))
        {
            if(!strcmp(secondParameter,"on"))
            {
                authorized = parseRelayAPICommand(connection->request.queryString,relays);
                if(authorized)
                {
                    char* relay;
                           relay = strtok(relays,",");
                           while(relay != NULL)
                           {
                               setRelayValue(atoi(relay),1);
                               relay = strtok(NULL,",");
                           }
                    sendIoStatus(connection);
                }
                else
                {
                    return ERROR_INVALID_REQUEST;
                }
            }
            if(!strcmp(secondParameter,"off"))
            {
                authorized = parseRelayAPICommand(connection->request.queryString,relays);
                if(authorized)
                {
                    char* relay;
                           relay = strtok(relays,",");
                           while(relay != NULL)
                           {
                               setRelayValue(atoi(relay),0);
                               relay = strtok(NULL,",");
                           }
                    sendIoStatus(connection);
                }
                else
                {
                    return ERROR_INVALID_REQUEST;
                }
            }
            if(!strcmp(secondParameter,"toggle"))
            {
                authorized = parseRelayAPICommand(connection->request.queryString,relays);
                if(authorized)
                {
                    char* relay;
                           relay = strtok(relays,",");
                           while(relay != NULL)
                           {
                               setRelayValue(atoi(relay),!getRelayValue(atoi(relay)));
                               relay = strtok(NULL,",");
                           }
                    sendIoStatus(connection);
                }
                else
                {
                    return ERROR_INVALID_REQUEST;
                }
            }
            if(!strcmp(secondParameter,"pulse"))
            {
                int time;
                authorized = parsePulseAPICommand(connection->request.queryString,relays,&time);
                if(authorized)
                {
                    char* relay;
                           relay = strtok(relays,",");
                           while(relay != NULL)
                           {
                               if(time == -1)
                               {
                                    startPulse(atoi(relay),appSettings.IoSettings.relays[atoi(relay)].PulseTime);
                               }
                               else
                               {
                                   startPulse(atoi(relay),time);
                               }
                               relay = strtok(NULL,",");
                           }
                    sendIoStatus(connection);
                }
                else
                {
                    return ERROR_INVALID_REQUEST;
                }
            }
        }else if(!strcasecmp(firstParameter,"status"))
        {
            if(isAPIAuthorized(connection->request.queryString))
            {
                return sendIoStatus(connection);
            }
            else
            {
                return ERROR_INVALID_REQUEST;
            }
        }else if(!strcasecmp(firstParameter,"settings"))
        {
            if(!strcmp(secondParameter,"names"))
            {
                if(isAPIAuthorized(connection->request.queryString))
                {
                    return sendNames(connection);
                }
                else
                {
                    return ERROR_INVALID_REQUEST;
                }
            }
            else
            {
                return ERROR_INVALID_REQUEST;
            }

        }else if(!strcasecmp(firstParameter,"auth"))
        {
            if(authUser(connection->request.queryString))
            {
                return sendAPIKey(connection);
            }
            else
            {
                return ERROR_INVALID_REQUEST;
            }
        }
        else
        {
            return ERROR_INVALID_REQUEST;
        }
    } else if (!strcasecmp(connection->request.uri, "/email_settings")) {
      return processEmailSettings(connection);
    } else if (!strcasecmp(connection->request.uri, "/alarm_settings")) {
        return processAlarmSettings(connection);
    } else if (strstr(connection->request.uri,"relay")) {
        char * part;
        int relay;
        char str[128];
        strcpy(str,connection->request.uri);
        part = strtok(str,"/"); //relay
        relay = atoi(strtok(NULL,"/"));
        char * command = strtok(NULL,"/");
        if(!strcasecmp(command,"on"))
        {
            setRelayValue(relay,1);
        }
        else if(!strcasecmp(command,"pulse"))
        {
            char* param = strtok(NULL,"/");
            if(param)//if custom time
            {
                uint_t time = atoi(param);
                if(time)//If time is not zero
                {
                    startPulse(relay,time);
                }
                else
                {
                    startPulse(relay,appSettings.IoSettings.relays[relay-1].PulseTime);
                }
            }
            else
            {
                startPulse(relay,appSettings.IoSettings.relays[relay-1].PulseTime);
            }
            
        }
        else if(!strcasecmp(command,"off"))// off
        {
            setRelayValue(relay,0);
        }
        return sendIoStatus(connection);
    }else if (!strcasecmp(connection->request.uri, "/status")) {
       return sendIoStatus(connection);
    }else if (!strcasecmp(connection->request.uri, "/network_settings")) {
        return processNetworkSettings(connection);
    } else if (!strcasecmp(connection->request.uri, "/auth_settings")) {
        return processAuthenticationSettings(connection);
    } else if (!strcasecmp(connection->request.uri, "/names")) {
        return processNames(connection);
    }else if (!strcasecmp(connection->request.uri, "/io_status")) {
        return sendIoStatus(connection);
    }else if(!strcasecmp(connection->request.uri,"/regenerate_api")){
        systime_t time = osGetSystemTime();
        srand(time);
        gen_random(appSettings.key,32);
        vTaskSuspendAll();
        WriteSettingsToFlash();
        xTaskResumeAll();
        return sendAPIKey(connection);
    }else if(!strcasecmp(connection->request.uri, "/debug")){
        return sendDebug(connection);
    }else if(!strcasecmp(connection->request.uri, "/bootloader")){
        GoToBootLoader();
        return sendIoStatus(connection);
    }else if(!strcasecmp(connection->request.uri, "/testmail")){
        return sendTestMail(connection);
    } else
        return ERROR_NOT_FOUND;
}

error_t sendDebug(HttpConnection* connection)
{
        char_t* buffer;
        int n;

        //Point to the scratch buffer
        buffer = connection->buffer + 384;
        char test[512] = {0};
        vTaskList(test);
        n= strlen(test);
        strcpy(buffer,test);

        //Format HTTP response header
        connection->response.version = connection->request.version;
        connection->response.statusCode = 200;
        connection->response.keepAlive = connection->response.keepAlive;
        connection->response.noCache = TRUE;
        connection->response.contentType = mimeGetType(".txt");
        connection->response.chunkedEncoding = FALSE;
        connection->response.contentLength = n;

        //Send the header to the client
        error = httpWriteHeader(connection);
        //Any error to report?
        if(error) return error;

        //Send response body
        error = httpWriteStream(connection, buffer, n);
        //Any error to report?
        if(error) return error;

        //Properly close output stream
        error = httpCloseStream(connection);
        //Return status code
        
        return error;
}

const char* bool2str(bool_t value)
{
    return value ? String_true : String_false;
}

void createJsonData(char * data)
{

    char analogValue[10];
    itoa(analogValue,appSettings.IoSettings.analog.Value,10);
    sprintf(data,"{\"relays\": [%s,%s,%s,%s],"
            "\"pulse\": [%s,%s,%s,%s],"
            "\"inputs\": [%s,%s,%s,%s],"
            "\"analog\": %s}",
            bool2str(READRY1),
            bool2str(READRY2),
            bool2str(READRY3),
            bool2str(READRY4),
            bool2str(appSettings.IoSettings.relays[0].PulseActive),
            bool2str(appSettings.IoSettings.relays[1].PulseActive),
            bool2str(appSettings.IoSettings.relays[2].PulseActive),
            bool2str(appSettings.IoSettings.relays[3].PulseActive),
            bool2str(READIN1),
            bool2str(READIN2),
            bool2str(READIN3),
            bool2str(READIN4),
            analogValue);

}

void createNamesJson(char * data)
{

    char analogValue[10];
    itoa(analogValue,appSettings.IoSettings.analog.Value,10);
    sprintf(data,"{\"relays\": [%s,%s,%s,%s],"
            "\"inputs\": [%s,%s,%s,%s],"
            "\"analog\": %s}",
            appSettings.IoSettings.relays[0].Name,
            appSettings.IoSettings.relays[1].Name,
            appSettings.IoSettings.relays[2].Name,
            appSettings.IoSettings.relays[3].Name,
            appSettings.IoSettings.inputs[0].Name,
            appSettings.IoSettings.inputs[1].Name,
            appSettings.IoSettings.inputs[2].Name,
            appSettings.IoSettings.inputs[3].Name,
            appSettings.IoSettings.analog.Name);

}

error_t sendIoStatus(HttpConnection *connection)
{
        char_t *buffer;
        char_t *data;
        int n;
    
        buffer = connection->buffer + 384;

        createJsonData(buffer);
        if(buffer != NULL)
        {
         
         n= strlen(buffer);
        
        }
        else
        {
            n= 0;
        }
        //Format HTTP response header
        connection->response.version = connection->request.version;
        connection->response.statusCode = 200;
        connection->response.keepAlive = FALSE;
        connection->response.noCache = TRUE;
        connection->response.contentType = mimeGetType(".json");
        connection->response.chunkedEncoding = FALSE;
        connection->response.contentLength = n;

        //Send the header to the client
        error = httpWriteHeader(connection);
        //Any error to report?
        if(error) return error;

        //Send response body
        error = httpWriteStream(connection, buffer, n);
        //Any error to report?
        if(error) return error;

        //Properly close output stream
        error = httpCloseStream(connection);
        
        //Return status code
        return error;
}

error_t sendNames(HttpConnection *connection)
{
        char_t *buffer;
        char_t *data;
        int n;

        buffer = connection->buffer + 384;

        createNamesJson(buffer);
        if(buffer != NULL)
        {

         n= strlen(buffer);

        }
        else
        {
            n= 0;
        }
        //Format HTTP response header
        connection->response.version = connection->request.version;
        connection->response.statusCode = 200;
        connection->response.keepAlive = FALSE;
        connection->response.noCache = TRUE;
        connection->response.contentType = mimeGetType(".json");
        connection->response.chunkedEncoding = FALSE;
        connection->response.contentLength = n;

        //Send the header to the client
        error = httpWriteHeader(connection);
        //Any error to report?
        if(error) return error;

        //Send response body
        error = httpWriteStream(connection, buffer, n);
        //Any error to report?
        if(error) return error;

        //Properly close output stream
        error = httpCloseStream(connection);

        //Return status code
        return error;
}

error_t processAlarmSettings(HttpConnection *connection)
{
    Notification notif;
    int alarm;
    char *separator;
        char *property;
        char *value;
        char *p;
        
        char_t *buffer;
        int i,j,n;
        
      

        //Point to the scratch buffer
        buffer = connection->buffer + 384;

        alarm = NOTIFICATIONS_SIZE;
        //Start of exception handling block
        do {
            //Process HTTP request body
            while (1) {
                //Read the HTTP request body until a ampersand is encountered
                error = httpReadStream(connection, buffer,
                        HTTP_SERVER_BUFFER_SIZE - 1, &n, HTTP_FLAG_BREAK('&'));
                //End of stream detected?
                if (error) break;

                //Properly terminate the string with a NULL character
                buffer[n] = '\0';

                //Remove the trailing ampersand
                if (n > 0 && buffer[n - 1] == '&')
                    buffer[--n] = '\0';

                //Decode the percent-encoded string
                for (i = 0, j = 0; i < n; i++, j++) {
                    //Replace '+' characters with spaces
                    if (buffer[i] == '+') {
                        buffer[j] = ' ';
                    }//Process percent-encoded characters
                    else if (buffer[i] == '%' && (i + 2) < n) {
                        buffer[i] = buffer[i + 1];
                        buffer[i + 1] = buffer[i + 2];
                        buffer[i + 2] = '\0';
                        buffer[j] = strtoul(buffer + i, NULL, 16);
                        i += 2;
                    }//Copy any other characters
                    else {
                        buffer[j] = buffer[i];
                    }
                }

                //Properly terminate the resulting string
                buffer[j] = '\0';

                //Check whether a separator is present
                separator = strchr(buffer, '=');

                //Separator found?
                if (separator) {
                    //Split the line
                    *separator = '\0';
                    //Get property name and value
                    property = strTrimWhitespace(buffer);
                    value = strTrimWhitespace(separator + 1);

                    //fill settings
                    if (!strcasecmp(property, "alarm")) {
                        alarm = atoi(value);
                        if(!(alarm <= NOTIFICATIONS_SIZE))
                            break;

                    }
                    else if (!strcasecmp(property, "enable")) {
                        appSettings.Notifications[alarm].enable = atoi(value);
                    }else if (!strcasecmp(property, "recipient")) {
                        strcpy(appSettings.Notifications[alarm].mail.recipients,value);
                    } else if (!strcasecmp(property, "alarmvalue")) {
                        appSettings.IoSettings.analog.AlarmValue = atoi(value);
                    }
            }
          }
        }while(0);

        if (error != ERROR_END_OF_STREAM)
        {
            strcpy(buffer,"NOK");
        }
        else
        {
            vTaskSuspendAll();
            WriteSettingsToFlash();
            xTaskResumeAll();
           strcpy(buffer,"OK");
        }

        n = strlen(buffer);

      //Format HTTP response header
      connection->response.version = connection->request.version;
      connection->response.statusCode = 200;
      connection->response.keepAlive = connection->request.keepAlive;
      connection->response.noCache = TRUE;
      connection->response.contentType = mimeGetType(".json");
      connection->response.chunkedEncoding = FALSE;
      connection->response.contentLength = n;


      //Send the header to the client
      error = httpWriteHeader(connection);
      //Any error to report?
      if(error) return error;

      //Send response body
      error = httpWriteStream(connection, buffer, n);
      //Any error to report?
      if(error) return error;
      //Properly close output stream
      error = httpCloseStream(connection);
      //Return status code

      return error;
}

error_t processEmailSettings(HttpConnection *connection)
{
    char *separator,*property,*value,*p;
        int i,j,n;
        char_t *buffer;
        //Point to the scratch buffer
        buffer = connection->buffer;

        //Start of exception handling block
        do {
            //Process HTTP request body
            while (1) {
                //Read the HTTP request body until a ampersand is encountered
                error = httpReadStream(connection, buffer,
                        HTTP_SERVER_BUFFER_SIZE - 1, &n, HTTP_FLAG_BREAK('&'));
                //End of stream detected?
                if (error) break;

                //Properly terminate the string with a NULL character
                buffer[n] = '\0';

                //Remove the trailing ampersand
                if (n > 0 && buffer[n - 1] == '&')
                    buffer[--n] = '\0';

                //Decode the percent-encoded string
                for (i = 0, j = 0; i < n; i++, j++) {
                    //Replace '+' characters with spaces
                    if (buffer[i] == '+') {
                        buffer[j] = ' ';
                    }//Process percent-encoded characters
                    else if (buffer[i] == '%' && (i + 2) < n) {
                        buffer[i] = buffer[i + 1];
                        buffer[i + 1] = buffer[i + 2];
                        buffer[i + 2] = '\0';
                        buffer[j] = strtoul(buffer + i, NULL, 16);
                        i += 2;
                    }//Copy any other characters
                    else {
                        buffer[j] = buffer[i];
                    }
                }

                //Properly terminate the resulting string
                buffer[j] = '\0';

                //Check whether a separator is present
                separator = strchr(buffer, '=');

                //Separator found?
                if (separator) {
                    //Split the line
                    *separator = '\0';
                    //Get property name and value
                    property = strTrimWhitespace(buffer);
                    value = strTrimWhitespace(separator + 1);

                    //Check property name
                    if (!strcasecmp(property, "smtpserver")) {
                        //Save server name
                        strcpy(appSettings.EmailSettings.serverName,value);
                    } else if (!strcasecmp(property, "smtpport")) {
                        //Save the server port to be used
                        appSettings.EmailSettings.serverPort = atoi(value);
                    } else if (!strcasecmp(property, "user")) {
                        //Save user name
                        strcpy(appSettings.EmailSettings.userName,value);
                    } else if (!strcasecmp(property, "password")) {
                        //Save password
                        strcpy(appSettings.EmailSettings.passWord,value);
                    } else if (!strcasecmp(property, "useTls")) {
                        //Open a secure SSL/TLS session?
                        appSettings.EmailSettings.useTls = FALSE;
                }
            }
          }
        }while(0);

        buffer  = connection->buffer + 384;

        if (error != ERROR_END_OF_STREAM)
        {
            strcpy(buffer,"NOK");
        }
        else
        {
            osSuspendAllTasks();
            WriteSettingsToFlash();
            osResumeAllTasks();
            strcpy(buffer,"OK");
        }

        n = strlen(buffer);

      //Format HTTP response header
      connection->response.version = connection->request.version;
      connection->response.statusCode = 200;
      connection->response.keepAlive = connection->request.keepAlive;
      connection->response.noCache = TRUE;
      connection->response.contentType = mimeGetType(".json");
      connection->response.chunkedEncoding = FALSE;
      connection->response.contentLength = n;


      //Send the header to the client
      error = httpWriteHeader(connection);
      //Any error to report?
      if(error) return error;

      //Send response body
      error = httpWriteStream(connection, buffer, n);
      //Any error to report?
      if(error) return error;
      //Properly close output stream
      error = httpCloseStream(connection);
      //Return status code

      return error;
}

error_t processNames(HttpConnection* connection){

    char *separator;
        char *property;
        int alarm;
        char *p;
        char* value;
        char_t *buffer;
        int i,j,n;



        //Point to the scratch buffer
        buffer = connection->buffer + 384;

        alarm = NOTIFICATIONS_SIZE;
        //Start of exception handling block
        do {
            //Process HTTP request body
            while (1) {
                //Read the HTTP request body until a ampersand is encountered
                error = httpReadStream(connection, buffer,
                        HTTP_SERVER_BUFFER_SIZE - 1, &n, HTTP_FLAG_BREAK('&'));
                //End of stream detected?
                if (error) break;

                //Properly terminate the string with a NULL character
                buffer[n] = '\0';

                //Remove the trailing ampersand
                if (n > 0 && buffer[n - 1] == '&')
                    buffer[--n] = '\0';

                //Decode the percent-encoded string
                for (i = 0, j = 0; i < n; i++, j++) {
                    //Replace '+' characters with spaces
                    if (buffer[i] == '+') {
                        buffer[j] = ' ';
                    }//Process percent-encoded characters
                    else if (buffer[i] == '%' && (i + 2) < n) {
                        buffer[i] = buffer[i + 1];
                        buffer[i + 1] = buffer[i + 2];
                        buffer[i + 2] = '\0';
                        buffer[j] = strtoul(buffer + i, NULL, 16);
                        i += 2;
                    }//Copy any other characters
                else {
                    buffer[j] = buffer[i];
                }
            }

            //Properly terminate the resulting string
            buffer[j] = '\0';

            //Check whether a separator is present
            separator = strchr(buffer, '=');

            //Separator found?
            if (separator) {
                //Split the line
                *separator = '\0';
                //Get property name and value
                property = strTrimWhitespace(buffer);
                value = strTrimWhitespace(separator + 1);
                int time;
                //fill settings
                if (!strcasecmp(property, r1)) {
                    strcpy(appSettings.IoSettings.relays[0].Name, value);
                } else if (!strcasecmp(property, r2)) {
                    strcpy(appSettings.IoSettings.relays[1].Name, value);
                } else if (!strcasecmp(property, r3)) {
                    strcpy(appSettings.IoSettings.relays[2].Name, value);
                } else if (!strcasecmp(property, r4)) {
                    strcpy(appSettings.IoSettings.relays[3].Name, value);
                } else if (!strcasecmp(property, p1)) {
                    time = atoi(value);
                    if(time)
                    {
                        appSettings.IoSettings.relays[0].PulseTime =  time;
                    }
                } else if (!strcasecmp(property, p2)) {
                    time = atoi(value);
                    if(time)
                    {
                        appSettings.IoSettings.relays[1].PulseTime =  time;
                    }
                } else if (!strcasecmp(property, p3)) {
                    time = atoi(value);
                    if(time)
                    {
                        appSettings.IoSettings.relays[2].PulseTime = time;
                    }
                } else if (!strcasecmp(property, p4)) {
                    time = atoi(value);
                    if(time)
                    {
                        appSettings.IoSettings.relays[3].PulseTime =  time;
                    }
                } else if (!strcasecmp(property, i1)) {
                    strcpy(appSettings.IoSettings.inputs[0].Name, value);
                } else if (!strcasecmp(property, i2)) {
                    strcpy(appSettings.IoSettings.inputs[1].Name, value);
                } else if (!strcasecmp(property, i3)) {
                    strcpy(appSettings.IoSettings.inputs[2].Name, value);
                } else if (!strcasecmp(property, i4)) {
                    strcpy(appSettings.IoSettings.inputs[3].Name, value);
                } else if (!strcasecmp(property, an)) {
                    strcpy(appSettings.IoSettings.analog.Name, value);
                }else if (!strcasecmp(property, js)) {
                    strcpy(appSettings.CustomJSLink, value);
                }else if (!strcasecmp(property, cardname)) {
                    strcpy(appSettings.CardName, value);
                    netSetHostname(interface,appSettings.CardName);
                }else if (!strcasecmp(property, css)) {
                    strcpy(appSettings.CustomCSSLink, value);
                }
            }
        }
    } while (0);

    if (error != ERROR_END_OF_STREAM) {
        strcpy(buffer,"NOK");
    } else {
        osSuspendAllTasks();
        WriteSettingsToFlash();
        osResumeAllTasks();
        strcpy(buffer,"OK");
    }

    n = strlen(buffer);

    //Format HTTP response header
    connection->response.version = connection->request.version;
    connection->response.statusCode = 200;
    connection->response.keepAlive = connection->request.keepAlive;
    connection->response.noCache = TRUE;
    connection->response.contentType = mimeGetType(".txt");
    connection->response.chunkedEncoding = FALSE;
    connection->response.contentLength = n;


    //Send the header to the client
    error = httpWriteHeader(connection);
    //Any error to report?
    if (error) return error;

    //Send response body
    error = httpWriteStream(connection, buffer, n);
    //Any error to report?
    if (error) return error;
    //Properly close output stream
    error = httpCloseStream(connection);
    //Return status code

    return error;
}

error_t processNetworkSettings(HttpConnection* connection){

    char *separator;
        char *property;
        char *value;
        char *p;
        int alarm;
        char_t *buffer;
        int i,j,n;



        //Point to the scratch buffer
        buffer = connection->buffer + 384;

        alarm = NOTIFICATIONS_SIZE;
        //Start of exception handling block
        do {
            //Process HTTP request body
            while (1) {
                //Read the HTTP request body until a ampersand is encountered
                error = httpReadStream(connection, buffer,
                        HTTP_SERVER_BUFFER_SIZE - 1, &n, HTTP_FLAG_BREAK('&'));
                //End of stream detected?
                if (error) break;

                //Properly terminate the string with a NULL character
                buffer[n] = '\0';

                //Remove the trailing ampersand
                if (n > 0 && buffer[n - 1] == '&')
                    buffer[--n] = '\0';

                //Decode the percent-encoded string
                for (i = 0, j = 0; i < n; i++, j++) {
                    //Replace '+' characters with spaces
                    if (buffer[i] == '+') {
                        buffer[j] = ' ';
                    }//Process percent-encoded characters
                    else if (buffer[i] == '%' && (i + 2) < n) {
                        buffer[i] = buffer[i + 1];
                        buffer[i + 1] = buffer[i + 2];
                        buffer[i + 2] = '\0';
                        buffer[j] = strtoul(buffer + i, NULL, 16);
                        i += 2;
                    }//Copy any other characters
                else {
                    buffer[j] = buffer[i];
                }
            }

            //Properly terminate the resulting string
            buffer[j] = '\0';

            //Check whether a separator is present
            separator = strchr(buffer, '=');

            //Separator found?
            if (separator) {
                //Split the line
                *separator = '\0';
                //Get property name and value
                property = strTrimWhitespace(buffer);
                value = strTrimWhitespace(separator + 1);

                //fill settings
   
                if (!strcasecmp(property, "webserverport")) {
                    appSettings.NetworkSetting.PortWebServer = atoi(value);
                } else if (!strcasecmp(property, "dhcpenable")) {
                    appSettings.NetworkSetting.DhcpEnabled = atoi(value);
                } else if (!strcasecmp(property, "ipaddress")) {
                    strcpy(appSettings.NetworkSetting.address, value);
                } else if (!strcasecmp(property, "gateway")) {
                    strcpy(appSettings.NetworkSetting.Gateway, value);
                } else if (!strcasecmp(property, "subnetmask")) {
                    strcpy(appSettings.NetworkSetting.SubnetMask, value);
                } else if (!strcasecmp(property, "primarydns")) {
                    strcpy(appSettings.NetworkSetting.PrimaryDNS, value);
                } else if (!strcasecmp(property, "secondarydns")) {
                    strcpy(appSettings.NetworkSetting.SecondaryDNS, value);
                }else if (!strcasecmp(property, "cardname")) {
                    strcpy(appSettings.CardName, value);
                }

            }
        }
    } while (0);

    if (error != ERROR_END_OF_STREAM) {
        strcpy(buffer,"NOK");
    } else {
        osSuspendAllTasks();
        WriteSettingsToFlash();
        osResumeAllTasks();
        strcpy(buffer,"OK");
    }

    n = strlen(buffer);
    //Format HTTP response header
    connection->response.version = connection->request.version;
    connection->response.statusCode = 200;
    connection->response.keepAlive = connection->request.keepAlive;
    connection->response.noCache = TRUE;
    connection->response.contentType = mimeGetType(".txt");
    connection->response.chunkedEncoding = FALSE;
    connection->response.contentLength = n;


    //Send the header to the client
    error = httpWriteHeader(connection);
    //Any error to report?
    if (error) return error;

    //Send response body
    error = httpWriteStream(connection, buffer, n);
    //Any error to report?
    if (error) return error;
    //Properly close output stream
    error = httpCloseStream(connection);
    //Return status code
    reboot();
    Nop();
    Nop();
    Nop();
    Nop();
    return error;
}

error_t processAuthenticationSettings(HttpConnection* connection){
    int alarm;
    char* value;
    char *separator;
        char *property;

        char *p;

        char_t *buffer;
        int i,j,n;



        //Point to the scratch buffer
        buffer = connection->buffer + 384;

        alarm = NOTIFICATIONS_SIZE;
        //Start of exception handling block
        do {
            //Process HTTP request body
            while (1) {
                //Read the HTTP request body until a ampersand is encountered
                error = httpReadStream(connection, buffer,
                        HTTP_SERVER_BUFFER_SIZE - 1, &n, HTTP_FLAG_BREAK('&'));
                //End of stream detected?
                if (error) break;

                //Properly terminate the string with a NULL character
                buffer[n] = '\0';

                //Remove the trailing ampersand
                if (n > 0 && buffer[n - 1] == '&')
                    buffer[--n] = '\0';

                //Decode the percent-encoded string
                for (i = 0, j = 0; i < n; i++, j++) {
                    //Replace '+' characters with spaces
                    if (buffer[i] == '+') {
                        buffer[j] = ' ';
                    }//Process percent-encoded characters
                    else if (buffer[i] == '%' && (i + 2) < n) {
                        buffer[i] = buffer[i + 1];
                        buffer[i + 1] = buffer[i + 2];
                        buffer[i + 2] = '\0';
                        buffer[j] = strtoul(buffer + i, NULL, 16);
                        i += 2;
                    }//Copy any other characters
                else {
                    buffer[j] = buffer[i];
                }
            }

            //Properly terminate the resulting string
            buffer[j] = '\0';

            //Check whether a separator is present
            separator = strchr(buffer, '=');

            //Separator found?
            if (separator) {
                //Split the line
                *separator = '\0';
                //Get property name and value
                property = strTrimWhitespace(buffer);
                value = strTrimWhitespace(separator + 1);

                //fill settings
                if (!strcasecmp(property, "login")) {
                    strcpy(appSettings.AuthSettings.Login, value);
                } else if (!strcasecmp(property, "password")) {
                    strcpy(appSettings.AuthSettings.Password, value);
                }
            }
        }
    } while (0);

    if (error != ERROR_END_OF_STREAM) {
        strcpy(buffer, "NOK");
    } else {
        osSuspendAllTasks();
        WriteSettingsToFlash();
        osResumeAllTasks();
        strcpy(buffer, "OK");
    }

    n = strlen(buffer);

    //Format HTTP response header
    connection->response.version = connection->request.version;
    connection->response.statusCode = 200;
    connection->response.keepAlive = connection->request.keepAlive;
    connection->response.noCache = TRUE;
    connection->response.contentType = mimeGetType(".txt");
    connection->response.chunkedEncoding = FALSE;
    connection->response.contentLength = n;


    //Send the header to the client
    error = httpWriteHeader(connection);
    //Any error to report?
    if (error) return error;

    //Send response body
    error = httpWriteStream(connection, buffer, n);
    //Any error to report?
    if (error) return error;
    //Properly close output stream
    error = httpCloseStream(connection);
    //Return status code
    reboot();
    return error;
}
#endif