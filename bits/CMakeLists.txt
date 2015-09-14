project(bits)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

#file(GLOB gtest_include C:/gtest-1.6.0/include/gtest/*.h C:/gtest-1.6.0/include/gtest/internal/*.h)
#set(gtest_libs C:/gtest-1.6.0/make/gtest_main.o C:/gtest-1.6.0/make/gtest-all.o)

#include_directories(${gtest_include})
#target_link_libraries(${PROJECT_NAME} ${gtest_libs})


