//
// Created by marcos on 26/4/20.
//

#include "Server.h"

int main() {
    Server server;
    serverCreate(&server, "8080");
    serverConnect(&server);
    serverDestroy(&server);
}
