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

TEST(Tokenizer, endline) {
  http_mp::Tokenizer t{"asdf\n\rfdsa"};
  http_mp::Token token = t.next_token();
  ASSERT_EQ(token.token, "asdf");
  token = t.next_token();
  ASSERT_EQ(token.token, "\n\r");
  token = t.next_token();
  ASSERT_EQ(token.token, "fdsa");
  ASSERT_TRUE(token.is_end);
}

TEST(Tokenizer, endlineAtEnd) {
  http_mp::Tokenizer t{"\n\r"};
  http_mp::Token token = t.next_token();
  ASSERT_TRUE(token.is_end);
  ASSERT_EQ(token.token, "\n\r");
}

TEST(Tokenizer, linecontiuation) {
  http_mp::Tokenizer t{"\n\r\t"};
  http_mp::Token token = t.next_token();
  ASSERT_TRUE(token.is_end);
  ASSERT_EQ(token.token, "");
}
