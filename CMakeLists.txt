cmake_minimum_required(VERSION 3.5)

project(p1)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} p1.cpp p2.cpp)
