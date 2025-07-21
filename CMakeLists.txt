# Version 3.12 for C++20
cmake_minimum_required(VERSION 3.12)
project(Soda)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR Ninja)

add_subdirectory(debug-enum-macro)
add_subdirectory(soda)
