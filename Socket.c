//
// Created by marcos on 25/4/20.
//

#define _POSIX_C_SOURCE 200112L

#include "Socket.h"
#include <netdb.h>
#include <unistd.h>
#include <string.h>

void socketCreate(Socket* this) {
    //do nothing
}

void mensajePrueba(Socket* this) {
    char* mensaje = "hola\n";
    int length = strlen(mensaje);
    int bytesSent = 0, s;

    while (bytesSent < length) {
        s = send(this->fd, mensaje, length - bytesSent, MSG_NOSIGNAL);
        if (s == -1) break;
        bytesSent += s;
    }
}

void socketConnect(Socket* this, struct addrinfo* addresses) {
    struct addrinfo* rp;
    for (rp = addresses; rp != NULL; rp = rp->ai_next) {
        this->fd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (this->fd  == -1)
            continue;

        if (connect(this->fd , rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

        close(this->fd );
    }
    errorVerifierConnect(&this->eVerifier, rp);
}

void socketDestroy(Socket* this) {
    close(this->fd);
}
