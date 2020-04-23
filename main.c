#include <stdio.h>
#include "ClientCommand.h"
#include "FileReader.h"

int main() {

    ClientCommand command;
    clientInitialize(&command);
    FileReader reader;
    fileReaderInitialize(&reader, stdin);

    char* cmd = fileReaderReadFile(&reader);
    clientLoadCommand(&command, cmd);

    clientDestroy(&command);

    return 0;
}
