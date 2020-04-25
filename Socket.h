//
// Created by marcos on 25/4/20.
//

#ifndef TP1DBUS_SOCKET_H
#define TP1DBUS_SOCKET_H

typedef struct Socket{
    int fd; //file descriptor
} Socket;

void socketCreate(Socket* this);

void socketDestroy(Socket* this);

#endif //TP1DBUS_SOCKET_H
