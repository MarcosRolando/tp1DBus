//
// Created by marcos on 25/4/20.
//

#ifndef TP1DBUS_SOCKET_H
#define TP1DBUS_SOCKET_H

#include <netdb.h>
#include "ErrorVerifier.h"

struct addrinfo;

typedef struct Socket{
    int fd; //file descriptor
    ErrorVerifier eVerifier;
} Socket;

void socketCreate(Socket* this);

void socketConnect(Socket* this, struct addrinfo* addresses);

int socketGetFileDescriptor(Socket* this);

void socketBind(Socket* this, struct addrinfo* addresses);

void socketMaxListen(Socket* this, int max);

Socket socketAccept(Socket* this);

void socketDestroy(Socket* this);

#endif //TP1DBUS_SOCKET_H
