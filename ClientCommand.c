//
// Created by marcos on 23/4/20.
//

#define _DEFAULT_SOURCE // esto es para que no se queje el make, no es standar C99 PREGUNTAR

#include "ClientCommand.h"
#include <string.h>
#include <stdlib.h>
#include "stringExtra.h"
#include <stdio.h>

#define HEADER_BASE_LENGTH 48 //tamanio minimo del header en bytes sin firma
#define FIRM_BASE_LENGTH 4 //4 bytes que siempre se envian si tengo parametros en la firma del metodo
#define ARRAY_BASE_LENGTH 36 //tamanio minilo del Array of Struct, no se cuenta el padding de la firma

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
    if (destLength % 8) destLength +=  (8 - destLength % 8); //cuento el padding
    uint32_t pathLength = this->pathLength + 1;//cuento el \0
    if (pathLength % 8) pathLength += (8 - pathLength % 8);
    uint32_t interLength = this->iLength + 1;//cuento el \0
    if (interLength % 8) interLength += (8 - interLength % 8);
    uint32_t methLength = this->mLength + 1;//cuento el \0
    if (methLength % 8) methLength += (8 - methLength % 8);
    this->commandLenght = destLength + pathLength + interLength + methLength;
    if (this->parameters != 0) this->commandLenght += this->parameterAmount + 1; //el +1 es del \0 de los parametros
}

static uint32_t _calculateHeaderLength(ClientCommand* this) {
    _calculateCommandLength(this);
    uint32_t bufferLength = HEADER_BASE_LENGTH + this->commandLenght;
    if (this->parameterAmount != 0) bufferLength += FIRM_BASE_LENGTH;
    if (bufferLength % 8) bufferLength += (8 - bufferLength % 8); //el buffer debe ser multiplo de 8
    return bufferLength;
}

static void _loadHeaderSettings(ClientCommand* this, char* header,
                                uint32_t messageID, uint32_t* bytesWritten) {
    char endiannes = 'l', messageType = 0x01, flag = 0x00, pVersion = 0x01;
    uint32_t bodyLength = htole32(this->paraLength + 5); //4 bytes indicando la longitud + el byte del \0
    messageID = htole32(messageID);
    *bytesWritten = snprintf(header, 5, "%c%c%c%c",
                                        endiannes, messageType, flag, pVersion);
    memcpy(header + *bytesWritten, &bodyLength, sizeof(uint32_t));
    *bytesWritten += sizeof(uint32_t);
    memcpy(header + *bytesWritten, &messageID, sizeof(uint32_t));
    *bytesWritten += sizeof(uint32_t);
}

static void _loadCommand(char* text, uint32_t length, char* header,
                uint32_t* bytesWritten, char id, char amount, char* dataType) {
    *bytesWritten += snprintf(header + *bytesWritten, 3, "%c%c",
                                                                    id, amount);
    memcpy(header + *bytesWritten, dataType, sizeof(char)*2);
    *bytesWritten += sizeof(char)*2;
    length = htole32(length);
    memcpy(header + *bytesWritten, &length, sizeof(uint32_t));
    *bytesWritten += sizeof(uint32_t);
    uint32_t textLength = strlen(text) + 1;
    memcpy(header + *bytesWritten, text, sizeof(char)*textLength);
    if (textLength % 8) textLength += (8 - textLength % 8);
    *bytesWritten += textLength*sizeof(char); //cuento el padding que tengo que dejar
}

static void _loadFirm(char* header, uint32_t * bytesWritten, char id, char amount, char* dataType) {
    *bytesWritten += snprintf(header + *bytesWritten, 3, "%c%c",
                              id, amount);
    memcpy(header + *bytesWritten, dataType, sizeof(char)*2);
    *bytesWritten += sizeof(char)*2;
}

static void _loadHeaderArray(ClientCommand* this, char* header,
                                                    uint32_t* bytesWritten) {
    uint32_t arrayLength = ARRAY_BASE_LENGTH + this->commandLenght;
    arrayLength = htole32(arrayLength);
    memcpy(header + *bytesWritten, &arrayLength, sizeof(uint32_t));
    *bytesWritten += sizeof(uint32_t);
    _loadCommand(this->path, this->pathLength, header, bytesWritten, 1, 1, "o"); //path
    _loadCommand(this->destiny, this->dLength, header, bytesWritten, 6, 1, "s"); //destiny
    _loadCommand(this->interface, this->iLength, header, bytesWritten, 2, 1, "s"); //interface
    _loadCommand(this->method, this->mLength, header, bytesWritten, 3, 1, "s"); //method
    if (this->parameterAmount != 0) _loadFirm();
}

//todo: tengo que avanzar esta funcion para escribir el protocolo
//por ahora me limito a armar el header
void clientCommandSetMessage(ClientCommand* this, uint32_t messageID) {
    uint32_t headerLength = _calculateHeaderLength(this);
    uint32_t bytesWritten = 0;
    char* header = malloc(headerLength * sizeof(char));
    memset(header, 0, headerLength * sizeof(char));
    _loadHeaderSettings(this, header, messageID, &bytesWritten); //cargo la parte que no es el array of struct, es decir, primeros 4 bytes y 2 uints
    _loadHeaderArray(this, header, &bytesWritten);
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

void clientCommandReadCommand(ClientCommand* this, char* input) {
    concatenateStrings(&(this->destiny), strtok(input, " "));
    concatenateStrings(&(this->path), strtok(NULL, " "));
    concatenateStrings(&(this->interface), strtok(NULL, " "));
    concatenateStrings(&(this->method), strtok(NULL, "("));
    concatenateStrings(&(this->parameters), strtok(NULL, ")"));
    _deleteParametersSeparator(this);
    _storeLength(this);
}
