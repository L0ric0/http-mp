#ifndef HTTP_MP__REQUEST_HPP_
#define HTTP_MP__REQUEST_HPP_

// http-mp
#include "http_mp/method.hpp"

namespace http_mp {

struct Request {
  Method method;

  bool operator==(const Request &request) const = default;
};

} // namespace http_mp

#endif // HTTP_MP__REQUEST_HPP_
