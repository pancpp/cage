/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Abstract HTTP view.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/http_view.hpp"
#include "cage/beast.hpp"
#include "cage/beast_http.hpp"
#include "cage/http_status.hpp"

namespace cage {

HttpView::~HttpView() {
}

HttpResponse HttpView::Get(HttpRequest const &request) {
  return BadRequest(request, "HTTP method GET not supported");
}

HttpResponse HttpView::Head(HttpRequest const &request) {
  return BadRequest(request, "HTTP method HEAD not supported");
}

HttpResponse HttpView::Post(HttpRequest const &request) {
  return BadRequest(request, "HTTP method POST not supported");
}

HttpResponse HttpView::Put(HttpRequest const &request) {
  return BadRequest(request, "HTTP method PUT not supported");
}

HttpResponse HttpView::BadRequest(HttpRequest const &request,
                                  std::string &&msg) {
  HttpResponse response{HttpStatus::bad_request, request.Version()};
  response.Set(HttpField::content_type, "text/plain");
  response.Body(std::move(msg));

  return response;
}

}  // namespace cage
