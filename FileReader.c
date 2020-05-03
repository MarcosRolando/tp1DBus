//
// Created by marcos on 23/4/20.
//

#include "FileReader.h"
#include <string.h>
#include <stdlib.h>
#include "stringExtra.h"

void fileReaderCreate(FileReader* this, FILE* file) {
    this->inputFile = file;
    this->command = NULL;
}

//retorna el primer comando del archivo
char* fileReaderReadFile(FileReader* this) {
    char buffer[33];
    if (!feof(this->inputFile)) {
        memset(buffer, 0, 33);
        do {
            if (fgets(buffer, 33, this->inputFile)) {
                concatenateStrings(&(this->command), buffer);
            }
        } while (strchr(buffer, '\n') == NULL);
    }
    return this->command;
}

bool fileReaderDoneReading(FileReader* this) {
    return feof(this->inputFile);
}

void fileReaderDestroy(FileReader* this) {
    free(this->command);
}
