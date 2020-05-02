//
// Created by marcos on 25/4/20.
//

#ifndef TP1DBUS_ERRORVERIFIER_H
#define TP1DBUS_ERRORVERIFIER_H

#include <netdb.h>

struct addrinfo;

typedef struct ErrorVerifier {
    int x;
} ErrorVerifier;

void errorVerifierCreate(ErrorVerifier* this);

void errorVerifierSend(ErrorVerifier* this, int flag);

void errorVerifierReceive(ErrorVerifier* this, int flag);

void errorVerifierDestroy(ErrorVerifier* this);

void errorVerifierGetAddrInfo(ErrorVerifier* this, int flag);

void errorVerifierConnect(ErrorVerifier* this, struct addrinfo* rp);

void errorVerifierBind(ErrorVerifier* this, struct addrinfo* rp);

#endif //TP1DBUS_ERRORVERIFIER_H
