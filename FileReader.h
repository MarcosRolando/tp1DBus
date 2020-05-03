//
// Created by marcos on 23/4/20.
//

#ifndef TP1DBUS_FILEREADER_H
#define TP1DBUS_FILEREADER_H

#include <stdio.h>
#include <stdbool.h>

typedef struct FileReader {
    FILE* inputFile;
    char* command;
} FileReader;

void fileReaderCreate(FileReader* this, char* file);

bool fileReaderDoneReading(FileReader* this);

void fileReaderDestroy(FileReader* this);

char* fileReaderReadFile(FileReader* this);

#endif //TP1DBUS_FILEREADER_H
