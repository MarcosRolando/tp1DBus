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
#define ARRAY_BASE_LENGTH 32 //tamanio minilo del Array of Struct, no se cuenta el padding de la firma

static void _deleteParametersSeparator(ClientCommand* this) {
    for (int i = 0; i < this->paraLength + 1; ++i) { //quiero contar el \0 xq es otro parametro mas
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
    if (methLength % 8 && this->parameters != 0) methLength += (8 - methLength % 8); //el parameters es para no contar el padding si no hay parametros
    this->commandLength = destLength + pathLength + interLength + methLength;
    if (this->parameters != 0) this->commandLength += this->parameterAmount + 1; //el +1 es del \0 de los parametros
}

static uint32_t _calculateHeaderLength(ClientCommand* this) {
    _calculateCommandLength(this);
    uint32_t bufferLength = HEADER_BASE_LENGTH + this->commandLength;
    if (this->parameterAmount != 0) bufferLength += FIRM_BASE_LENGTH;
    if (bufferLength % 8) bufferLength += (8 - bufferLength % 8); //el buffer debe ser multiplo de 8
    return bufferLength;
}

static void _loadHeaderSettings(ClientCommand* this, char* header,
                                                    uint32_t* bytesWritten) {
    char endiannes = 'l', messageType = 0x01, flag = 0x00, pVersion = 0x01;
    uint32_t bodyLength = 0;
    if (this->parameterAmount != 0) bodyLength = htole32(this->paraLength +
                                                    4*this->parameterAmount + 1); //+1 del /0 final
    this->messageID = htole32(this->messageID);
    *bytesWritten = snprintf(header, 5, "%c%c%c%c",
                                        endiannes, messageType, flag, pVersion);
    memcpy(header + *bytesWritten, &bodyLength, sizeof(uint32_t));
    *bytesWritten += sizeof(uint32_t);
    memcpy(header + *bytesWritten, &this->messageID, sizeof(uint32_t));
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

static void _loadFirm(char* header, uint32_t * bytesWritten, char id,
                            char amount, char* dataType, char parameterAmount) {
    *bytesWritten += snprintf(header + *bytesWritten, 3, "%c%c",
                                                                    id, amount);
    memcpy(header + *bytesWritten, dataType, sizeof(char)*2);
    *bytesWritten += sizeof(char)*2;
    *bytesWritten += snprintf(header + *bytesWritten, 2, "%c", parameterAmount);
    for (int i = 0; i < parameterAmount; ++i) {
        *bytesWritten += snprintf(header + *bytesWritten, 2, "s");
    }
}

static void _loadHeaderArray(ClientCommand* this, char* header,
                                                    uint32_t* bytesWritten) {
    uint32_t arrayLength = ARRAY_BASE_LENGTH + this->commandLength;
    if (this->parameterAmount != 0) arrayLength += FIRM_BASE_LENGTH;
    arrayLength = htole32(arrayLength);
    memcpy(header + *bytesWritten, &arrayLength, sizeof(uint32_t));
    *bytesWritten += sizeof(uint32_t);
    _loadCommand(this->path, this->pathLength, header, bytesWritten, 1,
                                                1, "o"); //path
    _loadCommand(this->destiny, this->dLength, header, bytesWritten, 6,
                                            1, "s"); //destiny
    _loadCommand(this->interface, this->iLength, header, bytesWritten, 2,
                                            1, "s"); //interface
    _loadCommand(this->method, this->mLength, header, bytesWritten, 3,
                                                1, "s"); //method
    if (this->parameterAmount != 0) _loadFirm(header, bytesWritten, 8,
                                1, "g", this->parameterAmount);
}

uint32_t clientCommandGetHeader(ClientCommand* this, char** header) {
    uint32_t headerLength = _calculateHeaderLength(this);
    uint32_t bytesWritten = 0;
    *header = malloc(headerLength * sizeof(char));
    memset(*header, 0, headerLength * sizeof(char));
    _loadHeaderSettings(this, *header, &bytesWritten); //cargo la parte que no es el array of struct, es decir, primeros 4 bytes y 2 uints
    _loadHeaderArray(this, *header, &bytesWritten);
    this->header = *header;
    return headerLength;
}

static void _loadParameter(ClientCommand* this, char* body, uint32_t* bytesWritten) {
    uint32_t length = strlen(this->parameters);
    length = htole32(length);
    memcpy(body + *bytesWritten, &length, sizeof(uint32_t));
    *bytesWritten += sizeof(uint32_t);
    *bytesWritten += snprintf(body + *bytesWritten, length + 1,
                                "%s", this->parameters) + 1; //sumo 1 extra por el \0
    this->parameters += length + 1;
}

uint32_t clientCommandGetBody(ClientCommand* this, char** body) {
    if (this->parameterAmount != 0) {
        uint32_t bodyLength = (this->parameterAmount * sizeof(uint32_t))
                              + this->paraLength + 1; //+1 por el \0
        *body = malloc(bodyLength*sizeof(char));
        uint32_t bytesWritten = 0;
        char* parametersBackUp = this->parameters; //asi no pierdo el puntero a los parametros para poder liberar la memoria
        for (int i = 0; i < this->parameterAmount; ++i) {
            _loadParameter(this, *body, &bytesWritten);
        }
        this->parameters = parametersBackUp;
        this->body = *body;
        return bodyLength;
    }
    return 0;
}

void clientCommandCreate(ClientCommand* this, uint32_t messageID) {
    this->destiny = NULL;
    this->path = NULL;
    this->interface = NULL;
    this->method = NULL;
    this->parameters = NULL;
    this->header = NULL;
    this->body = NULL;
    this->messageID = messageID;
    this->parameterAmount = 0;
    this->commandLength = 0;
}

void clientCommandDestroy(ClientCommand* this) {
    free(this->destiny);
    free(this->path);
    free(this->interface);
    free(this->method);
    free(this->parameters);
    free(this->header);
    free(this->body);
}

void _storeLength(ClientCommand* this) {
    this->dLength = strlen(this->destiny);
    this->pathLength = strlen(this->path);
    this->iLength = strlen(this->interface);
    this->mLength = strlen(this->method);
    if (this->parameters != NULL) this->paraLength = strlen(this->parameters);
    else this->paraLength = 0;
}

void clientCommandReadCommand(ClientCommand* this, char* input) {
    concatenateStrings(&(this->destiny), strtok(input, " "));
    concatenateStrings(&(this->path), strtok(NULL, " "));
    concatenateStrings(&(this->interface), strtok(NULL, " "));
    concatenateStrings(&(this->method), strtok(NULL, "("));
    concatenateStrings(&(this->parameters), strtok(NULL, ")\n"));
    _storeLength(this);
    if (this->paraLength != 0) _deleteParametersSeparator(this);
}
