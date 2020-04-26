//
// Created by marcos on 25/4/20.
//

#define _POSIX_C_SOURCE 200112L

#include "ErrorVerifier.h"
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

void errorVerifierGetAddrInfo(ErrorVerifier* this, int flag) {
    if (flag != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(flag));
        exit(EXIT_FAILURE);
    }
}

void errorVerifierConnect(ErrorVerifier* this, struct addrinfo* rp) {
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }
}

void errorVerifierCreate(ErrorVerifier* this) {
    //do nothing
}

void errorVerifierDestroy(ErrorVerifier* this) {
    //do nothing
}
