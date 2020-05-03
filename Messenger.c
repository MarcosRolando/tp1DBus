//
// Created by marcos on 26/4/20.
//

#include "Messenger.h"
#include "Socket.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void messengerCreate(Messenger* this, ErrorVerifier* eVerifier) {
    this->eVerifier = eVerifier;
}

void messengerSend(Messenger* this, Socket* socket, char* message, size_t length) {
    int destiny = socketGetFileDescriptor(socket);
    size_t bytesSent = 0;
    int s = 0;

    while (bytesSent < length) {
        s = send(destiny, message + bytesSent, length - bytesSent, MSG_NOSIGNAL);
        errorVerifierSend(this->eVerifier, s);
        bytesSent += s;
    }
}

void messengerReceive(Messenger* this, Socket* socket, char** message, size_t length) {
    int source = socketGetFileDescriptor(socket);
    size_t bytesReceived = 0;
    int s = 0;

    while (bytesReceived < length) {
        s = recv(source, *message + bytesReceived, length - bytesReceived, 0);
        errorVerifierReceive(this->eVerifier, s);
        if (errorVerifierClosedComms(this->eVerifier)) break;
        bytesReceived += s;
    }
}

void messengerDestroy(Messenger* this) {
    errorVerifierDestroy(this->eVerifier);
}