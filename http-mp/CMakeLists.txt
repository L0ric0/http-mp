add_library(http-mp
    "include/http_mp/http_mp.hpp"
    "include/http_mp/method.hpp"
    "include/http_mp/parser.hpp" "src/parser.cpp"
    "include/http_mp/request.hpp"
    "include/http_mp/state.hpp"
    "include/http_mp/uri_parser/uri_parser.hpp" "src/uri_parser/uri_parser.cpp"
    "include/http_mp/uri_parser/uri_state.hpp")

target_include_directories(http-mp PUBLIC include)
target_include_directories(http-mp PUBLIC "${PROJECT_BINARY_DIR}/include")

if(COVERAGE)
    append_coverage_compiler_flags()
endif()
