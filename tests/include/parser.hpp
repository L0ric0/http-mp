#ifndef PARSER_HPP_
#define PARSER_HPP_

// http_mp
#include "http_mp/method.hpp"

// googletest
#include <gtest/gtest.h>

// stl
#include <string>

using namespace http_mp;

class ParserMethodTest
    : public testing::TestWithParam<std::pair<const char *, Method>> {};

INSTANTIATE_TEST_SUITE_P(
    Methods, ParserMethodTest,
    testing::ValuesIn({
        std::make_pair("ACL", Method::ACL),
        std::make_pair("BASELINE-CONTROL", Method::BASELINE_CONTROL),
        std::make_pair("BIND", Method::BIND),
        std::make_pair("CHECKIN", Method::CHECKIN),
        std::make_pair("CHECKOUT", Method::CHECKOUT),
        std::make_pair("CONNECT", Method::CONNECT),
        std::make_pair("COPY", Method::COPY),
        std::make_pair("DELETE", Method::DELETE),
        std::make_pair("GET", Method::GET),
        std::make_pair("HEAD", Method::HEAD),
        std::make_pair("LABEL", Method::LABEL),
        std::make_pair("LINK", Method::LINK),
        std::make_pair("LOCK", Method::LOCK),
        std::make_pair("MERGE", Method::MERGE),
        std::make_pair("MKACTIVITY", Method::MKACTIVITY),
        std::make_pair("MKCALENDAR", Method::MKCALENDAR),
        std::make_pair("MKCOL", Method::MKCOL),
        std::make_pair("MKREDIRECTREF", Method::MKREDIRECTREF),
        std::make_pair("MKWORKSPACE", Method::MKWORKSPACE),
        std::make_pair("MOVE", Method::MOVE),
        std::make_pair("OPTIONS", Method::OPTIONS),
        std::make_pair("ORDERPATCH", Method::ORDERPATCH),
        std::make_pair("PATCH", Method::PATCH),
        std::make_pair("POST", Method::POST),
        std::make_pair("PRI", Method::PRI),
        std::make_pair("PROPFIND", Method::PROPFIND),
        std::make_pair("PROPPATCH", Method::PROPPATCH),
        std::make_pair("PUT", Method::PUT),
        std::make_pair("REBIND", Method::REBIND),
        std::make_pair("REPORT", Method::REPORT),
        std::make_pair("SEARCH", Method::SEARCH),
        std::make_pair("TRACE", Method::TRACE),
        std::make_pair("UNBIND", Method::UNBIND),
        std::make_pair("UNCHECKOUT", Method::UNCHECKOUT),
        std::make_pair("UNLINK", Method::UNLINK),
        std::make_pair("UNLOCK", Method::UNLOCK),
        std::make_pair("UPDATE", Method::UPDATE),
        std::make_pair("UPDATEREDIRECTREF", Method::UPDATEREDIRECTREF),
        std::make_pair("VERSION-CONTROL", Method::VERSION_CONTROL),
    }));

#endif // PARSER_HPP_
