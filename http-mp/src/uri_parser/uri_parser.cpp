// http-mp
#include "http_mp/uri_parser/uri_parser.hpp"

// stl
#include <istream>
#include <stdexcept>

namespace http_mp {

URIParser::URIParser(std::istream &stream, const URIParserState state)
    : m_stream{stream}, m_state{state} {}

bool URIParser::is_url_char(const char ch) const noexcept {
  return (unreserved.contains(ch) or sub_delimiters.contains(ch) or ch == ':' or
          ch == '@' or ch == '%' or ch == '/');
}

std::string URIParser::parse() {
  std::string target{};
  for (char ch = m_stream.get(); !m_stream.eof() and ch != ' ';
       ch = m_stream.get()) {
    m_state = parse_char(ch, m_state);
    target += ch;
  }
  return target;
}

URIParserState URIParser::parse_char(const char ch,
                                     const URIParserState state) const {
  switch (m_state) {
  case URIParserState::Start:
    if (ch == '/' or ch == '*') {
      return URIParserState::Path;
    } else if (alpha.contains(ch)) {
      return URIParserState::Scheme;
    }
    break;
  case URIParserState::Scheme:
    if (alpha.contains(ch)) {
      return URIParserState::Scheme;
    } else if (ch == ':') {
      return URIParserState::Scheme_Slash;
    }
    break;
  case URIParserState::Scheme_Slash:
    if (ch == '/') {
      return URIParserState::Scheme_Slash_Slash;
    }
    break;
  case URIParserState::Scheme_Slash_Slash:
    if (ch == '/') {
      return URIParserState::Authority;
    }
    break;
  case URIParserState::Authority_At:
    if (ch == '@') {
      throw std::runtime_error(
          "Only one '@' allowed in request-target authority part.");
    }
    [[fallthrough]];
  case URIParserState::Authority:
    if (unreserved.contains(ch) or sub_delimiters.contains(ch) or ch == '%' or
        ch == ':') {
      return URIParserState::Authority;
    } else if (ch == '@') {
      return URIParserState::Authority_At;
    } else if (ch == '/') {
      return URIParserState::Path;
    } else if (ch == '?') {
      return URIParserState::Query;
    } else if (ch == '#') {
      return URIParserState::Fragment;
    }
    break;
  case URIParserState::Path:
    if (is_url_char(ch)) {
      return URIParserState::Path;
    } else if (ch == '?') {
      return URIParserState::Query;
    } else if (ch == '#') {
      return URIParserState::Fragment;
    }
    break;
  case URIParserState::Query:
    if (is_url_char(ch) or ch == '?') {
      return URIParserState::Query;
    } else if (ch == '#') {
      return URIParserState::Fragment;
    }
    break;
  case URIParserState::Fragment:
    if (is_url_char(ch) or ch == '?') {
      return URIParserState::Fragment;
    }
    break;
  default:
    throw std::runtime_error("URIParser has unexpected state.");
  }
  throw std::runtime_error("Unexpected char in request-target.");
}

} // namespace http_mp
