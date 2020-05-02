//
// Created by marcos on 24/4/20.
//

#define _POSIX_C_SOURCE 200112L

#include "Client.h"
#include <netdb.h>
#include <string.h>

static struct addrinfo* _getAddresses(Client* this) {
    struct addrinfo hints, *result;
    int s; //flag por si hubo un error, lo maneja ErrorVerifier
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */
    s = getaddrinfo(this->host, this->port, &hints, &result);
    errorVerifierGetAddrInfo(&this->eVerifier, s);
    return result;
}

int clientConnect(Client* this) {
    struct addrinfo* addresses = _getAddresses(this);
    socketConnect(&this->socket, addresses);
    freeaddrinfo(addresses); //en este punto ya logre conectarme al socket y puedo empezar a mandar mensajes
    return 0;
}

void clientSend(Client* this, ClientCommand* command) {
    char* header = NULL;
    uint32_t length = clientCommandGetHeader(command, &header, 0x01);
    messengerSend(&this->courier, &this->socket, header, length);
    char* body = NULL;
    length = clientCommandGetBody(command, &body);
    messengerSend(&this->courier, &this->socket, body, length);
}

void clientCreate(Client* this, char* host, char* port) {
    this->host = host;
    this->port = port;
    socketCreate(&this->socket);
    errorVerifierCreate(&this->eVerifier);
    messengerCreate(&this->courier);
}

void clientDestroy(Client* this) {
    socketDestroy(&this->socket);
    errorVerifierDestroy(&this->eVerifier);
    messengerDestroy(&this->courier);
}





