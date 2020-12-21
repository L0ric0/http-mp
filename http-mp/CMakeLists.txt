file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

add_library(http-mp ${SOURCES})

target_include_directories(http-mp PUBLIC include)
target_include_directories(http-mp PUBLIC "${PROJECT_BINARY_DIR}/include")
