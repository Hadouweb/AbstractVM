cmake_minimum_required(VERSION 3.6)
project(abstractVM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(headers)

set(SOURCE_FILES
    srcs/main.cpp
    srcs/Lexer.class.cpp
    headers/Lexer.class.hpp
    )

add_executable(abstractVM ${SOURCE_FILES})