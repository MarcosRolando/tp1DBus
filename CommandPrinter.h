//
// Created by marcos on 2/5/20.
//

#ifndef TP1DBUS_COMMANDPRINTER_H
#define TP1DBUS_COMMANDPRINTER_H

#include <stdint.h>

typedef struct CommandPrinter {
    uint32_t messageID;
    char* path, *destiny, *interface, *method, **parameters;
    char parametersStored;
} CommandPrinter;

void commandPrinterCreate(CommandPrinter* this);

void commandPrinterSetID(CommandPrinter* this, uint32_t messageID);

void commandPrinterSetHeaderData(CommandPrinter* this, char* buffer, uint32_t length, char type);

void commandPrinterSetBodyData(CommandPrinter* this, char* buffer, uint32_t length);

void commandPrinterSetParameterAmount(CommandPrinter* this, char amount);

void commandPrinterDestroy(CommandPrinter* this);

#endif //TP1DBUS_COMMANDPRINTER_H
