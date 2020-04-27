//
// Created by marcos on 23/4/20.
//

#include "ClientCommand.h"
#include <string.h>
#include <stdlib.h>
#include "stringExtra.h"

#define HEADER_BASE_LENGTH 48 //tamanio minimo del header en bytes

static void _deleteParametersSeparator(ClientCommand* this) {
    for (int i = 0; i < strlen(this->parameters); ++i) {
        if (this->parameters[i] == ',') this->parameters[i] = '\0';
    }
}

static int _calculateHeaderLength(ClientCommand* this) {
    int destLength = this->dLenght + 1;//cuento el \0
    destLength += destLength % 8;
    int pathLength = this->pathLenght + 1;//cuento el \0
    pathLength += pathLength % 8;
    int interLength = this->iLenght + 1;//cuento el \0
    interLength += interLength % 8;
    int methLength = this->paraLenght + 1;//cuento el \0
    methLength += methLength % 8;
    return (HEADER_BASE_LENGTH + destLength + pathLength + interLength
                                                                + methLength);
}

//por ahora me limito a armar la cabecera
void clientCommandSetMessage(ClientCommand* this) {
    _calculateHeaderLength(this);
}

void clientCommandCreate(ClientCommand* this) {
    this->destiny = NULL;
    this->path = NULL;
    this->interface = NULL;
    this->method = NULL;
    this->parameters = NULL;
}

void clientCommandDestroy(ClientCommand* this) {
    free(this->destiny);
    free(this->path);
    free(this->interface);
    free(this->method);
    free(this->parameters);
}

void _storeLength(ClientCommand* this) {
    this->dLenght = strlen(this->destiny);
    this->pathLenght = strlen(this->path);
    this->iLenght = strlen(this->interface);
    this->paraLenght = strlen(this->method);
}

void clientCommandLoadCommand(ClientCommand* this, char* input) {
    concatenateStrings(&(this->destiny), strtok(input, " "));
    concatenateStrings(&(this->path), strtok(NULL, " "));
    concatenateStrings(&(this->interface), strtok(NULL, " "));
    concatenateStrings(&(this->method), strtok(NULL, "("));
    concatenateStrings(&(this->parameters), strtok(NULL, ")"));
    _deleteParametersSeparator(this);
    _storeLength(this);
}
