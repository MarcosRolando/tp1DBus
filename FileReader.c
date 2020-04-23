//
// Created by marcos on 23/4/20.
//

#include "FileReader.h"
#include <string.h>
#include <stdlib.h>

static void _storeText(char** buffer, char* text) {
    size_t textSize = strlen(text) + 1;//+1 porque strlen no cuenta el \0
    if (*buffer == NULL) {
        *buffer = malloc((textSize)*sizeof(char));
        strncpy(*buffer, text, textSize);
    } else {
        size_t newBufferSize = textSize + strlen(*buffer);
        char* newBuffer = malloc((newBufferSize)*sizeof(char));
        memset(newBuffer, 0, newBufferSize);
        strncpy(newBuffer, *buffer, newBufferSize);
        strncat(newBuffer, text, newBufferSize);
        free(*buffer);
        *buffer = newBuffer;
    }
}

void fileReaderCreate(FileReader* this, FILE* file) {
    this->inputFile = file;
    this->command = NULL;
}

//retorna el primer comando del archivo
char* fileReaderReadFile(FileReader* this) {
    char buffer[32];
    if (!feof(this->inputFile)) {
        memset(buffer, 0, 32);
        do {
            if (fgets(buffer, 32, this->inputFile)) {
                _storeText(&(this->command), buffer);
            }
        } while (strchr(buffer, '\n') == NULL);
    }
    return this->command;
}

void fileReaderDestroy(FileReader* this) {
    free(this->command);
}