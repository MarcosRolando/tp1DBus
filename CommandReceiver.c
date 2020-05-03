//
// Created by marcos on 2/5/20.
//

#define _DEFAULT_SOURCE

#include "CommandReceiver.h"
#include <stdlib.h>
#include <string.h>

void commandReceiverCreate(CommandReceiver* this) {
    commandPrinterCreate(&this->cPrinter);
    this->readBody = false;
    this->readHeader = false;
    this->readPreHeader = false;
    this->parameterAmount = 0;
    memset(this->preHeader, 0, 16);
}

static void _processPreHeader(CommandReceiver* this, char* command) {
    uint32_t bytesRead = 4; //me salteo los 4 primeros xq no me sirven
    this->bodyLength = *((uint32_t*) (command + bytesRead));
    bytesRead += sizeof(uint32_t);
    this->bodyLength = le32toh(this->bodyLength);
    uint32_t messageID = *((uint32_t*) (command + bytesRead));
    bytesRead += 4;
    commandPrinterSetID(&this->cPrinter, le32toh(messageID));
    this->headerLength = *((uint32_t*) (command + bytesRead));
    if (this->headerLength % 8) this->headerLength += (8-this->headerLength%8);
    this->headerLength = le32toh(this->headerLength); //cuento el padding
}

static uint32_t _processMainHeaderData(CommandReceiver* this, char* command,
                                                                    char type) {
    uint32_t bytesRead = 4;
    uint32_t length = *((uint32_t*) (command + bytesRead));
    length = le32toh(length) + 1; //+1 xq no toma en cuenta el /0 lo que leo
    bytesRead += 4;
    commandPrinterSetHeaderData(&this->cPrinter, command + bytesRead,
                                                                length, type);
    if (length % 8) length += 8 - length % 8;
    bytesRead += length;
    return bytesRead;
}

static uint32_t _processOptionalHeaderData(CommandReceiver* this,
                                                                char* command) {
    uint32_t bytesRead = 4; //los primeros 4 me dan igual
    this->parameterAmount = *(command + bytesRead);
    bytesRead += 1 + this->parameterAmount + 1;
    if (bytesRead % 8) bytesRead += 8 - bytesRead % 8;
    return bytesRead;
}

static uint32_t _processHeaderData(CommandReceiver* this, char* command) {
    char type = *command; //leo que parte del comando es path, dest, etc
    if (type != 0x08) return _processMainHeaderData(this, command, type);
    else
        return _processOptionalHeaderData(this, command); //la firma
}

static void _processHeader(CommandReceiver* this, char* command) {
    uint32_t bytesRead = 0;
    while (bytesRead < this->headerLength) {
        bytesRead += _processHeaderData(this, command + bytesRead);
    }
}

static uint32_t _processBodyData(CommandReceiver* this, char* command) {
    uint32_t length = *((uint32_t*) command) + 1; //+1 por el /0
    length = le32toh(length);
    uint32_t bytesRead = 4;
    commandPrinterSetBodyData(&this->cPrinter, command + bytesRead, length);
    bytesRead += length;
    return bytesRead;
}

static void _processBody(CommandReceiver* this, char* command) {
    uint32_t bytesRead = 0;
    commandPrinterSetParameterAmount(&this->cPrinter, this->parameterAmount);
    while (bytesRead < this->bodyLength) {
        bytesRead += _processBodyData(this, command + bytesRead);
    }
}

void commandReceiverProcess(CommandReceiver* this, char* command) {
    if (!this->readPreHeader) {
        _processPreHeader(this, command);
        this->readPreHeader = true;
    } else if (!this->readHeader) {
        _processHeader(this, command);
        this->readHeader = true;
        free(command);
    } else if (!this->readBody) {
        _processBody(this, command);
        this->readBody = true;
        free(command);
    }
}

void commandReceiverPrint(CommandReceiver* this) {
    commandPrinterPrint(&this->cPrinter);
}

size_t commandReceiverGetBuffer(CommandReceiver* this, char** buffer) {
    if (!this->readPreHeader) {
        *buffer = this->preHeader;
        return 16;
    } else if (!this->readHeader) {
        *buffer = malloc(sizeof(char)*this->headerLength);
        memset(*buffer, 0, this->headerLength);
        return this->headerLength;
    } else if (!this->readBody) {
        *buffer = malloc(sizeof(char)*this->bodyLength);
        memset(*buffer, 0, this->bodyLength);
        return this->bodyLength;
    }
    return 0;
}

bool commandReceiverFinished(CommandReceiver* this) {
    return (this->readPreHeader && this->readHeader && this->readBody);
}

void commandReceiverDestroy(CommandReceiver* this) {
    commandPrinterDestroy(&this->cPrinter);
}
