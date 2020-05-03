cmake_minimum_required(VERSION 3.15)
project(tp1DBus)

set(SOURCES main.c ClientCommand.c ClientCommand.h FileReader.c FileReader.h
        stringExtra.c stringExtra.h Client.c Client.h Socket.c Socket.h
        ErrorVerifier.c ErrorVerifier.h Messenger.c Messenger.h DBus.c DBus.h
        Server.c Server.h CommandReceiver.c CommandReceiver.h CommandPrinter.c
        CommandPrinter.h)

add_executable(client ${SOURCES})

add_executable(server ${SOURCES})

target_compile_options (client PRIVATE -std=c99 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(client PRIVATE -lm)

target_compile_options (server PRIVATE -std=c99 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(server PRIVATE -lm)
