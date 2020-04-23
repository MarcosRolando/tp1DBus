//
// Created by marcos on 23/4/20.
//

#ifndef TP1DBUS_CLIENTCOMMAND_H
#define TP1DBUS_CLIENTCOMMAND_H

#include <stdbool.h>

struct ClientCommand {
    char *destiny, *path, *interface, *method, *parameters;
    bool readDestiny, readPath, readInterface, readMethod, readParameters;
    int amountRead;
    char* textToRead; //los tokens
} typedef ClientCommand;

void clientInitialize(ClientCommand* this);

void clientDestroy(ClientCommand* this);

int clientLoadCommand(ClientCommand* this, char* input);


#endif //TP1DBUS_CLIENTCOMMAND_H
