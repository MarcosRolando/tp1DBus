cmake_minimum_required(VERSION 3.15)
project(tp1DBus)

add_executable(tp1DBus main.c ClientCommand.c FileReader.c
        stringExtra.c stringExtra.h Client.c Client.h Socket.c Socket.h
        ErrorVerifier.c ErrorVerifier.h Messenger.c Messenger.h)

add_executable(server Server.c Server.h Socket.c Socket.h
        ErrorVerifier.c ErrorVerifier.h Messenger.c Messenger.h serverMain.c
        CommandReceiver.c CommandReceiver.h CommandPrinter.c CommandPrinter.h)

target_compile_options (tp1DBus PRIVATE -std=c99 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(tp1DBus PRIVATE -lm)

target_compile_options (server PRIVATE -std=c99 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(server PRIVATE -lm)
