// tests
#include "parser.hpp"

// http-mp
#include "http_mp/http_mp.hpp"

// googletest
#include <gtest/gtest.h>

// stl
#include <sstream>

using namespace http_mp;

TEST(Parser, emptyMessage) {
  std::stringbuf mesg{""};
  RequestParser p(&mesg);
  Request r = p.parse();
  ASSERT_EQ(r, Request{});
}

TEST(Parser, wrongChar) {
  std::stringbuf mesg{"LONK"};
  RequestParser p(&mesg);
  ASSERT_THROW(p.parse(), std::runtime_error);
}

TEST_P(ParserMethodTest, parseMethods) {
  auto [message, method] = GetParam();
  std::stringbuf mesg{message};
  RequestParser p(&mesg);
  Request r = p.parse();
  ASSERT_EQ(r, Request{method});
}
