cmake_minimum_required(VERSION 3.8)
project(task5 C)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lfuse")

#set(SOURCE_FILES lab5.c)

add_executable(task5 lab5.c)
#target_link_libraries(task5 fuse)