//
// Created by marcos on 26/4/20.
//

#include "Messenger.h"
#include "Socket.h"
#include <string.h>
#include <stdlib.h>

void messengerCreate(Messenger* this) {
    //do nothing
}

void enviarMensajePrueba(Messenger* this, Socket* socket, char* message) {
    int length = strlen(message);
    int destiny = socketGetFileDescriptor(socket);
    int bytesSent = 0, s = 0;

    while (bytesSent < length) {
        s = send(destiny, message, length - bytesSent, MSG_NOSIGNAL);
        if (s == -1) break;
        bytesSent += s;
    }
}

char* recibirMensajePrueba(Messenger* this, Socket* socket) {
    int source = socketGetFileDescriptor(socket);
    int bytesRecieved = 0, s = 0;
    char* buff = malloc(sizeof(char)*6);
    memset(buff, 0, 6);
    while (bytesRecieved < 5 && s != -1) {
        s = recv(source, buff, 5 - bytesRecieved, 0);
        if (s!=-1) bytesRecieved += s;
    }
    return buff;
}

void messengerDestroy(Messenger* this) {
    //do nothing;
}