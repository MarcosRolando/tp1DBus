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

static void _DBusNextCommand(Client* client, FileReader* reader, uint32_t messageID) {
    ClientCommand command;
    clientCommandCreate(&command, messageID);
    char* commandRead = fileReaderReadFile(reader);
    if (commandRead) {
        clientCommandReadCommand(&command, commandRead);
        char confirmMessage[4];
        clientSend(client, &command, confirmMessage);
        printf("0x%04x: %s", messageID, confirmMessage);
    }
    clientCommandDestroy(&command);
}

static void _DBusClient(DBus* this) {
    Client client;
    clientCreate(&client, "localhost", "8080");
    FileReader reader;
    fileReaderCreate(&reader, "client0.in");
    clientConnect(&client);
    uint32_t messageID = 1;

    while (!fileReaderDoneReading(&reader)) {
        _DBusNextCommand(&client, &reader, messageID);
        messageID++;
    }

    clientDestroy(&client);
    fileReaderDestroy(&reader);
}

static void _DBusServer(DBus* this) {
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
