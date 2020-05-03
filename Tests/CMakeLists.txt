cmake_minimum_required(VERSION 3.15)
project(tp1DBus)

add_executable(tests tests.cpp)

target_link_options(tests PRIVATE -pthread)
