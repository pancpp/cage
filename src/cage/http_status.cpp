/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP status.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/http_status.hpp"

namespace cage {

std::string HttpStatusToString(HttpStatus status) {
  switch (status) {
    // 1xx
    case HttpStatus::continue_:
      return "Continue";
    case HttpStatus::switching_protocols:
      return "Switching Protocols";
    case HttpStatus::processing:
      return "Processing";

    // 2xx
    case HttpStatus::ok:
      return "OK";
    case HttpStatus::created:
      return "Created";
    case HttpStatus::accepted:
      return "Accepted";
    case HttpStatus::non_authoritative_information:
      return "Non-Authoritative Information";
    case HttpStatus::no_content:
      return "No Content";
    case HttpStatus::reset_content:
      return "Reset Content";
    case HttpStatus::partial_content:
      return "Partial Content";
    case HttpStatus::multi_status:
      return "Multi-Status";
    case HttpStatus::already_reported:
      return "Already Reported";
    case HttpStatus::im_used:
      return "IM Used";

    // 3xx
    case HttpStatus::multiple_choices:
      return "Multiple Choices";
    case HttpStatus::moved_permanently:
      return "Moved Permanently";
    case HttpStatus::found:
      return "Found";
    case HttpStatus::see_other:
      return "See Other";
    case HttpStatus::not_modified:
      return "Not Modified";
    case HttpStatus::use_proxy:
      return "Use Proxy";
    case HttpStatus::temporary_redirect:
      return "Temporary Redirect";
    case HttpStatus::permanent_redirect:
      return "Permanent Redirect";

    // 4xx
    case HttpStatus::bad_request:
      return "Bad Request";
    case HttpStatus::unauthorized:
      return "Unauthorized";
    case HttpStatus::payment_required:
      return "Payment Required";
    case HttpStatus::forbidden:
      return "Forbidden";
    case HttpStatus::not_found:
      return "Not Found";
    case HttpStatus::method_not_allowed:
      return "Method Not Allowed";
    case HttpStatus::not_acceptable:
      return "Not Acceptable";
    case HttpStatus::proxy_authentication_required:
      return "Proxy Authentication Required";
    case HttpStatus::request_timeout:
      return "Request Timeout";
    case HttpStatus::conflict:
      return "Conflict";
    case HttpStatus::gone:
      return "Gone";
    case HttpStatus::length_required:
      return "Length Required";
    case HttpStatus::precondition_failed:
      return "Precondition Failed";
    case HttpStatus::payload_too_large:
      return "Payload Too Large";
    case HttpStatus::uri_too_long:
      return "URI Too Long";
    case HttpStatus::unsupported_media_type:
      return "Unsupported Media Type";
    case HttpStatus::range_not_satisfiable:
      return "Range Not Satisfiable";
    case HttpStatus::expectation_failed:
      return "Expectation Failed";
    case HttpStatus::misdirected_request:
      return "Misdirected Request";
    case HttpStatus::unprocessable_entity:
      return "Unprocessable Entity";
    case HttpStatus::locked:
      return "Locked";
    case HttpStatus::failed_dependency:
      return "Failed Dependency";
    case HttpStatus::upgrade_required:
      return "Upgrade Required";
    case HttpStatus::precondition_required:
      return "Precondition Required";
    case HttpStatus::too_many_requests:
      return "Too Many Requests";
    case HttpStatus::request_header_fields_too_large:
      return "Request Header Fields Too Large";
    case HttpStatus::connection_closed_without_response:
      return "Connection Closed Without Response";
    case HttpStatus::unavailable_for_legal_reasons:
      return "Unavailable For Legal Reasons";
    case HttpStatus::client_closed_request:
      return "Client Closed Request";
    // 5xx
    case HttpStatus::internal_server_error:
      return "Internal Server Error";
    case HttpStatus::not_implemented:
      return "Not Implemented";
    case HttpStatus::bad_gateway:
      return "Bad Gateway";
    case HttpStatus::service_unavailable:
      return "Service Unavailable";
    case HttpStatus::gateway_timeout:
      return "Gateway Timeout";
    case HttpStatus::http_version_not_supported:
      return "HTTP Version Not Supported";
    case HttpStatus::variant_also_negotiates:
      return "Variant Also Negotiates";
    case HttpStatus::insufficient_storage:
      return "Insufficient Storage";
    case HttpStatus::loop_detected:
      return "Loop Detected";
    case HttpStatus::not_extended:
      return "Not Extended";
    case HttpStatus::network_authentication_required:
      return "Network Authentication Required";
    case HttpStatus::network_connect_timeout_error:
      return "Network Connect Timeout Error";

    default:
      break;
  }
  return "<unknown-status>";
}

std::ostream& operator<<(std::ostream& os, HttpStatus status) {
  os << HttpStatusToString(status);
}

}  // namespace cage
