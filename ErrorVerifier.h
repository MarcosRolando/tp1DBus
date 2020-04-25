//
// Created by marcos on 25/4/20.
//

#ifndef TP1DBUS_ERRORVERIFIER_H
#define TP1DBUS_ERRORVERIFIER_H

#include <netdb.h>

typedef struct ErrorVerifier {
    int evitoStructHasNoMember;
} ErrorVerifier;

void errorVerifierCreate(ErrorVerifier* this);

void errorVerifierDestroy(ErrorVerifier* this);

void errorVerifierGetAddrInfo(ErrorVerifier* this, int flag);

void errorVerifierConnect(ErrorVerifier* this, struct addrinfo* rp);

#endif //TP1DBUS_ERRORVERIFIER_H
