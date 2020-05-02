//
// Created by marcos on 26/4/20.
//

#include "Server.h"
#include "CommandReceiver.h"

int main() {
    Server server;
    CommandReceiver cReceiver;
    commandReceiverCreate(&cReceiver);
    serverCreate(&server, "8080");

    serverConnect(&server);
    serverReceive(&server, &cReceiver);
    commandReceiverPrint(&cReceiver);

    serverDestroy(&server);
    commandReceiverDestroy(&cReceiver);
}
