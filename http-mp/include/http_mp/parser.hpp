#ifndef HTTP_MP__PARSER_HPP_
#define HTTP_MP__PARSER_HPP_

// http-mp
#include "http_mp/request.hpp"

// stl
#include <string_view>

namespace http_mp {
class Parser {
  Parser();
  Parser(const std::string_view message);

  Request parse();
  Request parse(const std::string_view message);

private:
  std::string_view::iterator m_start;
  std::string_view::iterator m_end;
  std::string_view m_message;
};

} // namespace http_mp

#endif // HTTP_MP__PARSER_HPP_
