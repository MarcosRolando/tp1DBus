//
// Created by marcos on 23/4/20.
//

#ifndef TP1DBUS_CLIENTCOMMAND_H
#define TP1DBUS_CLIENTCOMMAND_H

typedef struct ClientCommand {
    char *destiny, *path, *interface, *method, *parameters;
    int dLenght, pathLenght, iLenght, mLenght, paraLenght; //no cuentan el \0
} ClientCommand;

void clientCommandCreate(ClientCommand* this);

void clientCommandSetMessage(ClientCommand* this);

void clientCommandDestroy(ClientCommand* this);

void clientCommandLoadCommand(ClientCommand* this, char* input);


#endif //TP1DBUS_CLIENTCOMMAND_H
