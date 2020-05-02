//
// Created by marcos on 2/5/20.
//

#include "CommandPrinter.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void commandPrinterCreate(CommandPrinter* this) {
    this->path = NULL;
    this->destiny = NULL;
    this->interface = NULL;
    this->method = NULL;
    this->parameters = NULL;
    this->parametersStored = 0;
}

void commandPrinterSetID(CommandPrinter* this, uint32_t messageID) {
    this->messageID = messageID;
}

static void _set(char** string, char* buffer, uint32_t length) {
    *string = malloc(sizeof(char)*length);
    memset(*string, 0, length);
    snprintf(*string, length, "%s", buffer);
}

void commandPrinterSetHeaderData(CommandPrinter* this, char* buffer, uint32_t length, char type) {
    if (type == 0x01) _set(&this->path, buffer, length);
    else if (type == 0x06) _set(&this->destiny, buffer, length);
    else if (type == 0x02) _set(&this->interface, buffer, length);
    else if (type == 0x03) _set(&this->method, buffer, length);
}

void commandPrinterSetBodyData(CommandPrinter* this, char* buffer, uint32_t length) {
    char** parameter = this->parameters + this->parametersStored;
    _set(parameter, buffer, length);
    this->parametersStored++;
}

void commandPrinterSetParameterAmount(CommandPrinter* this, char amount) {
    this->parameters = malloc(sizeof(char*)*amount);
}

void commandPrinterDestroy(CommandPrinter* this) {
    free(this->path);
    free(this->destiny);
    free(this->interface);
    free(this->method);
    free(this->parameters);
}
