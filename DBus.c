//
// Created by marcos on 2/5/20.
//

#include "DBus.h"
#include "ClientCommand.h"
#include "FileReader.h"
#include "Client.h"
#include "Server.h"
#include <string.h>

void DBusCreate(DBus* this) {
    //do nothing
}

void _DBusClient(DBus* this) {
    ClientCommand command;
    clientCommandCreate(&command, 0x01);
    FileReader reader;
    fileReaderCreate(&reader, stdin);

    char* cmd = fileReaderReadFile(&reader);
    clientCommandReadCommand(&command, cmd);

    char confirmMessage[3];

    Client client;
    clientCreate(&client, "localhost", "8080");
    clientConnect(&client);
    clientSend(&client, &command, confirmMessage);

    printf("%s", confirmMessage);

    clientDestroy(&client);
    clientCommandDestroy(&command);
    fileReaderDestroy(&reader);
}

void _DBusServer(DBus* this) {
    Server server;
    serverCreate(&server, "8080");
    serverConnect(&server);
    bool serverIsDone = false;

    while (!serverIsDone) {
        CommandReceiver cReceiver;
        commandReceiverCreate(&cReceiver);
        serverIsDone = serverReceive(&server, &cReceiver);
        if (!serverIsDone) commandReceiverPrint(&cReceiver);
        commandReceiverDestroy(&cReceiver);
    }

    serverDestroy(&server);
}

void DBusRun(DBus* this, int argc, const char* argv[]) {
    const char* mode = *argv + (strlen(*argv) - 6);
    if (!strcmp(mode, "client")) _DBusClient(this);
    else if (!strcmp(mode, "server")) _DBusServer(this);
}

void DBusDestroy(DBus* this) {
    //do nothing
}
