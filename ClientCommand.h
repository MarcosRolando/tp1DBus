//
// Created by marcos on 23/4/20.
//

#ifndef TP1DBUS_CLIENTCOMMAND_H
#define TP1DBUS_CLIENTCOMMAND_H

#include <stdint.h>

typedef struct ClientCommand {
    char *destiny, *path, *interface, *method, *parameters;
    uint32_t dLength, pathLength, iLength, mLength, paraLength; //no cuentan el \0
} ClientCommand;

void clientCommandCreate(ClientCommand* this);

void clientCommandSetMessage(ClientCommand* this);

void clientCommandDestroy(ClientCommand* this);

void clientCommandLoadCommand(ClientCommand* this, char* input);


#endif //TP1DBUS_CLIENTCOMMAND_H
