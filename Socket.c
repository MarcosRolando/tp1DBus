//
// Created by marcos on 25/4/20.
//

#define _POSIX_C_SOURCE 200112L

#include "Socket.h"
#include <netdb.h>
#include <unistd.h>
#include <string.h>

static void _setFileDescriptor(Socket* this, int fd) {
    this->fd = fd;
}

void socketCreate(Socket* this, ErrorVerifier* eVerifier) {
    this->eVerifier = eVerifier;
}

int socketGetFileDescriptor(Socket* this) {
    return this->fd;
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

        close(this->fd);
    }
    errorVerifierConnect(this->eVerifier, rp);
}

void socketBind(Socket* this, struct addrinfo* addresses) {
    struct addrinfo* rp;
    int val = 1; //no entiendo esto pero el dipa lo hace
    for (rp = addresses; rp != NULL; rp = rp->ai_next) {
        this->fd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (this->fd == -1)
            continue;

        setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

        if (bind(this->fd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(this->fd);
    }
    errorVerifierBind(this->eVerifier, rp);
}

Socket socketAccept(Socket* this) {
    int peerFd = accept(this->fd, NULL, NULL);
    Socket peer;
    socketCreate(&peer, this->eVerifier);
    _setFileDescriptor(&peer, peerFd);
    return peer;
}

void socketMaxListen(Socket* this, int max) {
    listen(this->fd, 20);
}

void socketDestroy(Socket* this) {
    shutdown(this->fd, SHUT_RDWR);
    close(this->fd);
}
