set(BINARY ${CMAKE_PROJECT_NAME}_test)

add_executable(${BINARY} EXCLUDE_FROM_ALL
    "include/parser.hpp" "src/parser.cpp"
)

target_include_directories(${BINARY} PRIVATE include)

find_package(GTest REQUIRED)
target_link_libraries(${BINARY} PRIVATE GTest::GTest GTest::Main)

target_link_libraries(${BINARY} PRIVATE http-mp)

gtest_discover_tests(${BINARY})

if (COVERAGE)
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME ${PROJECT_NAME}_coverage
        EXECUTABLE ctest -j ${PROCESSOR_COUNT}
        DEPENDENCIES ${CMAKE_PROJECT_NAME}_test
        EXCLUDE ${PROJECT_SOURCE_DIR}/tests
    )
endif()
