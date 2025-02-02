//
// Created by marcos on 24/4/20.
//

#include <string.h>
#include <stdlib.h>

//concatena text en buffer y hace que buffer apunte al nuevo char* dinamico
void concatenateStrings(char** buffer, char* text) {
    size_t textSize = 0;
    if (text != NULL) textSize += strlen(text) + 1;
    if (textSize != 0) {
        if (*buffer == NULL) {
            *buffer = malloc((textSize)*sizeof(char));
            strncpy(*buffer, text, textSize);
        } else {
            size_t newBufferSize = textSize + strlen(*buffer);
            *buffer = realloc(*buffer, (newBufferSize)*sizeof(char));
            strncat(*buffer, text, textSize);
        }
    }
}
