//
// Created by marcos on 23/4/20.
//

#ifndef TP1DBUS_FILEREADER_H
#define TP1DBUS_FILEREADER_H

#include <stdio.h>

struct FileReader {
    FILE* inputFile;
    char* command;
} typedef FileReader;

void fileReaderInitialize(FileReader* this, FILE* file);

char* fileReaderReadFile(FileReader* this);

#endif //TP1DBUS_FILEREADER_H
