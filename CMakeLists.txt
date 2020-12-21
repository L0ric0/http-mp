cmake_minimum_required(VERSION 3.10)

project(http-mp VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(http-mp)
add_subdirectory(tests)
