//
// Created by marcos on 26/4/20.
//
//
// Created by marcos on 25/4/20.
//
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Server.h"

#define MAX_LISTENERS 1

void serverCreate(Server* this, char* port) {
    this->port = port;
    socketCreate(&this->socket);
    messengerCreate(&this->courier);
    errorVerifierCreate(&this->eVerifier);
}

void serverDestroy(Server* this) {
    socketDestroy(&this->socket);
    messengerDestroy(&this->courier);
    errorVerifierDestroy(&this->eVerifier);
}

static struct addrinfo* _getAddresses(Server* this) {
    struct addrinfo hints, *result;
    int s; //flag por si hubo un error, lo maneja ErrorVerifier
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    s = getaddrinfo(NULL, this->port, &hints, &result);
    errorVerifierGetAddrInfo(&this->eVerifier, s);
    return result;
}


int serverConnect(Server* this) {
    struct addrinfo* addresses = _getAddresses(this);
    socketBind(&this->socket, addresses);
    freeaddrinfo(addresses); //en este punto ya logre bindear al socket y puedo empezar a aceptar conexiones
    socketMaxListen(&this->socket, MAX_LISTENERS);
    Socket peer = socketAccept(&this->socket);
    char* message = recibirMensajePrueba(&this->courier, &peer);
    printf("%s", message);
    socketDestroy(&peer);
    return 0;
}
