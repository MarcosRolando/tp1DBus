//
// Created by marcos on 23/4/20.
//

#include "ClientCommand.h"
#include <string.h>
#include <stdlib.h>
#include "stringExtra.h"
#include <stdio.h>

#define HEADER_BASE_LENGTH 52 //tamanio minimo del header en bytes

static void _deleteParametersSeparator(ClientCommand* this) {
    for (int i = 0; i < (strlen(this->parameters) + 1); ++i) { //quiero contar el \0 xq es otro parametro mas
        if (this->parameters[i] == ',') {
            this->parameters[i] = '\0';
        }
        if (this->parameters[i] == '\0') this->parameterAmount++;
    }
}

static void _calculateCommandLength(ClientCommand* this) {
    uint32_t destLength = this->dLength + 1;//cuento el \0
    destLength +=  (8 - destLength % 8); //cuento el padding
    uint32_t pathLength = this->pathLength + 1;//cuento el \0
    pathLength += (8 - pathLength % 8);
    uint32_t interLength = this->iLength + 1;//cuento el \0
    interLength += (8 - interLength % 8);
    uint32_t methLength = this->mLength + 1;//cuento el \0
    methLength += (8 - methLength % 8);
    this->commandLenght = destLength + pathLength + interLength + methLength +
                                                        this->parameterAmount; //esto seria el arrayLength en el PDF
}

static uint32_t _calculateHeaderLength(ClientCommand* this) {
    _calculateCommandLength(this);
    uint32_t bufferLength = HEADER_BASE_LENGTH + this->commandLenght;
    bufferLength += (8 - bufferLength % 8); //el buffer debe ser multiplo de 8
    return bufferLength;
}

static void _loadHeaderSettings(ClientCommand* this, char* header,
                                uint32_t messageID, uint32_t* bytesWritten) {
    char endiannes = 'l', messageType = 0x01, flag = 0x00, pVersion = 0x01;
    uint32_t bodyLength = htole32(this->paraLength + 5); //4 bytes indicando la longitud + el byte del \0
    messageID = htole32(messageID);
    *bytesWritten = snprintf(header, 4, "%c%c%c%c", //todo ACA NO SE SI VA 4 O 5 POR EL NULL CHARACTER, VER
                                        endiannes, messageType, flag, pVersion);
    memcpy(header + *bytesWritten, &bodyLength, sizeof(uint32_t));
    bytesWritten += sizeof(uint32_t);
    memcpy(header + *bytesWritten, &messageID, sizeof(uint32_t));
    *bytesWritten += sizeof(uint32_t);
}

static void _loadHeaderCommands(ClientCommand* this, char* header,
                                                    uint32_t* bytesWritten) {

}

//todo: tengo que avanzar esta funcion para escribir el protocolo
//por ahora me limito a armar el header
void clientCommandSetMessage(ClientCommand* this, uint32_t messageID) {
    uint32_t headerLength = _calculateHeaderLength(this);
    char* header = malloc(headerLength * sizeof(char));
    uint32_t bytesWritten = 0;
    _loadHeaderSettings(this, header, messageID, &bytesWritten); //cargo la parte que no es el array of struct, es decir, primeros 4 bytes y 2 uints
    _loadHeaderCommands(this, header, &bytesWritten);

    memcpy(header + bytesWritten, &this->headerLength , sizeof(uint32_t));
    free(header);
}

void clientCommandCreate(ClientCommand* this) {
    this->destiny = NULL;
    this->path = NULL;
    this->interface = NULL;
    this->method = NULL;
    this->parameters = NULL;
    this->parameterAmount = 0;
    this->commandLenght = 0;
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
