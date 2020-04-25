#include <stdio.h>
#include "ClientCommand.h"
#include "FileReader.h"
#include "Client.h"

int main() {

    ClientCommand command;
    clientCommandCreate(&command);
    FileReader reader;
    fileReaderCreate(&reader, stdin);

    char* cmd = fileReaderReadFile(&reader);
    clientCommandLoadCommand(&command, cmd);

    clientCommandDestroy(&command);
    fileReaderDestroy(&reader);

    test();

    return 0;
}
