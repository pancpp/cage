/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @file
 * @brief HTTP response.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_HTTP_RESPONSE_HPP_
#define CAGE_HTTP_RESPONSE_HPP_

#include <memory>
#include "cage/http_message.hpp"
#include "cage/http_status.hpp"

namespace cage {

class HttpResponse : public HttpMessage {
 public:
  using SelfPtr = std::shared_ptr<HttpResponse>;

 public:
  ~HttpResponse() = default;
  HttpResponse() = default;
  HttpResponse(HttpResponse const&) = default;
  HttpResponse(HttpResponse&&) = default;
  HttpResponse& operator=(HttpResponse const&) = default;
  HttpResponse& operator=(HttpResponse&&) = default;

  explicit HttpResponse(HttpStatus status, int version = 11);

  HttpStatus Status() const;
  void Status(HttpStatus status);
  std::string Reason() const;

  bool NeedEof() const;

 private:
  HttpStatus status_;
};

}  // namespace cage

#endif  // CAGE_HTTP_RESPONSE_HPP_
