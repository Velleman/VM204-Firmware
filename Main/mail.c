/**
 * @brief SMTP client test routine
 * @return Error code
 **/

#include "shared.h"
#include "yarrow.h"
#include "alarmSetting.h"
#include "http/http_server.h"
#include "str.h"

error_t sendAlarmMail() {
    error_t error;
    if (appSettings.Notifications[NOTIFICATION_ANALOG].enable) {
        getCurrentTime();

        //Authentication information
        SmtpAuthInfo authInfo;
        authInfo.interface = NULL;
        authInfo.serverName = appSettings.EmailSettings.serverName; //SMTP server name
        authInfo.serverPort = appSettings.EmailSettings.serverPort; //SMTP server port
        authInfo.userName = appSettings.EmailSettings.userName; //User name
        authInfo.password = appSettings.EmailSettings.passWord; //Password
        authInfo.useTls = appSettings.EmailSettings.useTls; //Use STARTTLS rather than implicit TLS
        authInfo.prngAlgo = YARROW_PRNG_ALGO; //PRNG algorithm
        authInfo.prngContext = &appSettings.yarrowContext; //PRNG context

        char* subject;
        subject = pvPortMalloc(256);
        char valueBuffer[10];
        getAnalogInputInString(valueBuffer);
        sprintf(subject, "[%s] analog alarm (%s V)", appSettings.CardName,valueBuffer);


        SmtpMailAddr recipients[4];

        int recipientCount = CreateMailAddressFromString(appSettings.Notifications[NOTIFICATION_ANALOG].mail.recipients, recipients);
        static SmtpMail mail;
        mail.from.name = NULL;
        mail.from.addr = appSettings.EmailSettings.userName;
        mail.from.type = SMTP_RCPT_TYPE_TO;
        mail.recipients = recipients;
        mail.recipientCount = recipientCount; //Recipient count
        mail.dateTime = "NOW"; //Date
        mail.subject = subject; //Subject
        mail.body = "This is an automatically generated mail by the VM204 card";


        error = smtpSendMail(&authInfo, &mail);
        vPortFree(subject);
        int i;
        for (i = 0; i < recipientCount; i++) {
            vPortFree(recipients[i].addr);
        }
    } else {
        return ERROR_NOT_FOUND;
    }
    //Return status code
    return error;
}

int CreateMailAddressFromString(char * string, SmtpMailAddr* recipients) {
    char cpy[255];
    char* cptr;
    int recipient = 0;

    strcpy(cpy, string);
    cptr = strtok(cpy, ";");
    do {
        recipients[recipient].name = NULL;
        recipients[recipient].addr = strDuplicate(cptr);
        recipients[recipient].type = SMTP_RCPT_TYPE_TO;
        recipient++;
        cptr = strtok(NULL, ";");
    } while (cptr != NULL);
    return recipient;
}

error_t sendBootMail() {
    error_t error;

    getCurrentTime();

    //Authentication information
    SmtpAuthInfo authInfo;
    authInfo.interface = NULL;
    authInfo.serverName = appSettings.EmailSettings.serverName; //SMTP server name
    authInfo.serverPort = appSettings.EmailSettings.serverPort; //SMTP server port
    authInfo.userName = appSettings.EmailSettings.userName; //User name
    authInfo.password = appSettings.EmailSettings.passWord; //Password
    authInfo.useTls = appSettings.EmailSettings.useTls; //Use STARTTLS rather than implicit TLS
    authInfo.prngAlgo = YARROW_PRNG_ALGO; //PRNG algorithm
    authInfo.prngContext = &appSettings.yarrowContext; //PRNG context

    char* subject;
    subject = pvPortMalloc(128);


    sprintf(subject, "[%s] %s has booted up on %s (UTC)", appSettings.CardName, appSettings.CardName, formatDate(&appSettings.date, NULL));
    SmtpMailAddr recipients[4];

    int recipientCount = CreateMailAddressFromString(appSettings.Notifications[NOTIFICATION_BOOT].mail.recipients, recipients);
    static SmtpMail mail;
    mail.from.name = NULL;
    mail.from.addr = appSettings.EmailSettings.userName;
    mail.from.type = SMTP_RCPT_TYPE_TO;
    mail.recipients = recipients;
    mail.recipientCount = recipientCount; //Recipient count
    mail.dateTime = "NOW"; //Date
    mail.subject = subject; //Subject
    char ip[16];
    mail.body = pvPortMalloc(128);
    ipv4AddrToString(netGetDefaultInterface()->ipv4Config.addr, ip);
    sprintf(mail.body, "This is an automatically generated mail by the VM204 card\r\n%s", ip);


    error = smtpSendMail(&authInfo, &mail);
    if (subject)
        vPortFree(subject);
    if (mail.body)
        vPortFree(mail.body);
    int i;
    for (i = 0; i < recipientCount; i++) {
        if (recipients[i].addr)
            vPortFree(recipients[i].addr);
    }
    //Return status code
    return error;
}

error_t sendMail(int input, int reason) {
    error_t error;
    SmtpAuthInfo authInfo;
    authInfo.interface = NULL;
    authInfo.serverName = appSettings.EmailSettings.serverName; //SMTP server name
    authInfo.serverPort = appSettings.EmailSettings.serverPort; //SMTP server port
    authInfo.userName = appSettings.EmailSettings.userName; //User name
    authInfo.password = appSettings.EmailSettings.passWord; //Password
    authInfo.useTls = appSettings.EmailSettings.useTls; //Use STARTTLS rather than implicit TLS
    authInfo.prngAlgo = YARROW_PRNG_ALGO; //PRNG algorithm
    authInfo.prngContext = &appSettings.yarrowContext; //PRNG context


    if (appSettings.Notifications[input + 4].enable && (reason == FALLING)) {
        getCurrentTime();
        char* subject;
        subject = pvPortMalloc(128);
        SmtpMailAddr recipients[4];
        int recipientCount = 0;

        sprintf(subject, SUBJECT_INPUT_FALLING, appSettings.CardName, appSettings.IoSettings.inputs[input].Name, formatDate(&appSettings.date, NULL));
        recipientCount = CreateMailAddressFromString(appSettings.Notifications[input + 4].mail.recipients, recipients);

        static SmtpMail mail;
        mail.from.name = NULL;
        mail.from.addr = appSettings.EmailSettings.userName;
        mail.recipients = recipients;
        mail.recipientCount = recipientCount;
        mail.dateTime = "NOW"; //Date
        mail.subject = subject; //Subject
        mail.body = "This is an automatically generated mail by the VM204 card";
        error = smtpSendMail(&authInfo, &mail);
        if (subject)
            vPortFree(subject);
        int i;
        for (i = 0; i < recipientCount; i++) {
            if (recipients[i].addr)
                vPortFree(recipients[i].addr);
        }
    } else if (appSettings.Notifications[input].enable && (reason == RISING)) {
        getCurrentTime();
        char* subject;
        subject = pvPortMalloc(128);
        SmtpMailAddr recipients[4];
        int recipientCount = 0;

        sprintf(subject, SUBJECT_INPUT_RISING, appSettings.CardName, appSettings.IoSettings.inputs[input].Name, formatDate(&appSettings.date, NULL));
        recipientCount = CreateMailAddressFromString(appSettings.Notifications[input].mail.recipients, recipients);

        static SmtpMail mail;
        mail.from.name = NULL;
        mail.from.addr = appSettings.EmailSettings.userName;
        mail.recipients = recipients;
        mail.recipientCount = recipientCount;
        mail.dateTime = "NOW"; //Date
        mail.subject = subject; //Subject
        mail.body = "This is an automatically generated mail by the VM204 card";
        error = smtpSendMail(&authInfo, &mail);
        vPortFree(subject);
        int i;
        for (i = 0; i < recipientCount; i++) {
            vPortFree(recipients[i].addr);
        }
    }

    //Return status code
    return error;
}

error_t sendTestMail(HttpConnection* connection ) {
    char *separator;
    char *property;
    char *value;
    char *p;
    SmtpMailAddr recipients[4];
    error_t error;
    uint_t i;
    uint_t j;
    uint_t n;
    char_t *buffer;

     //Authentication information
    SmtpAuthInfo authInfo;
    authInfo.interface = NULL;
    authInfo.serverName = appSettings.EmailSettings.serverName; //SMTP server name
    authInfo.serverPort = appSettings.EmailSettings.serverPort; //SMTP server port
    authInfo.userName = appSettings.EmailSettings.userName; //User name
    authInfo.password = appSettings.EmailSettings.passWord; //Password
    authInfo.useTls = appSettings.EmailSettings.useTls; //Use STARTTLS rather than implicit TLS
    authInfo.prngAlgo = YARROW_PRNG_ALGO; //PRNG algorithm
    authInfo.prngContext = &appSettings.yarrowContext; //PRNG context
    
    SmtpMailAddr recipient[1];
    recipient[0].name = NULL;
    recipient[0].addr = strDuplicate(appSettings.EmailSettings.userName);
    recipient[0].type = SMTP_RCPT_TYPE_TO;

    SmtpMail mail;
    mail.from.name = NULL;
    mail.from.addr = strDuplicate(appSettings.EmailSettings.userName);
    mail.from.type = SMTP_RCPT_TYPE_TO;
    mail.recipients = recipient;
    mail.recipientCount = 1; //Recipient count
    mail.dateTime = strDuplicate("NOW"); //Date
    mail.subject = strDuplicate("VM204 Test Mail"); //Subject

    mail.body =  strDuplicate("If you received this mail, everything is OK");

    //Send mail
    error = smtpSendMail(&authInfo, &mail);
    osFreeMem((void *)mail.from.addr);
    osFreeMem((void *)recipient[0].addr);
    osFreeMem((void *)mail.subject);
    osFreeMem((void *)mail.body);

    //Point to the scratch buffer
         buffer = connection->buffer + 384;

         char status[64] = "";
         
         //Format XML data
         if(error == NO_ERROR)
            strcpy(status,"Mail successfully sent");
         else if(error == ERROR_NAME_RESOLUTION_FAILED)
            strcpy(status,"Cannot resolve SMTP server name");
         else if(error == ERROR_AUTHENTICATION_FAILED)
            strcpy(status,"Authentication failed");
         else if(error == ERROR_UNEXPECTED_RESPONSE)
            strcpy(status,"Unexpected response from SMTP server");
         else
            sprintf(status, "Failed to send mail (error %d)", error);

         createMailStatus(buffer,status);
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
         //Any error to report?
         osFreeMem((void *)mail.from.addr);
    osFreeMem((void *)recipient[0].addr);
    osFreeMem((void *)mail.subject);
    osFreeMem((void *)mail.body);
         return error;

    
}

void createMailStatus(char* buffer,char* status)
{
    sprintf(buffer,"{\"status\":\"%s\"}",status);
}
