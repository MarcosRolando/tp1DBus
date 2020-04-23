//
// Created by marcos on 23/4/20.
//

#include "ClientCommand.h"
#include <string.h>
#include <stdlib.h>

#define LOADING_COMPLETE 1

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

void clientCommandCreate(ClientCommand* this) {
    this->destiny = NULL;
    this->path = NULL;
    this->interface = NULL;
    this->method = NULL;
    this->parameters = NULL;
}

void clientCommandDestroy(ClientCommand* this) {
    free(this->destiny);
    free(this->path);
    free(this->interface);
    free(this->method);
    free(this->parameters);
}

int clientCommandLoadCommand(ClientCommand* this, char* input) {
    _storeText(&(this->destiny), strtok(input, " "));
    _storeText(&(this->path), strtok(NULL, " "));
    _storeText(&(this->interface), strtok(NULL, " "));
    _storeText(&(this->method), strtok(NULL, "("));
    _storeText(&(this->parameters), strtok(NULL, ")"));
    return LOADING_COMPLETE;
}
