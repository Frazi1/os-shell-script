cmake_minimum_required(VERSION 3.8)
project(task6)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(task6 ${SOURCE_FILES})
target_link_libraries(task6 pthread tokyotyrant tokyocabinet )
