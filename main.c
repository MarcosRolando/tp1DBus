#include <stdio.h>
#include "ClientCommand.h"
#include <string.h>

int main() {

    char buffer[32];
    ClientCommand command;
    clientInitialize(&command);

    while (!feof(stdin)) {
        memset(buffer, 0, 32);
        while (fgets(buffer, 32, stdin)) {
            clientLoadCommand(&command, buffer);
        }
    }

    clientDestroy(&command);

    return 0;
}
