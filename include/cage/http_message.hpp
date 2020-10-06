/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP message.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_HTTP_MESSAGE_HPP_
#define CAGE_HTTP_MESSAGE_HPP_

#include <cstddef>
#include <string>
#include "cage/http_header.hpp"

namespace cage {

class HttpMessage {
 public:
  virtual ~HttpMessage() = default;
  HttpMessage(HttpMessage const &) = default;
  HttpMessage(HttpMessage &&) = default;
  HttpMessage &operator=(HttpMessage const &) = default;
  HttpMessage &operator=(HttpMessage &&other) = default;

  HttpMessage(int version = 11);

  bool Chunked() const;
  void Chunked(bool chunked);

  bool HasContentLength() const;
  void ContentLength();
  void ContentLength(std::size_t content_length);

  bool KeepAlive() const;
  void KeepAlive(bool keep_alive);

  int Version() const;
  void Version(int version);

  bool NeedEof() const;

  std::string const &Body() const;
  void Body(std::string const &body);
  void Body(std::string &&body);

  std::string const &Get(HttpField key) const;
  void Set(HttpField key, std::string const &value);
  void Set(HttpField key, std::string &&value);

  HttpHeader const &Header() const;
  void Header(HttpHeader const &header);
  void Header(HttpHeader header);

 private:
  int version_;
  HttpHeader header_;
  std::string body_;
};

}  // namespace cage

#endif  // CAGE_HTTP_MESSAGE_HPP_
