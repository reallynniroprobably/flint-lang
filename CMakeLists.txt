cmake_minimum_required(VERSION 4.1)
project(Cobalt)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(Cobalt
        src/lexer.cpp
        src/main.cpp
)
