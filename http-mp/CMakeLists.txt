file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

add_library(http-mp ${SOURCES})

set_property(TARGET http-mp PROPERTY CXX_STANDARD 20)

target_include_directories(http-mp PRIVATE include)
target_include_directories(http-mp PUBLIC "${PROJECT_BINARY_DIR}/include")
