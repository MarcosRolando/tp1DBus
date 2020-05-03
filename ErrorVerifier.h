//
// Created by marcos on 25/4/20.
//

#ifndef TP1DBUS_ERRORVERIFIER_H
#define TP1DBUS_ERRORVERIFIER_H

#include <netdb.h>
#include <stdbool.h>

struct addrinfo;

typedef struct ErrorVerifier {
    bool closedComms;
} ErrorVerifier;

void errorVerifierCreate(ErrorVerifier* this);

void errorVerifierSend(ErrorVerifier* this, int flag);

void errorVerifierReceive(ErrorVerifier* this, int flag);

void errorVerifierDestroy(ErrorVerifier* this);

void errorVerifierGetAddrInfo(ErrorVerifier* this, int flag);

bool errorVerifierClosedComms(ErrorVerifier* this);

void errorVerifierConnect(ErrorVerifier* this, struct addrinfo* rp);

void errorVerifierBind(ErrorVerifier* this, struct addrinfo* rp);

#endif //TP1DBUS_ERRORVERIFIER_H
