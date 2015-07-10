#include "os_port.h"
#include "shared.h"
#include "http/http_server.h"

void createAPIKeyJson(char* data) {
    sprintf(data, "{\"ApiKey\":\"%s\"}", appSettings.key);
}

bool_t isAPIAuthorized(char * query) {
    char uri[128];
    char property[32];
    char* seperator;
    char* ampersand;
    char pair[64];
    char value[32];
    char queryString[64];
    bool_t auth;
    auth = FALSE;
    strcpy(queryString, query);
    ampersand = strchr(queryString, '&');
    if (ampersand) {
        *ampersand = '\0';
        strcpy(pair, queryString);
        while (pair != NULL) {
            seperator = strchr(pair, '=');
            if (seperator) {
                *seperator = '\0';
                strcpy(property, pair);
                strcpy(value, seperator + 1);
                if (!strcasecmp(property, "key")) {
                    if (!strcasecmp(value, appSettings.key)) {
                        auth = TRUE;
                    }
                }
            }
            if (strchr(queryString, '&') == NULL) {
                strcpy(pair, ampersand + 1);
                if (strlen(pair) == 0) {
                    break;
                } else {
                    ampersand++;
                    ampersand += strlen(pair);
                }
            } else {
                ampersand = strchr(queryString, '&');
                strcpy(pair, ampersand + 1);
            }

        }
    } else//No second parameter still check for key
    {
        seperator = strchr(query, '=');
        if (seperator) {
            *seperator = '\0';
            strcpy(property, query);
            strcpy(value, seperator + 1);
            if (!strcasecmp(property, "key")) {
                if (!strcasecmp(value, appSettings.key)) {
                    auth = TRUE;
                }
            }
        }
    }
    return auth;
}

bool_t parseRelayAPICommand(char* query, char* relays) {
    char uri[128];
    char* ampersand;
    char* cursor;
    char* endAddress;
    char pair[64];
    char property[32];
    char value[32];
    char queryString[64];
    bool_t auth;
    auth = FALSE;
    strcpy(queryString, query);
    cursor = queryString;
    endAddress = queryString + strlen(queryString);
    while (cursor != endAddress) {
        ampersand = strchr(cursor, '&');
        if (ampersand) {
            *ampersand = '\0';
            getPair(cursor, value, property);
            if (!strcasecmp(property, "key")) {
                if (!strcasecmp(value, appSettings.key)) {
                    auth = TRUE;
                }
            } else if (!strcasecmp(property, "relay")) {
                strcpy(relays, value);
            } 
            cursor = ampersand + 1;
        } else {
             getPair(cursor, value, property);
            if (!strcasecmp(property, "key")) {
                if (!strcasecmp(value, appSettings.key)) {
                    auth = TRUE;
                }
            } else if (!strcasecmp(property, "relay")) {
                strcpy(relays, value);
            } 
            cursor = endAddress;
        }
    }
    return auth;
}

bool_t parsePulseAPICommand(char* query, char* relays, int* time) {
    char uri[128];
    char* ampersand;
    char* cursor;
    char* endAddress;
    char pair[64];
    char property[32];
    char value[32];
    char queryString[64];
    bool_t auth;
    auth = FALSE;
    strcpy(queryString, query);
    cursor = queryString;
    endAddress = queryString + strlen(queryString);
    while (cursor != endAddress) {
        ampersand = strchr(cursor, '&');
        if (ampersand) {
            *ampersand = '\0';
            getPair(cursor, value, property);
            if (!strcasecmp(property, "key")) {
                if (!strcasecmp(value, appSettings.key)) {
                    auth = TRUE;
                }
            } else if (!strcasecmp(property, "relay")) {
                strcpy(relays, value);
            } else if (!strcasecmp(property, "time")) {
                if(!strcmp(value,"default"))
                {
                    *time = -1;
                }
                else
                {
                    *time = atoi(value);
                }
            }
            cursor = ampersand + 1;
        } else {
             getPair(cursor, value, property);
            if (!strcasecmp(property, "key")) {
                if (!strcasecmp(value, appSettings.key)) {
                    auth = TRUE;
                }
            } else if (!strcasecmp(property, "relay")) {
                strcpy(relays, value);
            } else if (!strcasecmp(property, "time")) {
                *time = atoi(value);
            }
            cursor = endAddress;
        }
    }
    return auth;
}

void getPair(char* cptr, char* value, char* property) {
    char pair[128];
    char* seperator;
    strcpy(pair, cptr);
    seperator = strchr(pair, '=');
    if (seperator) {
        *seperator = '\0';
        strcpy(property, pair);
        strcpy(value, seperator + 1);
    }
}

error_t sendAPIKey(HttpConnection *connection) {
    char_t *buffer;
    char_t *data;
    int n;
    error_t error;
    buffer = connection->buffer + 384;

    createAPIKeyJson(buffer);
    n = strlen(buffer);
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

bool_t authUser(char * query) {
    char uri[128];
    char property[32];
    char* seperator;
    char* ampersand;
    char pair[64];
    char value[32];
    char queryString[64];
    char user[32];
    char password[32];
    bool_t auth;
    auth = FALSE;
    strcpy(queryString, query);
    ampersand = strchr(queryString, '&');
    if (ampersand) {
        *ampersand = '\0';
        strcpy(pair, queryString);
        while (pair != NULL) {
            seperator = strchr(pair, '=');
            if (seperator) {
                *seperator = '\0';
                strcpy(property, pair);
                strcpy(value, seperator + 1);
                if (!strcasecmp(property, "user")) {
                    strcpy(user, value);
                }
                if (!strcasecmp(property, "password")) {
                    strcpy(password, value);
                }
            }
            if (strchr(queryString, '&') == NULL) {
                strcpy(pair, ampersand + 1);
                if (strlen(pair) == 0) {
                    break;
                } else {
                    ampersand++;
                    ampersand += strlen(pair);
                }
            } else {
                ampersand = strchr(queryString, '&');
                strcpy(pair, ampersand + 1);
            }

        }
    } else//No second parameter still check for key
    {
        seperator = strchr(query, '=');
        if (seperator) {
            *seperator = '\0';
            strcpy(property, query);
            strcpy(value, seperator + 1);
            if (!strcasecmp(property, "user")) {
                strcpy(user, value);
            }
            if (!strcasecmp(property, "password")) {
                strcpy(password, value);
            }
        }
    }
    if (!strcmp(user, appSettings.AuthSettings.Login) && !strcmp(password, appSettings.AuthSettings.Password)) {
        return TRUE;
    } else {
        return FALSE;
    }
}