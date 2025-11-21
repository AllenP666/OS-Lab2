cmake_minimum_required(VERSION 3.10)
project(process_lib CXX)

add_library(process_lib src/process.cpp)

target_include_directories(process_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
