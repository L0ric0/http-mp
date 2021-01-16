#ifndef HTTP_MP__URI_PARSER__URI_STATE_HPP_
#define HTTP_MP__URI_PARSER__URI_STATE_HPP_

namespace http_mp {

enum class URIParserState {
  Start,
  Scheme,
  Scheme_Slash,
  Scheme_Slash_Slash,
  Authority,
  Authority_At,
  Path,
  Query,
  Fragment,
};

}

#endif // HTTP_MP__URI_PARSER__URI_STATE_HPP_
