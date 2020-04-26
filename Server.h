//
// Created by marcos on 25/4/20.
//

#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "Socket.h"
#include "ErrorVerifier.h"
#include "Messenger.h"

typedef struct Server {
    char* port;
    Messenger courier;
    Socket socket;
    ErrorVerifier eVerifier;
} Server;

void serverCreate(Server* this, char* port);

int serverConnect(Server* this);

void serverDestroy(Server* this);

#endif //TP1_SERVER_H
