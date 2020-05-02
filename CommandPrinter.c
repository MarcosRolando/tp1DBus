//
// Created by marcos on 2/5/20.
//

#include "CommandPrinter.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void commandPrinterCreate(CommandPrinter* this) {
    //do nothing
}

void commandPrinterSetID(CommandPrinter* this, uint32_t messageID) {
    this->messageID = messageID;


}

static void _set(char** string, char* buffer, uint32_t length) {
    *string = malloc(sizeof(char)*length);
    memset(*string, 0, length);
    snprintf(*string, length, "%s", buffer);
}

void commandPrinterSetData(CommandPrinter* this, char* buffer, uint32_t length, char type) {
    if (type == 0x01) _set(&this->path, buffer, length);
    else if (type == 0x06) _set(&this->destiny, buffer, length);
    else if (type == 0x02) _set(&this->interface, buffer, length);
    else if (type == 0x03) _set(&this->method, buffer, length);
}

void commandPrinterDestroy(CommandPrinter* this) {
    //do nothing
}
