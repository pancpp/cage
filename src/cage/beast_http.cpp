/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Conversion between beast http and cage http messages.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */

#include "cage/beast_http.hpp"
#include <string>
#include "cage/http_method.hpp"

namespace cage {

inline HttpRequest BeastRequestToHttpImpl(BeastRequest const& beast_request) {
  HttpRequest http_request;

  http_request.Version(beast_request.version());
  http_request.Method(static_cast<HttpMethod>(beast_request.method()));
  http_request.Path(std::string(beast_request.target().data(),
                                beast_request.target().size()));

  return http_request;
}

HttpRequest BeastRequestToHttp(BeastRequest const& beast_request) {
  HttpRequest http_request = BeastRequestToHttpImpl(beast_request);
  http_request.Body(beast_request.body());
  return http_request;
}

HttpRequest BeastRequestToHttp(BeastRequest&& beast_request) {
  HttpRequest http_request = BeastRequestToHttpImpl(beast_request);
  http_request.Body(std::move(beast_request.body()));
  return http_request;
}

BeastResponse HttpResponseToBeastImpl(HttpResponse const& http_response) {
  BeastResponse beast_response{
      static_cast<http::status>(http_response.Status()),
      http_response.Version()};
  return beast_response;
}

BeastResponse HttpResponseToBeast(HttpResponse const& http_response) {
  BeastResponse beast_response = HttpResponseToBeastImpl(http_response);
  beast_response.body() = http_response.Body();
  return beast_response;
}

BeastResponse HttpResponseToBeast(HttpResponse&& http_response) {
  BeastResponse beast_response = HttpResponseToBeastImpl(http_response);
  beast_response.body() = std::move(http_response.Body());
  return beast_response;
}

}  // namespace cage
