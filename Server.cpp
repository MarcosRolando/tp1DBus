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

int main() {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */

    s = getaddrinfo(NULL, "8081", &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    int val = 1;

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
            continue;

        setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(sfd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */

    listen(sfd, 20);

    int sktConnected = accept(sfd, NULL, NULL);
    int bytesRecieved = 0;
    char buff[5];
    memset(buff, 0, 5);
    while (bytesRecieved < 4 && s != -1) {
        s = recv(sktConnected, buff, 4 - bytesRecieved, 0);
        if (s!=-1) bytesRecieved += s;
    }
    printf("%s", buff);

    close(sktConnected);
    close(sfd);

    return 0;

}