#ifndef HTTP_MP__PARSER_HPP_
#define HTTP_MP__PARSER_HPP_

// http-mp
#include "http_mp/request.hpp"
#include "http_mp/state.hpp"

// stl
#include <array>
#include <functional>
#include <istream>
#include <optional>
#include <streambuf>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace std {

template <> struct hash<std::pair<http_mp::RequestState, std::optional<char>>> {
  std::size_t
  operator()(std::pair<http_mp::RequestState, std::optional<char>> const &p)
      const noexcept {
    std::size_t h1 = std::hash<http_mp::RequestState>{}(p.first);
    if (p.second) {
      std::size_t h2 = std::hash<std::optional<char>>{}(p.second);
      return h1 ^ (h2 << 1);
    }
    return h1;
  }
};

} // namespace std

namespace http_mp {

class RequestParser {
public:
  RequestParser(std::streambuf *message);

  // const char maps
  static const std::unordered_map<char, bool> &generate_gen_delimiters() {
    static const std::unordered_map<char, bool> gen_delimiters{
        {':', true}, {'/', true}, {'?', true}, {'#', true},
        {'[', true}, {']', true}, {'@', true},
    };
    return gen_delimiters;
  }

  const std::unordered_map<char, bool> gen_delimiters =
      generate_gen_delimiters();

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

  static const std::unordered_map<char, bool> &generate_numbers() {
    static const std::unordered_map<char, bool> numbers{
        {'0', true}, {'1', true}, {'2', true}, {'3', true}, {'4', true},
        {'5', true}, {'6', true}, {'7', true}, {'8', true}, {'9', true},
    };
    return numbers;
  }

  const std::unordered_map<char, bool> numbers = generate_numbers();

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

  // state machine maps
  static const std::unordered_map<
      RequestState, std::function<Request(RequestParser &, Request &)>> &
  generate_state_func_map() {

    using enum RequestState;

    static const std::unordered_map<
        RequestState, std::function<Request(RequestParser &, Request &)>>
        &state_func_map{
            {ACL, RequestParser::set_method},
            {BASELINE_CONTROL, RequestParser::set_method},
            {BIND, RequestParser::set_method},
            {CHECKIN, RequestParser::set_method},
            {CHECKOUT, RequestParser::set_method},
            {CONNECT, RequestParser::set_method},
            {COPY, RequestParser::set_method},
            {DELETE, RequestParser::set_method},
            {GET, RequestParser::set_method},
            {HEAD, RequestParser::set_method},
            {LABEL, RequestParser::set_method},
            {LINK, RequestParser::set_method},
            {LOCK, RequestParser::set_method},
            {MERGE, RequestParser::set_method},
            {MKACTIVITY, RequestParser::set_method},
            {MKCALENDAR, RequestParser::set_method},
            {MKCOL, RequestParser::set_method},
            {MKREDIRECTREF, RequestParser::set_method},
            {MKWORKSPACE, RequestParser::set_method},
            {MOVE, RequestParser::set_method},
            {OPTIONS, RequestParser::set_method},
            {ORDERPATCH, RequestParser::set_method},
            {PATCH, RequestParser::set_method},
            {POST, RequestParser::set_method},
            {PRI, RequestParser::set_method},
            {PROPFIND, RequestParser::set_method},
            {PROPPATCH, RequestParser::set_method},
            {PUT, RequestParser::set_method},
            {REBIND, RequestParser::set_method},
            {REPORT, RequestParser::set_method},
            {SEARCH, RequestParser::set_method},
            {TRACE, RequestParser::set_method},
            {UNBIND, RequestParser::set_method},
            {UNCHECKOUT, RequestParser::set_method},
            {UNLINK, RequestParser::set_method},
            {UNLOCK, RequestParser::set_method},
            {UPDATE, RequestParser::set_method},
            {UPDATEREDIRECTREF, RequestParser::set_method},
            {VERSION_CONTROL, RequestParser::set_method},
            {REQUEST_TARGET, RequestParser::parse_target},
        };
    return state_func_map;
  }

  const std::unordered_map<RequestState,
                           std::function<Request(RequestParser &, Request &)>>
      state_func_map = generate_state_func_map();

  static const std::unordered_map<std::pair<RequestState, std::optional<char>>,
                                  std::pair<RequestState, std::string_view>> &
  generate_state_char_state_chars_map() {
    using enum RequestState;
    static const std::unordered_map<
        std::pair<RequestState, std::optional<char>>,
        std::pair<RequestState, std::string_view>>
        state_char_state_chars_map{{
            {{START, 'A'}, {ACL, "CL "}},
            {{START, 'B'}, {B, ""}},
            {{B, 'A'}, {BASELINE_CONTROL, "SELINE-CONTROL "}},
            {{B, 'I'}, {BIND, "ND "}},
            {{START, 'C'}, {C, ""}},
            {{C, 'H'}, {CHECK, "ECK"}},
            {{CHECK, 'I'}, {CHECKIN, "N "}},
            {{CHECK, 'O'}, {CHECKOUT, "UT "}},
            {{C, 'O'}, {CO, ""}},
            {{CO, 'N'}, {CONNECT, "NECT "}},
            {{CO, 'P'}, {COPY, "Y "}},
            {{START, 'D'}, {DELETE, "ELETE "}},
            {{START, 'G'}, {GET, "ET "}},
            {{START, 'H'}, {HEAD, "EAD "}},
            {{START, 'L'}, {L, ""}},
            {{L, 'A'}, {LABEL, "BEL "}},
            {{L, 'I'}, {LINK, "NK "}},
            {{L, 'O'}, {LOCK, "CK "}},
            {{START, 'M'}, {M, ""}},
            {{M, 'E'}, {MERGE, "RGE "}},
            {{M, 'K'}, {MK, ""}},
            {{MK, 'A'}, {MKACTIVITY, "CTIVITY "}},
            {{MK, 'C'}, {MKC, ""}},
            {{MKC, 'A'}, {MKCALENDAR, "LENDAR "}},
            {{MKC, 'O'}, {MKCOL, "L "}},
            {{MK, 'R'}, {MKREDIRECTREF, "EDIRECTREF "}},
            {{MK, 'W'}, {MKWORKSPACE, "ORKSPACE "}},
            {{M, 'O'}, {MOVE, "VE "}},
            {{START, 'O'}, {O, ""}},
            {{O, 'P'}, {OPTIONS, "TIONS "}},
            {{O, 'R'}, {ORDERPATCH, "DERPATCH "}},
            {{START, 'P'}, {P, ""}},
            {{P, 'A'}, {PATCH, "TCH "}},
            {{P, 'O'}, {POST, "ST "}},
            {{P, 'R'}, {PR, ""}},
            {{PR, 'I'}, {PRI, " "}},
            {{PR, 'O'}, {PROP, "P"}},
            {{PROP, 'F'}, {PROPFIND, "IND "}},
            {{PROP, 'P'}, {PROPPATCH, "ATCH "}},
            {{P, 'U'}, {PUT, "T "}},
            {{START, 'R'}, {RE, "E"}},
            {{RE, 'B'}, {REBIND, "IND "}},
            {{RE, 'P'}, {REPORT, "ORT "}},
            {{START, 'S'}, {SEARCH, "EARCH "}},
            {{START, 'T'}, {TRACE, "RACE "}},
            {{START, 'U'}, {U, ""}},
            {{U, 'N'}, {UN, ""}},
            {{UN, 'B'}, {UNBIND, "IND "}},
            {{UN, 'C'}, {UNCHECKOUT, "HECKOUT "}},
            {{UN, 'L'}, {UNL, ""}},
            {{UNL, 'I'}, {UNLINK, "NK "}},
            {{UNL, 'O'}, {UNLOCK, "CK "}},
            {{U, 'P'}, {UPDATE_pre, "DATE"}},
            {{UPDATE_pre, ' '}, {UPDATE, ""}},
            {{UPDATE_pre, 'R'}, {UPDATEREDIRECTREF, "EDIRECTREF "}},
            {{START, 'V'}, {VERSION_CONTROL, "ERSION-CONTROL "}},
            {{REQUEST_TARGET, {}}, {HTTP_VERSION, ""}},
        }};
    return state_char_state_chars_map;
  }

  const std::unordered_map<std::pair<RequestState, std::optional<char>>,
                           std::pair<RequestState, std::string_view>>
      state_char_state_chars_map = generate_state_char_state_chars_map();

  static const std::unordered_map<RequestState, Method> &
  generate_state_method_map() {
    using enum RequestState;
    static const std::unordered_map<RequestState, Method> state_method_map{
        {ACL, Method::ACL},
        {BASELINE_CONTROL, Method::BASELINE_CONTROL},
        {BIND, Method::BIND},
        {CHECKIN, Method::CHECKIN},
        {CHECKOUT, Method::CHECKOUT},
        {CONNECT, Method::CONNECT},
        {COPY, Method::COPY},
        {DELETE, Method::DELETE},
        {GET, Method::GET},
        {HEAD, Method::HEAD},
        {LABEL, Method::LABEL},
        {LINK, Method::LINK},
        {LOCK, Method::LOCK},
        {MERGE, Method::MERGE},
        {MKACTIVITY, Method::MKACTIVITY},
        {MKCALENDAR, Method::MKCALENDAR},
        {MKCOL, Method::MKCOL},
        {MKREDIRECTREF, Method::MKREDIRECTREF},
        {MKWORKSPACE, Method::MKWORKSPACE},
        {MOVE, Method::MOVE},
        {OPTIONS, Method::OPTIONS},
        {ORDERPATCH, Method::ORDERPATCH},
        {PATCH, Method::PATCH},
        {POST, Method::POST},
        {PRI, Method::PRI},
        {PROPFIND, Method::PROPFIND},
        {PROPPATCH, Method::PROPPATCH},
        {PUT, Method::PUT},
        {REBIND, Method::REBIND},
        {REPORT, Method::REPORT},
        {SEARCH, Method::SEARCH},
        {TRACE, Method::TRACE},
        {UNBIND, Method::UNBIND},
        {UNCHECKOUT, Method::UNCHECKOUT},
        {UNLINK, Method::UNLINK},
        {UNLOCK, Method::UNLOCK},
        {UPDATE, Method::UPDATE},
        {UPDATEREDIRECTREF, Method::UPDATEREDIRECTREF},
        {VERSION_CONTROL, Method::VERSION_CONTROL},
    };
    return state_method_map;
  }

  const std::unordered_map<RequestState, Method> state_method_map =
      generate_state_method_map();

  Request parse();

  static Request set_method(RequestParser &parser, Request &request);

  static Request parse_target(RequestParser &parser, Request &request);

  static Request parse_target_connect(RequestParser &parser, Request &request);

  Request parse_target_absolute(Request &request);

  Request parse_target_asterisk(Request &request);

  Request parse_target_origin(Request &request);

  std::string parse_until_space(std::function<char(char)> fn);

private:
  std::istream m_stream;
  Request m_request{};
  RequestState m_state{RequestState::START};
};

} // namespace http_mp

#endif // HTTP_MP__PARSER_HPP_
