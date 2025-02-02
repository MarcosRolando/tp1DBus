//
// Created by marcos on 26/4/20.
//

#ifndef TP1DBUS_MESSENGER_H
#define TP1DBUS_MESSENGER_H

#include "Socket.h"
#include "ErrorVerifier.h"

typedef struct Messenger {
    ErrorVerifier* eVerifier;
} Messenger;

void messengerCreate(Messenger* this, ErrorVerifier* eVerifier);

void messengerSend(Messenger* this, Socket* socket, char* message,
                                                                size_t length);

void messengerReceive(Messenger* this, Socket* socket, char** message,
                                                                size_t length);

void messengerDestroy(Messenger* this);

#endif //TP1DBUS_MESSENGER_H
