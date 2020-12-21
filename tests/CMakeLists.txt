set(BINARY ${CMAKE_PROJECT_NAME}_test)

add_executable(${BINARY} EXCLUDE_FROM_ALL
    src/tokenizer.cpp)

target_include_directories(${BINARY} PRIVATE include)

find_package(GTest REQUIRED)
target_link_libraries(${BINARY} PRIVATE GTest::GTest GTest::Main)

target_link_libraries(${BINARY} PRIVATE http-mp)

gtest_discover_tests(${BINARY})
