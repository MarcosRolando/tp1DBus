//
// Created by marcos on 23/4/20.
//

#include "ClientCommand.h"
#include <string.h>
#include <stdlib.h>

#define INCOMPLETE 0
#define LOADING_COMPLETE 1

void _storeText(char** buffer, char* text) {
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

int _countCompleteInputs(ClientCommand* this, char* input) {
    int length = (int)strlen(input);
    for (int i = 0; i < length; i++) {
        if (input[i] == ' ' || input[i] == '(' || input[i] == ')') {
            this->amountRead++;
        }
    }
    return this->amountRead;
}

bool _loadDestiny(ClientCommand* this) {
    if (!this->readDestiny) {
        _storeText(&(this->destiny), this->textToRead);
        this->readDestiny = (this->amountRead > 0);
        this->textToRead = strtok(NULL, " ");
    }
    return this->readDestiny;
}

bool _loadPath(ClientCommand* this) {
    if (this->amountRead > 0 && !(this->readPath)) {
        _storeText(&(this->path), this->textToRead);
        this->readPath = (this->amountRead > 1);
        this->textToRead = strtok(NULL, " ");
    }
    return this->readPath;
}

bool _loadInterface(ClientCommand* this) {
    if (this->amountRead > 1 && !(this->readInterface)) {
        _storeText(&(this->interface), this->textToRead);
        this->readInterface = (this->amountRead > 2);
        this->textToRead = strtok(NULL, "(");
    }
    return this->readInterface;
}

//TENGO BUG EN EL CASO BORDE DONDE TERMINE DE LEER PERO ME ENTERO DESPUES TODO
bool _loadMethod(ClientCommand* this) {
    if (this->amountRead > 2 && !(this->readMethod)) {
        _storeText(&(this->method), this->textToRead);
        this->readMethod = (this->amountRead > 3);
        this->textToRead = strtok(NULL, ")");
    }
    return this->readMethod;
}

bool _loadParameters(ClientCommand* this) {
    if (this->amountRead > 3 && !(this->readParameters)) {
        _storeText(&(this->parameters), this->textToRead);
        this->readParameters = (this->amountRead > 4);
    }
    return this->readParameters;
}

void clientInitialize(ClientCommand* this) {
    this->destiny = NULL;
    this->path = NULL;
    this->interface = NULL;
    this->method = NULL;
    this->parameters = NULL;
    this->readDestiny = false;
    this->readPath = false;
    this->readInterface = false;
    this->readMethod = false;
    this->readParameters = false;
    this->textToRead = NULL;
    this->amountRead = 0;
}

void clientDestroy(ClientCommand* this) {
    free(this->destiny);
    free(this->path);
    free(this->interface);
    free(this->method);
    free(this->parameters);
}

int clientLoadCommand(ClientCommand* this, char* input) {
    _countCompleteInputs(this, input);
    this->textToRead = strtok(input, " ()");
    if (!_loadDestiny(this)) return INCOMPLETE;
    if (!_loadPath(this)) return INCOMPLETE;
    if (!_loadInterface(this)) return INCOMPLETE;
    if (!_loadMethod(this)) return INCOMPLETE;
    if (!_loadParameters(this)) return INCOMPLETE;
    return LOADING_COMPLETE;
}
