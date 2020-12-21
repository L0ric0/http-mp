#ifndef HTTP_MP__TOKENIZER_HPP_
#define HTTP_MP__TOKENIZER_HPP_

// http-mp
#include "http_mp/token.hpp"

// stl
#include <string_view>
#include <vector>

namespace http_mp {

class Tokenizer {
public:
  Tokenizer(const std::string_view message);

  Token next_token();

  static const std::array<std::string, 19> &generate_separators() {
    static const std::array<std::string, 19> separators{
        "(", ")", "<", ">", "@", ",", ";", ":", "\\", "\"",
        "/", "[", "]", "?", "=", "{", "}", " ", "\t"};
    return separators;
  }

  const std::array<std::string, 19> &separators = generate_separators();

private:
  std::string_view m_message;
  size_t m_pos = 0;
};

} // namespace http_mp

#endif // HTTP_MP__TOKENIZER_HPP_
