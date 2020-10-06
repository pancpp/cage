/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP request.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_HTTP_REQUEST_HPP_
#define CAGE_HTTP_REQUEST_HPP_

#include <memory>
#include "cage/http_message.hpp"
#include "cage/http_method.hpp"

namespace cage {

class HttpRequest : public HttpMessage {
 public:
  using SelfPtr = std::shared_ptr<HttpRequest>;

 public:
  ~HttpRequest() = default;
  HttpRequest() = default;
  HttpRequest(HttpRequest const &) = default;
  HttpRequest(HttpRequest &&) = default;
  HttpRequest &operator=(HttpRequest const &) = default;
  HttpRequest &operator=(HttpRequest &&other) = default;

  explicit HttpRequest(HttpMethod method, std::string path, int version = 11);

  HttpMethod Method() const;
  void Method(HttpMethod method);

  std::string const &MethodString() const;
  void MethodString(std::string const &method_string);
  void MethodString(std::string method_string);

  std::string const &Path() const;
  void Path(std::string const &path);
  void Path(std::string path);

 private:
  HttpMethod method_;
  std::string method_string_;
  std::string path_;
};

}  // namespace cage

#endif  // CAGE_HTTP_REQUEST_HPP_
