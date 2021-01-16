#ifndef PARSER_HPP_
#define PARSER_HPP_

// http_mp
#include "http_mp/method.hpp"

// googletest
#include <gtest/gtest.h>

// stl
#include <iostream>
#include <string>
#include <utility>

using namespace http_mp;

namespace std {
std::ostream &operator<<(std::ostream &out, const Method value) {
  switch (value) {
  case Method::ACL:
    return out << "Method::ACL";
  case Method::BASELINE_CONTROL:
    return out << "Method::BASELINE_CONTROL";
  case Method::BIND:
    return out << "Method::BIND";
  case Method::CHECKIN:
    return out << "Method::CHECKIN";
  case Method::CONNECT:
    return out << "Method::CONNECT";
  case Method::COPY:
    return out << "Method::COPY";
  case Method::DELETE:
    return out << "Method::DELETE";
  case Method::GET:
    return out << "Method::GET";
  case Method::HEAD:
    return out << "Method::HEAD";
  case Method::LABEL:
    return out << "Method::LABEL";
  case Method::LINK:
    return out << "Method::LINK";
  case Method::LOCK:
    return out << "Method::LOCK";
  case Method::MERGE:
    return out << "Method::MERGE";
  case Method::MKACTIVITY:
    return out << "Method::MKACTIVITY";
  case Method::MKCALENDAR:
    return out << "Method::MKCALENDAR";
  case Method::MKCOL:
    return out << "Method::MKCOL";
  case Method::MKREDIRECTREF:
    return out << "Method::MKREDIRECTREF";
  case Method::MKWORKSPACE:
    return out << "Method::MKWORKSPACE";
  case Method::MOVE:
    return out << "Method::MOVE";
  case Method::OPTIONS:
    return out << "Method::OPTIONS";
  case Method::ORDERPATCH:
    return out << "Method::ORDERPATCH";
  case Method::PATCH:
    return out << "Method::PATCH";
  case Method::POST:
    return out << "Method::POST";
  case Method::PRI:
    return out << "Method::PRI";
  case Method::PROPFIND:
    return out << "Method::PROPFIND";
  case Method::PROPPATCH:
    return out << "Method::PROPPATCH";
  case Method::PUT:
    return out << "Method::PUT";
  case Method::REBIND:
    return out << "Method::REBIND";
  case Method::REPORT:
    return out << "Method::REPORT";
  case Method::SEARCH:
    return out << "Method::SEARCH";
  case Method::TRACE:
    return out << "Method::Trace";
  case Method::UNBIND:
    return out << "Method::UNBIND";
  case Method::UNCHECKOUT:
    return out << "Method::UNCHECKOUT";
  case Method::UNLINK:
    return out << "Method::UNLINK";
  case Method::UNLOCK:
    return out << "Method::UNLOCK";
  case Method::UPDATE:
    return out << "Method::UPDATE";
  case Method::UPDATEREDIRECTREF:
    return out << "Method::UPDATEREDIRECTREF";
  case Method::VERSION_CONTROL:
    return out << "Method::VERSION_CONTROL";
  }
  return out;
}

void PrintTo(const std::pair<const char *, Method> &pair, std::ostream *os) {
  *os << "[" << pair.first << ", " << pair.second << "]";
}
} // namespace std

class ParserMethodTest
    : public testing::TestWithParam<std::pair<const char *, Method>> {};

INSTANTIATE_TEST_SUITE_P(
    Methods, ParserMethodTest,
    testing::Values(
        std::pair("ACL ", Method::ACL),
        std::pair("BASELINE-CONTROL ", Method::BASELINE_CONTROL),
        std::pair("BIND ", Method::BIND),
        std::pair("CHECKIN ", Method::CHECKIN),
        std::pair("CHECKOUT ", Method::CHECKOUT),
        std::pair("CONNECT ", Method::CONNECT),
        std::pair("COPY ", Method::COPY), std::pair("DELETE ", Method::DELETE),
        std::pair("GET ", Method::GET), std::pair("HEAD ", Method::HEAD),
        std::pair("LABEL ", Method::LABEL), std::pair("LINK ", Method::LINK),
        std::pair("LOCK ", Method::LOCK), std::pair("MERGE ", Method::MERGE),
        std::pair("MKACTIVITY ", Method::MKACTIVITY),
        std::pair("MKCALENDAR ", Method::MKCALENDAR),
        std::pair("MKCOL ", Method::MKCOL),
        std::pair("MKREDIRECTREF ", Method::MKREDIRECTREF),
        std::pair("MKWORKSPACE ", Method::MKWORKSPACE),
        std::pair("MOVE ", Method::MOVE),
        std::pair("OPTIONS ", Method::OPTIONS),
        std::pair("ORDERPATCH ", Method::ORDERPATCH),
        std::pair("PATCH ", Method::PATCH), std::pair("POST ", Method::POST),
        std::pair("PRI ", Method::PRI),
        std::pair("PROPFIND ", Method::PROPFIND),
        std::pair("PROPPATCH ", Method::PROPPATCH),
        std::pair("PUT ", Method::PUT), std::pair("REBIND ", Method::REBIND),
        std::pair("REPORT ", Method::REPORT),
        std::pair("SEARCH ", Method::SEARCH),
        std::pair("TRACE ", Method::TRACE),
        std::pair("UNBIND ", Method::UNBIND),
        std::pair("UNCHECKOUT ", Method::UNCHECKOUT),
        std::pair("UNLINK ", Method::UNLINK),
        std::pair("UNLOCK ", Method::UNLOCK),
        std::pair("UPDATE ", Method::UPDATE),
        std::pair("UPDATEREDIRECTREF ", Method::UPDATEREDIRECTREF),
        std::pair("VERSION-CONTROL ", Method::VERSION_CONTROL)));

#endif // PARSER_HPP_
