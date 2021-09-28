cmake_minimum_required(VERSION 3.2)

project(server)

link_directories(./)

add_executable(${PROJECT_NAME} server.c serverErro.c)
