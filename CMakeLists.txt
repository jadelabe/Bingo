cmake_minimum_required (VERSION 2.6)

project (bingo)

set (security_VERSION_MAJOR 0)
set (security_VERSION_MINOR 1)
set (CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-std=c99")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(bingo main.c)

