cmake_minimum_required(VERSION 3.6)
project(abstractVM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(headers)
include_directories(srcs)

set(SOURCE_FILES
    srcs/main.cpp
    srcs/Lexer.class.cpp
    srcs/Node.class.cpp
    srcs/Parser.class.cpp
    srcs/ParsedNode.class.cpp
    srcs/Operand.class.cpp
    headers/Lexer.class.hpp
    headers/Node.class.hpp
    headers/Parser.class.hpp
    headers/ParsedNode.class.hpp
    headers/Operand.class.hpp
    headers/IOperand.class.hpp
    )

add_executable(abstractVM ${SOURCE_FILES})