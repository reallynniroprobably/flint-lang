cmake_minimum_required(VERSION 4.1)
project(flint)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(flint
        src/lexer.cpp
        src/main.cpp
)
