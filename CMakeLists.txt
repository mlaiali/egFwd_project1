cmake_minimum_required(VERSION 3.23)
project(egFwd_project1 C)

set(CMAKE_C_STANDARD 99)

add_executable(egFwd_project1 Card/card.c Card/card.h util/utiliti.h Terminal/terminal.c Terminal/terminal.h util/utiliti.c Server/server.c Server/server.h Application/application.c Application/application.h)
