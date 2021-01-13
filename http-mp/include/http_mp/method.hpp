#ifndef HTTP_MP__METHOD_HPP
#define HTTP_MP__METHOD_HPP

namespace http_mp {

enum class Method {
  ACL,
  BASELINE_CONTROL,
  BIND,
  CHECKIN,
  CHECKOUT,
  CONNECT,
  COPY,
  DELETE,
  GET,
  HEAD,
  LABEL,
  LINK,
  LOCK,
  MERGE,
  MKACTIVITY,
  MKCALENDAR,
  MKCOL,
  MKREDIRECTREF,
  MKWORKSPACE,
  MOVE,
  OPTIONS,
  ORDERPATCH,
  PATCH,
  POST,
  PRI,
  PROPFIND,
  PROPPATCH,
  PUT,
  REBIND,
  REPORT,
  SEARCH,
  TRACE,
  UNBIND,
  UNCHECKOUT,
  UNLINK,
  UNLOCK,
  UPDATE,
  UPDATEREDIRECTREF,
  VERSION_CONTROL,
};

}

#endif // HTTP_MP__METHOD_HPP
