//
// Created by marcos on 24/4/20.
//

#ifndef TP1DBUS_CLIENT_H
#define TP1DBUS_CLIENT_H

#include "Socket.h"
#include "ErrorVerifier.h"

typedef struct Client {
    char* host; //hostname
    char* port; //servicename
    Socket socket;
    ErrorVerifier eVerifier;
} Client;

void clientCreate(Client* this, char* host, char* port);

int clientConnect(Client* this);

void clientDestroy(Client* this);

#endif //TP1DBUS_CLIENT_H
