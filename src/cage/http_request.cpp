/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP request.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/http_request.hpp"

namespace cage {

HttpRequest::HttpRequest(HttpMethod method, std::string path, int version)
    : HttpMessage{version},
      method_{method},
      method_string_{HttpMethodToString(method)},
      path_{std::move(path)} {
}

HttpMethod HttpRequest::Method() const {
  return method_;
}

void HttpRequest::Method(HttpMethod method) {
  method_ = method;
  method_string_ = HttpMethodToString(method);
}

std::string const &HttpRequest::MethodString() const {
  return method_string_;
}

void HttpRequest::MethodString(std::string const &method_string) {
  method_ = HttpStringToMethod(method_string);
  method_string_ = method_string;
}

void HttpRequest::MethodString(std::string method_string) {
  method_ = HttpStringToMethod(method_string);
  method_string_ = std::move(method_string);
}

std::string const &HttpRequest::Path() const {
  return path_;
}

void HttpRequest::Path(std::string const &path) {
  path_ = path;
}

void HttpRequest::Path(std::string &&path) {
  path_ = std::move(path);
}

}  // namespace cage
