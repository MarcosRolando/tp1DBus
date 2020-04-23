//
// Created by marcos on 23/4/20.
//

#ifndef TP1DBUS_CLIENTCOMMAND_H
#define TP1DBUS_CLIENTCOMMAND_H

#include <stdbool.h>

struct ClientCommand {
    char *destiny, *path, *interface, *method, *parameters;
} typedef ClientCommand;

void clientCommandCreate(ClientCommand* this);

void clientCommandDestroy(ClientCommand* this);

int clientCommandLoadCommand(ClientCommand* this, char* input);


#endif //TP1DBUS_CLIENTCOMMAND_H
