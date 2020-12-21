// http-mp
#include "http_mp/tokenizer.hpp"
#include "http_mp/token.hpp"

// stl
#include <string_view>

namespace http_mp {

Tokenizer::Tokenizer(const std::string_view message) : m_message(message) {}

Token Tokenizer::next_token() {
  if (size_t sep_pos = m_message.find_first_of(" \t", m_pos);
      sep_pos != std::string_view::npos) {

    if (sep_pos == m_pos) {
      m_pos++;
      return next_token();
    }
    auto token = m_message.substr(m_pos, sep_pos);
    m_pos = sep_pos;
    return Token{token, false};
  }

  auto token = m_message.substr(m_pos);
  m_pos = std::string_view::npos;
  return Token{token, true};
}

} // namespace http_mp
