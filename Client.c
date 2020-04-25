//
// Created by marcos on 24/4/20.
//

#define _POSIX_C_SOURCE 200112L

#include "Client.h"
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>



int test() {
    int s = 0;
    bool are_we_connected = false;

    // A quien nos queremos conectar
    const char *hostname = "localhost";
    const char *servicename = "8081";

    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    int skt = 0;

    /* Creo una especie de filtro para decir que direcciones me interesan
       En este caso, TCP sobre IPv4 para ser usada por un socket 'activo'
       (no es para un server)
    */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */


    /* Obtengo la (o las) direcciones segun el nombre de host y servicio que
       busco

       De todas las direcciones posibles, solo me interesan aquellas que sean
       IPv4 y TCP (segun lo definido en hints)

       El resultado lo guarda en result
    */
    s = getaddrinfo(hostname, servicename, &hints, &result);

    /* Es muy importante chequear los errores.
       En caso de uno, usar gai_strerror para traducir el codigo de error (s)
       a un mensaje humanamente entendible.
    */
    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    /* getaddrinfo retorna una **lista** de direcciones. Hay que iterarla
       para encontrar la que mejor se ajusta.
       (generalmente la primera direccion es la mejor, pero dependera de
       cada caso)
       En este caso voy a probar cada direccion posible. La primera que
       funcione sera la que se usara por el resto del ejemplo.
    */
    for (ptr = result; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {
        /* Creamos el socket definiendo la familia (deberia ser AF_INET IPv4),
           el tipo de socket (deberia ser SOCK_STREAM TCP) y el protocolo (0) */
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt == -1) {
            printf("Error: %s\n", strerror(errno));
        }
        else
        {
            /* Nos conectamos a la fiuba
               ai_addr encapsula la IP y el puerto del server.
               La estructura es automaticamente creada por getaddrinfo */
            s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
            if (s == -1) {
                printf("Error: %s\n", strerror(errno));
                close(skt);
            }
            are_we_connected = (s != -1); // nos conectamos?
        }
    }

    /* Finalmente, la **lista** de direcciones debe ser liberada */
    freeaddrinfo(result);

    char* mensaje = "hola";
    int length = strlen(mensaje);
    int bytesSent = 0;

    while (bytesSent < length) {
        s = send(skt, mensaje, length - bytesSent, MSG_NOSIGNAL);
        if (s == -1) break;
        bytesSent += s;
    }

    close(skt);

    return 0;
}

static struct addrinfo* _setHints(Client* this) {
    struct addrinfo hints, *result;
    int s; //flag por si hubo un error, lo maneja ErrorVerifier
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */
    s = getaddrinfo(this->host, this->port, &hints, &result);
}

int clientConnect(Client* this) {
    _setHints(this);
}

void clientCreate(Client* this, char* host, char* port) {
    this->host = host;
    this->port = port;
    socketCreate(&this->socket);
}

void clientDestroy(Client* this) {
    socketDestroy(&this->socket);
}





