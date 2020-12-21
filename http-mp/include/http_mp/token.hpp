#ifndef HTTP_MP__TOKEN_HPP_
#define HTTP_MP__TOKEN_HPP_

// stl
#include <array>
#include <string>
#include <string_view>

namespace http_mp {

struct Token {
  std::string_view token;
  bool is_end;
};

} // namespace http_mp

#endif // HTTP_MP__TOKEN_HPP
