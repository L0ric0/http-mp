#ifndef HTTP_MP__PARSER_HPP_
#define HTTP_MP__PARSER_HPP_

// http-mp
#include "http_mp/request.hpp"
#include "http_mp/state.hpp"

// stl
#include <array>
#include <functional>
#include <istream>
#include <streambuf>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace std {

template <> struct hash<std::pair<http_mp::State, char>> {
  std::size_t
  operator()(std::pair<http_mp::State, char> const &p) const noexcept {
    std::size_t h1 = std::hash<http_mp::State>{}(p.first);
    std::size_t h2 = std::hash<char>{}(p.second);
    return h1 ^ (h2 << 1);
  }
};

} // namespace std

namespace http_mp {

class Parser {
public:
  Parser(std::streambuf *message);

  static const std::array<char, 19> &generate_separators() {
    static const std::array<char, 19> separators{
        '(', ')', '<', '>', '@', ',', ';', ':', '\\', '"',
        '/', '[', ']', '?', '=', '{', '}', ' ', '\t'};
    return separators;
  }

  const std::array<char, 19> &separators = generate_separators();

  static const std::array<char, 78> &generate_tokens() {
    static const std::array<char, 78> tokens{
        ' ', '!', '#', '$', '%', '&', '\'', '*', '+', '-', '.', '0', '1',
        '2', '3', '4', '5', '6', '7', '8',  '9', 'A', 'B', 'C', 'D', 'E',
        'F', 'G', 'H', 'I', 'J', 'K', 'L',  'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y',  'Z', '^', '_', '`', 'a', 'b',
        'c', 'd', 'e', 'f', 'g', 'h', 'i',  'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v',  'w', 'x', 'y', 'z', '|', '~'};
    return tokens;
  }

  const std::array<char, 78> &tokens = generate_tokens();

  static const std::unordered_map<
      State, std::function<Request(Parser &, Request &, char)>> &
  generate_state_func_map() {

    static const std::unordered_map<
        State, std::function<Request(Parser &, Request &, char)>>
        &state_func_map{
            {State::ACL_req, Parser::set_method},
            {State::BASELINE_CONTROL_req, Parser::set_method},
            {State::BIND_req, Parser::set_method},
            {State::CHECKIN_req, Parser::set_method},
            {State::CHECKOUT_req, Parser::set_method},
            {State::CONNECT_req, Parser::set_method},
            {State::COPY_req, Parser::set_method},
            {State::DELETE_req, Parser::set_method},
            {State::GET_req, Parser::set_method},
            {State::HEAD_req, Parser::set_method},
            {State::LABEL_req, Parser::set_method},
            {State::LINK_req, Parser::set_method},
            {State::LOCK_req, Parser::set_method},
            {State::MERGE_req, Parser::set_method},
            {State::MKACTIVITY_req, Parser::set_method},
            {State::MKCALENDAR_req, Parser::set_method},
            {State::MKCOL_req, Parser::set_method},
            {State::MKREDIRECTREF_req, Parser::set_method},
            {State::MKWORKSPACE_req, Parser::set_method},
            {State::MOVE_req, Parser::set_method},
            {State::OPTIONS_req, Parser::set_method},
            {State::ORDERPATCH_req, Parser::set_method},
            {State::PATCH_req, Parser::set_method},
            {State::POST_req, Parser::set_method},
            {State::PRI_req, Parser::set_method},
            {State::PROPFIND_req, Parser::set_method},
            {State::PROPPATCH_req, Parser::set_method},
            {State::PUT_req, Parser::set_method},
            {State::REBIND_req, Parser::set_method},
            {State::REPORT_req, Parser::set_method},
            {State::SEARCH_req, Parser::set_method},
            {State::TRACE_req, Parser::set_method},
            {State::UNBIND_req, Parser::set_method},
            {State::UNCHECKOUT_req, Parser::set_method},
            {State::UNLINK_req, Parser::set_method},
            {State::UNLOCK_req, Parser::set_method},
            {State::UPDATE_req, Parser::set_update_method},
            {State::UPDATEREDIRECTREF_req, Parser::set_method},
            {State::VERSION_CONTROL_req, Parser::set_method},
        };
    return state_func_map;
  }

  const std::unordered_map<State,
                           std::function<Request(Parser &, Request &, char)>>
      state_func_map = generate_state_func_map();

  static const std::unordered_map<std::pair<State, char>,
                                  std::pair<State, std::string_view>> &
  generate_state_char_state_chars_map() {
    static const std::unordered_map<std::pair<State, char>,
                                    std::pair<State, std::string_view>>
        state_char_state_chars_map{{
            {{State::Start, 'A'}, {State::ACL_req, "CL"}},
            {{State::Start, 'B'}, {State::B_req, ""}},
            {{State::B_req, 'A'},
             {State::BASELINE_CONTROL_req, "SELINE-CONTROL"}},
            {{State::B_req, 'I'}, {State::BIND_req, "ND"}},
            {{State::Start, 'C'}, {State::C_req, ""}},
            {{State::C_req, 'H'}, {State::CHECK_req, "ECK"}},
            {{State::CHECK_req, 'I'}, {State::CHECKIN_req, "N"}},
            {{State::CHECK_req, 'O'}, {State::CHECKOUT_req, "UT"}},
            {{State::C_req, 'O'}, {State::CO_req, ""}},
            {{State::CO_req, 'N'}, {State::CONNECT_req, "NECT"}},
            {{State::CO_req, 'P'}, {State::COPY_req, "Y"}},
            {{State::Start, 'D'}, {State::DELETE_req, "ELETE"}},
            {{State::Start, 'G'}, {State::GET_req, "ET"}},
            {{State::Start, 'H'}, {State::H_req_resp, ""}},
            {{State::H_req_resp, 'E'}, {State::HEAD_req, "AD"}},
            {{State::H_req_resp, 'T'}, {State::HTTP_resp, "TP"}},
            {{State::Start, 'L'}, {State::L_req, ""}},
            {{State::L_req, 'A'}, {State::LABEL_req, "BEL"}},
            {{State::L_req, 'I'}, {State::LINK_req, "NK"}},
            {{State::L_req, 'O'}, {State::LOCK_req, "CK"}},
            {{State::Start, 'M'}, {State::M_req, ""}},
            {{State::M_req, 'E'}, {State::MERGE_req, "RGE"}},
            {{State::M_req, 'K'}, {State::MK_req, ""}},
            {{State::MK_req, 'A'}, {State::MKACTIVITY_req, "CTIVITY"}},
            {{State::MK_req, 'C'}, {State::MKC_req, ""}},
            {{State::MKC_req, 'A'}, {State::MKCALENDAR_req, "LENDAR"}},
            {{State::MKC_req, 'O'}, {State::MKCOL_req, "L"}},
            {{State::MK_req, 'R'}, {State::MKREDIRECTREF_req, "EDIRECTREF"}},
            {{State::MK_req, 'W'}, {State::MKWORKSPACE_req, "ORKSPACE"}},
            {{State::M_req, 'O'}, {State::MOVE_req, "VE"}},
            {{State::Start, 'O'}, {State::O_req, ""}},
            {{State::O_req, 'P'}, {State::OPTIONS_req, "TIONS"}},
            {{State::O_req, 'R'}, {State::ORDERPATCH_req, "DERPATCH"}},
            {{State::Start, 'P'}, {State::P_req, ""}},
            {{State::P_req, 'A'}, {State::PATCH_req, "TCH"}},
            {{State::P_req, 'O'}, {State::POST_req, "ST"}},
            {{State::P_req, 'R'}, {State::PR_req, ""}},
            {{State::PR_req, 'I'}, {State::PRI_req, ""}},
            {{State::PR_req, 'O'}, {State::PROP_req, "P"}},
            {{State::PROP_req, 'F'}, {State::PROPFIND_req, "IND"}},
            {{State::PROP_req, 'P'}, {State::PROPPATCH_req, "ATCH"}},
            {{State::P_req, 'U'}, {State::PUT_req, "T"}},
            {{State::Start, 'R'}, {State::RE_req, "E"}},
            {{State::RE_req, 'B'}, {State::REBIND_req, "IND"}},
            {{State::RE_req, 'P'}, {State::REPORT_req, "ORT"}},
            {{State::Start, 'S'}, {State::SEARCH_req, "EARCH"}},
            {{State::Start, 'T'}, {State::TRACE_req, "RACE"}},
            {{State::Start, 'U'}, {State::U_req, ""}},
            {{State::U_req, 'N'}, {State::UN_req, ""}},
            {{State::UN_req, 'B'}, {State::UNBIND_req, "IND"}},
            {{State::UN_req, 'C'}, {State::UNCHECKOUT_req, "HECKOUT"}},
            {{State::UN_req, 'L'}, {State::UNL_req, ""}},
            {{State::UNL_req, 'I'}, {State::UNLINK_req, "NK"}},
            {{State::UNL_req, 'O'}, {State::UNLOCK_req, "CK"}},
            {{State::U_req, 'P'}, {State::UPDATE_req, "DATE"}},
            {{State::UPDATE_req, 'R'},
             {State::UPDATEREDIRECTREF_req, "EDIRECTREF"}},
            {{State::Start, 'V'},
             {State::VERSION_CONTROL_req, "ERSION-CONTROL"}},
        }};
    return state_char_state_chars_map;
  }

  const std::unordered_map<std::pair<State, char>,
                           std::pair<State, std::string_view>>
      state_char_state_chars_map = generate_state_char_state_chars_map();

  static const std::unordered_map<State, Method> &generate_state_method_map() {
    static const std::unordered_map<State, Method> state_method_map{
        {State::ACL_req, Method::ACL},
        {State::BASELINE_CONTROL_req, Method::BASELINE_CONTROL},
        {State::BIND_req, Method::BIND},
        {State::CHECKIN_req, Method::CHECKIN},
        {State::CHECKOUT_req, Method::CHECKOUT},
        {State::CONNECT_req, Method::CONNECT},
        {State::COPY_req, Method::COPY},
        {State::DELETE_req, Method::DELETE},
        {State::GET_req, Method::GET},
        {State::HEAD_req, Method::HEAD},
        {State::LABEL_req, Method::LABEL},
        {State::LINK_req, Method::LINK},
        {State::LOCK_req, Method::LOCK},
        {State::MERGE_req, Method::MERGE},
        {State::MKACTIVITY_req, Method::MKACTIVITY},
        {State::MKCALENDAR_req, Method::MKCALENDAR},
        {State::MKCOL_req, Method::MKCOL},
        {State::MKREDIRECTREF_req, Method::MKREDIRECTREF},
        {State::MKWORKSPACE_req, Method::MKWORKSPACE},
        {State::MOVE_req, Method::MOVE},
        {State::OPTIONS_req, Method::OPTIONS},
        {State::ORDERPATCH_req, Method::ORDERPATCH},
        {State::PATCH_req, Method::PATCH},
        {State::POST_req, Method::POST},
        {State::PRI_req, Method::PRI},
        {State::PROPFIND_req, Method::PROPFIND},
        {State::PROPPATCH_req, Method::PROPPATCH},
        {State::PUT_req, Method::PUT},
        {State::REBIND_req, Method::REBIND},
        {State::REPORT_req, Method::REPORT},
        {State::SEARCH_req, Method::SEARCH},
        {State::TRACE_req, Method::TRACE},
        {State::UNBIND_req, Method::UNBIND},
        {State::UNCHECKOUT_req, Method::UNCHECKOUT},
        {State::UNLINK_req, Method::UNLINK},
        {State::UNLOCK_req, Method::UNLOCK},
        {State::UPDATE_req, Method::UPDATE},
        {State::UPDATEREDIRECTREF_req, Method::UPDATEREDIRECTREF},
        {State::VERSION_CONTROL_req, Method::VERSION_CONTROL},
    };
    return state_method_map;
  }

  const std::unordered_map<State, Method> state_method_map =
      generate_state_method_map();

  Request parse();

  static Request set_method(Parser &parser, Request &request, const char ch);

  static Request set_update_method(Parser &parser, Request &request,
                                   const char ch);

private:
  std::istream m_stream;
  Request m_request;
  State m_state;
};

} // namespace http_mp

#endif // HTTP_MP__PARSER_HPP_
