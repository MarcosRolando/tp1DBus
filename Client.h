//
// Created by marcos on 24/4/20.
//

#ifndef TP1DBUS_CLIENT_H
#define TP1DBUS_CLIENT_H

#include "Socket.h"
#include "ErrorVerifier.h"
#include "Messenger.h"
#include "ClientCommand.h"

typedef struct Client {
    char* host; //hostname
    char* port; //servicename
    Messenger courier;
    Socket socket;
    ErrorVerifier eVerifier;
} Client;

void clientCreate(Client* this, char* host, char* port);

void clientSend(Client* this, ClientCommand* command, char confirmMessage[]);

int clientConnect(Client* this);

void clientDestroy(Client* this);

#endif //TP1DBUS_CLIENT_H
