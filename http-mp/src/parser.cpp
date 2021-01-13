// http-mp
#include "http_mp/parser.hpp"
#include "http_mp/method.hpp"
#include "http_mp/request.hpp"
#include "http_mp/state.hpp"

// stl
#include <iostream>
#include <stdexcept>
#include <streambuf>
#include <string_view>
#include <utility>

namespace http_mp {

Parser::Parser(std::streambuf *message)
    : m_stream(message), m_state(State::Start) {}

Request Parser::parse() {
  Request request{};
  for (char ch = m_stream.get(); !m_stream.eof(); ch = m_stream.get()) {
    std::cout << ch << "\n";
    auto [state, chars] =
        state_char_state_chars_map.at(std::make_pair(m_state, ch));

    for (const auto &elem : chars) {
      if (not(elem == m_stream.get())) {
        throw std::runtime_error("Unexpected char.");
      }
    }

    m_state = state;
    if (auto it = state_func_map.find(m_state); it != state_func_map.end()) {
      request = it->second(*this, request, ch);
    }
  }
  return request;
}

Request Parser::set_method(Parser &parser, Request &request, const char ch) {
  auto method = parser.state_method_map.at(parser.m_state);
  request.method = method;
  parser.m_state = State::METHOD_SP;
  return request;
}

Request Parser::set_update_method(Parser &parser, Request &request,
                                  const char ch) {
  if (parser.m_stream.peek() == 'R') {
    return request;
  }
  return set_method(parser, request, ch);
}

} // namespace http_mp
