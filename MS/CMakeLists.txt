cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME MS)
project(${PROJECT_NAME})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++0x -pthread")

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

