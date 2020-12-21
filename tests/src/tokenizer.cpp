// http-mp
#include "http_mp/tokenizer.hpp"
#include "http_mp/token.hpp"

// gtest
#include <gtest/gtest.h>

TEST(Tokenizer, emptyString) {
  http_mp::Tokenizer t{""};
  http_mp::Token token = t.next_token();
  ASSERT_TRUE(token.is_end);
  ASSERT_EQ(token.token, "");
}

TEST(Tokenizer, singelToken) {
  http_mp::Tokenizer t{"asdf"};
  http_mp::Token token = t.next_token();
  ASSERT_TRUE(token.is_end);
  ASSERT_EQ(token.token, "asdf");
}
