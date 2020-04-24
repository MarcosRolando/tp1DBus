//
// Created by marcos on 24/4/20.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//concatena text en buffer y hace que buffer apunte al nuevo char* dinamico
void concatenateStrings(char** buffer, char* text) {
    size_t textSize = strlen(text) + 1;//+1 porque strlen no cuenta el \0
    if (*buffer == NULL) {
        *buffer = malloc((textSize)*sizeof(char));
        strncpy(*buffer, text, textSize);
    } else {
        size_t newBufferSize = textSize + strlen(*buffer);
        char* newBuffer = malloc((newBufferSize)*sizeof(char));
        memset(newBuffer, 0, newBufferSize);
        snprintf(newBuffer, newBufferSize, "%s%s", *buffer, text);
        free(*buffer);
        *buffer = newBuffer;
    }
}
