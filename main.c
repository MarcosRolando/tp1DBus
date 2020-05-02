#include <stdio.h>
#include "ClientCommand.h"
#include "FileReader.h"
#include "Client.h"

int main() {

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

    return 0;
}
