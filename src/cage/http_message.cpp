/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP message.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/http_message.hpp"

namespace cage {

HttpMessage::HttpMessage(int version) : version_(version) {
}

bool HttpMessage::Chunked() const {
}

void HttpMessage::Chunked(bool chunked) {
}

bool HttpMessage::HasContentLength() const {
  auto it = header_.find(HttpField::content_length);
  return it != header_.end();
}

void HttpMessage::ContentLength() {
  header_.erase(HttpField::content_length);
}

void HttpMessage::ContentLength(std::size_t content_length) {
  header_.insert_or_assign(HttpField::content_length,
                           std::to_string(content_length));
}

bool HttpMessage::KeepAlive() const {
  auto it = header_.find(HttpField::connection);
  if (version_ < 11) {
    if (it == header_.end()) {
      return false;
    }
  }
  it = header_.find(HttpField::keep_alive);
  if (it == header_.end()) {
    return true;
  }

  it = header_.find(HttpField::close);
  return it == header_.end();
}

void HttpMessage::KeepAlive(bool keep_alive) {
}

int HttpMessage::Version() const {
  return version_;
}

void HttpMessage::Version(int version) {
  version_ = version;
}

std::string const &HttpMessage::Body() const {
  return body_;
}

void HttpMessage::Body(std::string const &body) {
  body_ = body;
}

void HttpMessage::Body(std::string &&body) {
  body_ = std::move(body);
}

std::string const &HttpMessage::Get(HttpField key) const {
  return header_.at(key);
}

void HttpMessage::Set(HttpField key, std::string const &value) {
  header_[key] = value;
}

void HttpMessage::Set(HttpField key, std::string &&value) {
  header_[key] = std::move(value);
}

HttpHeader const &HttpMessage::Header() const {
  return header_;
}

void HttpMessage::Header(HttpHeader const &header) {
  header_ = header;
}

void HttpMessage::Header(HttpHeader header) {
  header_ = std::move(header);
}

}  // namespace cage
