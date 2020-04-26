cmake_minimum_required(VERSION 3.15)
project(tp1DBus)

set(CMAKE_C_STANDARD 99)

add_executable(tp1DBus main.c ClientCommand.c FileReader.c
        stringExtra.c stringExtra.h Client.c Client.h Socket.c Socket.h
        ErrorVerifier.c ErrorVerifier.h Messenger.c Messenger.h)

add_executable(server Server.c Server.h Socket.c Socket.h
        ErrorVerifier.c ErrorVerifier.h Messenger.c Messenger.h serverMain.c)

target_compile_options (tp1DBus PRIVATE -Wall -Werror -pedantic -pedantic-errors
        -O3 -ggdb -DDEBUG -fno-inline)

target_link_options(tp1DBus PRIVATE -lm)

target_compile_options (server PRIVATE -Wall -Werror -pedantic -pedantic-errors
        -O3 -ggdb -DDEBUG -fno-inline)

target_link_options(server PRIVATE -lm)
