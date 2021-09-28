cmake_minimum_required(VERSION 3.2)

link_directories(./)
file (GLOB SRC ".c")

add_executable(${PROJECT_NAME} client.c clientErro.c)