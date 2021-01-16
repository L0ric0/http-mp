// http-mp
#include "http_mp/parser.hpp"
#include "http_mp/method.hpp"
#include "http_mp/request.hpp"
#include "http_mp/state.hpp"
#include "http_mp/uri_parser/uri_parser.hpp"
#include "http_mp/uri_parser/uri_state.hpp"

// stl
#include <optional>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <utility>

namespace http_mp {

RequestParser::RequestParser(std::streambuf *message) : m_stream(message) {}

Request RequestParser::parse() {
  Request request{};

  for (char ch = m_stream.get(); !m_stream.eof(); ch = m_stream.get()) {
    RequestState state;
    std::string_view chars;

    if (auto it = state_char_state_chars_map.find(std::make_pair(m_state, ch));
        it != state_char_state_chars_map.end()) {
      state = it->second.first;
      chars = it->second.second;
    } else if (auto it = state_char_state_chars_map.find(
                   std::make_pair(m_state, std::optional<char>{}));
               it != state_char_state_chars_map.end()) {
      // put the character back into the input stream a we didn't need it
      m_stream.unget();
      state = it->second.first;
      chars = it->second.second;
    } else {
      throw std::runtime_error("Unexpected char.");
    }

    for (const auto &elem : chars) {
      if (not(elem == m_stream.get())) {
        throw std::runtime_error("Unexpected char.");
      }
    }

    m_state = state;
    if (auto it = state_func_map.find(m_state); it != state_func_map.end()) {
      request = it->second(*this, request);
    }
  }
  return request;
}

Request RequestParser::set_method(RequestParser &parser, Request &request) {
  request.method = parser.state_method_map.at(parser.m_state);
  parser.m_state = RequestState::REQUEST_TARGET;
  return request;
}

Request RequestParser::parse_target(RequestParser &parser, Request &request) {

  if (request.method == Method::CONNECT) [[unlikely]] {
    URIParser uri_parser{parser.m_stream, URIParserState::Authority};
    request.target = uri_parser.parse();
  } else {
    URIParser uri_parser{parser.m_stream};
    request.target = uri_parser.parse();
  }
  parser.m_state = RequestState::HTTP_VERSION;
  return request;
}

} // namespace http_mp
