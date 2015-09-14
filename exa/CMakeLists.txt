# --------------
# CMake file for party
# Author: Zhihong (John) Zeng
# ChangLog:  12/2012: initialization

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(subProject party)

PROJECT(${subProject})

file(GLOB SRCS *.c*)
file(GLOB HDRS *.h*)

add_executable(${subProject} ${SRCS} ${HDRS})
