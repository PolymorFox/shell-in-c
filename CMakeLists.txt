cmake_minimum_required(VERSION 3.10)

project(SHELL VERSION 1.0)

add_library(shell_backend shell.c)

add_executable(shell main.c)

target_link_libraries(shell PRIVATE shell_backend)
