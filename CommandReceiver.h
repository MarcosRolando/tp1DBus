//
// Created by marcos on 2/5/20.
//

#ifndef TP1DBUS_COMMANDRECEIVER_H
#define TP1DBUS_COMMANDRECEIVER_H

#include <stdio.h>
#include "CommandPrinter.h"
#include <stdbool.h>

typedef struct CommandReceiver {
    CommandPrinter cPrinter;
    uint32_t bodyLength, headerLength;
    char parameterAmount;
    bool readPreHeader; //los 16 bytes antes de leer el header
    bool readHeader, readBody; //para chequear si ya los lei
} CommandReceiver;

void commandReceiverCreate(CommandReceiver* this);

void commandReceiverProcess(CommandReceiver* this, char* command);

size_t commandReceiverGetBuffer(CommandReceiver* this, char** buffer);

void commandReceiverDestroy(CommandReceiver* this);


#endif //TP1DBUS_COMMANDRECEIVER_H
