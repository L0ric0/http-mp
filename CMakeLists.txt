cmake_minimum_required(VERSION 3.10)

project(http-mp VERSION 0.0.1)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(COVERAGE OFF)
if(COVERAGE)
    include(CodeCoverage)
endif()

add_subdirectory(http-mp)
add_subdirectory(tests)
