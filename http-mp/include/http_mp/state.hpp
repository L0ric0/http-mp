#ifndef HTTP_MP__STATE_HPP_
#define HTTP_MP__STATE_HPP_

namespace http_mp {

enum class State {
  Start,
  H_req_resp,
  HTTP_resp,
  ACL_req,
  B_req,
  BASELINE_CONTROL_req,
  BIND_req,
  C_req,
  CHECK_req,
  CHECKIN_req,
  CHECKOUT_req,
  CO_req,
  CONNECT_req,
  COPY_req,
  DELETE_req,
  GET_req,
  HEAD_req,
  L_req,
  LABEL_req,
  LINK_req,
  LOCK_req,
  M_req,
  MERGE_req,
  MK_req,
  MKACTIVITY_req,
  MKC_req,
  MKCALENDAR_req,
  MKCOL_req,
  MKREDIRECTREF_req,
  MKWORKSPACE_req,
  MOVE_req,
  O_req,
  OPTIONS_req,
  ORDERPATCH_req,
  P_req,
  PATCH_req,
  POST_req,
  PR_req,
  PRI_req,
  PROP_req,
  PUT_req,
  PROPFIND_req,
  PROPPATCH_req,
  RE_req,
  REBIND_req,
  REPORT_req,
  SEARCH_req,
  TRACE_req,
  U_req,
  UN_req,
  UNL_req,
  UNBIND_req,
  UNCHECKOUT_req,
  UNLINK_req,
  UNLOCK_req,
  UPDATE_req,
  UPDATE_2_req,
  UPDATEREDIRECTREF_req,
  VERSION_CONTROL_req,
  METHOD_SP,
};

}

#endif // HTTP_MP__STATE_HPP_