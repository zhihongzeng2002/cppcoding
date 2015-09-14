project(elements)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")

file(GLOB SRCS *.c*)
file(GLOB HDRS *.h*)

#aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

