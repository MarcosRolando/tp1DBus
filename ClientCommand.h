//
// Created by marcos on 23/4/20.
//

#ifndef TP1DBUS_CLIENTCOMMAND_H
#define TP1DBUS_CLIENTCOMMAND_H

#include <stdint.h>

typedef struct ClientCommand {
    char *destiny, *path, *interface, *method, *parameters;
    uint32_t dLength, pathLength, iLength, mLength, paraLength; //no cuentan el \0
    uint32_t parameterAmount;
    uint32_t commandLenght; //esto solo cuenta el largo de los comandos (\0 incluido)
                        // sin tener en cuenta el padding de los parametros por cada s
} ClientCommand;

void clientCommandCreate(ClientCommand* this);

void clientCommandSetMessage(ClientCommand* this, uint32_t messageID);

void clientCommandDestroy(ClientCommand* this);

void clientCommandLoadCommand(ClientCommand* this, char* input);


#endif //TP1DBUS_CLIENTCOMMAND_H
