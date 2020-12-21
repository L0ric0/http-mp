// http-mp
#include "http_mp/parser.hpp"
#include "http_mp/request.hpp"

// stl
#include <string_view>

namespace http_mp {

Parser::Parser(const std::string_view message)
    : m_start(message.begin()), m_end(message.end()), m_message(message) {}

Request Parser::parse(const std::string_view message) { return Request(); }

} // namespace http_mp
