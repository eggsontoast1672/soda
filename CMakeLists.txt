cmake_minimum_required(VERSION 3.10)
project(Soda)

add_executable(soda src/compiler.cpp src/lexer.cpp src/main.cpp src/parser.cpp src/token.cpp)
target_include_directories(soda PRIVATE include)
