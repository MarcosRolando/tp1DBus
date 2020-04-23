cmake_minimum_required(VERSION 3.15)
project(tp1DBus)

set(CMAKE_C_STANDARD 99)

add_executable(tp1DBus main.c ClientCommand.c FileReader.c)

target_compile_options (tp1DBus PRIVATE -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline)

target_link_options(tp1DBus PRIVATE -lm)
