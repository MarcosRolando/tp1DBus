//
// Created by marcos on 23/4/20.
//

#include "ClientCommand.h"
#include <string.h>
#include <stdlib.h>
#include "stringExtra.h"
#include <stdio.h>

#define HEADER_BASE_LENGTH 48 //tamanio minimo del header en bytes

static void _deleteParametersSeparator(ClientCommand* this) {
    for (int i = 0; i < strlen(this->parameters); ++i) {
        if (this->parameters[i] == ',') this->parameters[i] = '\0';
    }
}

static uint32_t _calculateHeaderLength(ClientCommand* this) {
    uint32_t destLength = this->dLength + 1;//cuento el \0
    destLength +=  (8 - destLength % 8); //cuento el padding
    uint32_t pathLength = this->pathLength + 1;//cuento el \0
    pathLength += (8 - pathLength % 8);
    uint32_t interLength = this->iLength + 1;//cuento el \0
    interLength += (8 - interLength % 8);
    uint32_t methLength = this->mLength + 1;//cuento el \0
    methLength += (8 - methLength % 8);
    return (HEADER_BASE_LENGTH + destLength + pathLength + interLength
                                                                + methLength);
}

//todo: tengo que avanzar esta funcion para escribir el protocolo
//por ahora me limito a armar el header
void clientCommandSetMessage(ClientCommand* this, uint32_t messageID) {
    char messageType = 0x01, flag = 0x00, pVersion = 0x01;
    uint32_t headerLength = _calculateHeaderLength(this);
    uint32_t bodyLength = htole32(this->paraLength); //no se cuenta el \0
    headerLength = htole32(headerLength);
    messageID = htole32(messageID);
    char* header = malloc(headerLength*sizeof(char));
    uint32_t bytesWritten;
    bytesWritten = snprintf(header, headerLength, "l%c%c%c", messageType,
                                                                flag, pVersion);
    memcpy(header + bytesWritten, &bodyLength, sizeof(uint32_t));
    bytesWritten += sizeof(uint32_t);
    memcpy(header + bytesWritten, &messageID, sizeof(uint32_t));
    bytesWritten += sizeof(uint32_t);
    memcpy(header + bytesWritten, &headerLength, sizeof(uint32_t));
    free(header);
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
    this->dLength = strlen(this->destiny);
    this->pathLength = strlen(this->path);
    this->iLength = strlen(this->interface);
    this->mLength = strlen(this->method);
    this->paraLength = strlen(this->parameters);
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
