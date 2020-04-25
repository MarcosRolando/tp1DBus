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

void clientDestroy(Client* this);

int test();

#endif //TP1DBUS_CLIENT_H
