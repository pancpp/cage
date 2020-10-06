/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP response.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/http_response.hpp"

namespace cage {

HttpResponse::HttpResponse(HttpStatus status, int version)
    : HttpMessage{version},
      status_{status},
      reason_{HttpStatusToString(status)} {
}

HttpStatus HttpResponse::Status() const {
  return status_;
}

void HttpResponse::Status(HttpStatus status) {
  status_ = status;
  reason_ = HttpStatusToString(status);
}

std::string const& HttpResponse::Reason() const {
  return reason_;
}

bool HttpResponse::NeedEof() const {
  if (status_ == HttpStatus::no_content ||
      status_ == HttpStatus::not_modified || status_ == HttpStatus::continue_ ||
      status_ == HttpStatus::switching_protocols ||
      status_ == HttpStatus::processing || HasContentLength() || Chunked()) {
    return !KeepAlive();
  }

  return true;
}

}  // namespace cage
