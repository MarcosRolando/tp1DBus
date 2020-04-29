//
// Created by marcos on 26/4/20.
//

#include "Messenger.h"
#include "Socket.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void messengerCreate(Messenger* this) {
    errorVerifierCreate(&this->eVerifier);
}

void messengerSend(Messenger* this, Socket* socket, char* message, size_t length) {
    int destiny = socketGetFileDescriptor(socket);
    int bytesSent = 0, s = 0;
    bool lostConection = false;

    while (!lostConection && (bytesSent < length)) {
        s = send(destiny, message, length - bytesSent, MSG_NOSIGNAL);
        errorVerifierSend(&this->eVerifier, s);
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
    errorVerifierDestroy(&this->eVerifier);
}