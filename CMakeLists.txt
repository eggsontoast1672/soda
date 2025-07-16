cmake_minimum_required(VERSION 3.12)
project(Soda)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR Ninja)

add_executable(soda
  src/fs.cpp
  src/lexer.cpp
  src/logging.cpp
  src/main.cpp
  src/options.cpp
  src/parser.cpp
  src/token.cpp)

target_compile_options(soda
  PRIVATE
    -Wall -Wextra
    -pedantic)

target_include_directories(soda PRIVATE include)
