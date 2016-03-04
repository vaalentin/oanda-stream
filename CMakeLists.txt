cmake_minimum_required(VERSION 3.4)

project(stream C)

set(STREAM_MAJOR_VERSION 0)
set(STREAM_MINOR_VERSION 1)
set(STREAM_PATCH_VERSION 0)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(cli)
