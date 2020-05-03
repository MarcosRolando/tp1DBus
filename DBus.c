//
// Created by marcos on 2/5/20.
//

#include "DBus.h"
#include "ClientCommand.h"
#include "FileReader.h"
#include "Client.h"
#include "Server.h"
#include <string.h>

#define ERROR -1
#define OK 0

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
        printf("0x%08x: %s", messageID, confirmMessage);
    }
    clientCommandDestroy(&command);
}

static void _DBusClient(DBus* this, char* hostname, char* port, char* file) {
    Client client;
    clientCreate(&client, hostname, port);
    FileReader reader;
    fileReaderCreate(&reader, file);
    clientConnect(&client);
    uint32_t messageID = 1;

    while (!fileReaderDoneReading(&reader)) {
        _DBusNextCommand(&client, &reader, messageID);
        messageID++;
    }

    clientDestroy(&client);
    fileReaderDestroy(&reader);
}

static void _DBusServer(DBus* this, char* port) {
    Server server;
    serverCreate(&server, port);
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

int DBusRun(DBus* this, int argc, char* argv[]) {
    const char* mode = *argv + (strlen(*argv) - 6);
    if (!strcmp(mode, "client")) {
        if (argc == 3) _DBusClient(this, argv[1], argv[2], NULL);
        else if (argc == 4) _DBusClient(this, argv[1], argv[2], argv[3]);
        else return ERROR;
    } else if (!strcmp(mode, "server"))  {
        if (argc != 2) return ERROR;
        _DBusServer(this, argv[1]);
    }
    return OK;
}

void DBusDestroy(DBus* this) {
    //do nothing
}
