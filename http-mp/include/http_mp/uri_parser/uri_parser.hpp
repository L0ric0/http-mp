#ifndef HTTP_MP__URI_PARSER__URI_PARSER_HPP_
#define HTTP_MP__URI_PARSER__URI_PARSER_HPP_

// http-mp
#include "http_mp/uri_parser/uri_state.hpp"

// stl
#include <istream>
#include <string>
#include <unordered_map>

namespace http_mp {

class URIParser {
public:
  URIParser(std::istream &stream,
            const URIParserState state = URIParserState::Start);
  std::string parse();

  static const std::unordered_map<char, bool> &generate_sub_delimiters() {
    static const std::unordered_map<char, bool> sub_delimiters{
        {'!', true}, {'$', true}, {'&', true}, {'\'', true},
        {'(', true}, {')', true}, {'*', true}, {'+', true},
        {',', true}, {';', true}, {'=', true},
    };
    return sub_delimiters;
  }

  const std::unordered_map<char, bool> sub_delimiters =
      generate_sub_delimiters();

  static const std::unordered_map<char, bool> &generate_unreserved() {
    static const std::unordered_map<char, bool> unreserved{
        {'-', true}, {'.', true}, {'_', true}, {'~', true}, {'0', true},
        {'1', true}, {'2', true}, {'3', true}, {'4', true}, {'5', true},
        {'6', true}, {'7', true}, {'8', true}, {'9', true}, {'a', true},
        {'b', true}, {'c', true}, {'d', true}, {'e', true}, {'f', true},
        {'g', true}, {'h', true}, {'i', true}, {'j', true}, {'k', true},
        {'l', true}, {'m', true}, {'n', true}, {'o', true}, {'p', true},
        {'q', true}, {'r', true}, {'s', true}, {'t', true}, {'u', true},
        {'v', true}, {'w', true}, {'x', true}, {'y', true}, {'z', true},
        {'A', true}, {'B', true}, {'C', true}, {'D', true}, {'E', true},
        {'F', true}, {'G', true}, {'H', true}, {'I', true}, {'J', true},
        {'K', true}, {'L', true}, {'M', true}, {'N', true}, {'O', true},
        {'P', true}, {'Q', true}, {'R', true}, {'S', true}, {'T', true},
        {'U', true}, {'V', true}, {'W', true}, {'X', true}, {'Y', true},
        {'Z', true},
    };
    return unreserved;
  }

  const std::unordered_map<char, bool> unreserved = generate_unreserved();

  static const std::unordered_map<char, bool> &generate_alpha() {
    static const std::unordered_map<char, bool> alpha{
        {'a', true}, {'b', true}, {'c', true}, {'d', true}, {'e', true},
        {'f', true}, {'g', true}, {'h', true}, {'i', true}, {'j', true},
        {'k', true}, {'l', true}, {'m', true}, {'n', true}, {'o', true},
        {'p', true}, {'q', true}, {'r', true}, {'s', true}, {'t', true},
        {'u', true}, {'v', true}, {'w', true}, {'x', true}, {'y', true},
        {'z', true}, {'A', true}, {'B', true}, {'C', true}, {'D', true},
        {'E', true}, {'F', true}, {'G', true}, {'H', true}, {'I', true},
        {'J', true}, {'K', true}, {'L', true}, {'M', true}, {'N', true},
        {'O', true}, {'P', true}, {'Q', true}, {'R', true}, {'S', true},
        {'T', true}, {'U', true}, {'V', true}, {'W', true}, {'X', true},
        {'Y', true}, {'Z', true},
    };
    return alpha;
  }

  const std::unordered_map<char, bool> alpha = generate_alpha();

  bool is_url_char(const char ch) const noexcept;

  URIParserState parse_char(const char ch, const URIParserState state) const;

private:
  std::istream &m_stream;
  URIParserState m_state = URIParserState::Start;
};

} // namespace http_mp

#endif // HTTP_MP__URI_PARSER__URI_PARSER_HPP_
