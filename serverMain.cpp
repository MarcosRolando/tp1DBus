//
// Created by marcos on 26/4/20.
//

#include "Server.h"

int main() {
    Server server;
    serverCreate(&server);
    serverConnect(&server);
    serverDestroy(&server);

    return 0;
}