cmake_minimum_required(VERSION 3.5)

project(p2)

include_directories(${PROJECT_SOURCE_DIR})

FILE(GLOB path ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${path})
