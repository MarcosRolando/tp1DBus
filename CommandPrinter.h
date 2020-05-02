//
// Created by marcos on 2/5/20.
//

#ifndef TP1DBUS_COMMANDPRINTER_H
#define TP1DBUS_COMMANDPRINTER_H

#include <stdint.h>

typedef struct CommandPrinter {
    uint32_t messageID;
    char* path, *destiny, *interface, *method, *parameters;
} CommandPrinter;

void commandPrinterCreate(CommandPrinter* this);

void commandPrinterSetID(CommandPrinter* this, uint32_t messageID);

void commandPrinterSetData(CommandPrinter* this, char* buffer, uint32_t length, char type);

void commandPrinterDestroy(CommandPrinter* this);

#endif //TP1DBUS_COMMANDPRINTER_H
