//
// Created by marcos on 25/4/20.
//

#define _POSIX_C_SOURCE 200112L

#include "ErrorVerifier.h"
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void errorVerifierGetAddrInfo(ErrorVerifier* this, int flag) {
    if (flag != 0) {
        fprintf(stderr, "Error in getaddrinfo: %s\n", gai_strerror(flag));
        exit(EXIT_FAILURE);
    }
}

void errorVerifierSend(ErrorVerifier* this, int flag) {
    if (flag == -1) {
        fprintf(stderr, "Error in send: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void errorVerifierReceive(ErrorVerifier* this, int flag) {
    if (flag == -1) {
        fprintf(stderr, "Error in receive: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void errorVerifierConnect(ErrorVerifier* this, struct addrinfo* rp) {
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }
}

void errorVerifierBind(ErrorVerifier* this, struct addrinfo* rp) {
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }
}

void errorVerifierCreate(ErrorVerifier* this) {
    this->x = 0;
}

void errorVerifierDestroy(ErrorVerifier* this) {
    //do nothing
}
