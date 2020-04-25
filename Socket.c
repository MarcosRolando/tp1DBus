//
// Created by marcos on 25/4/20.
//

#include "Socket.h"
#include <netdb.h>
#include <unistd.h>

void socketCreate(Socket* this) {
    //do nothing
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
    //do nothing
}
