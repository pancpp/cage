/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Conversion between beast http and cage http messages.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_BEAST_HTTP_HPP_
#define CAGE_BEAST_HTTP_HPP_

#include "cage/beast.hpp"
#include "cage/http_request.hpp"
#include "cage/http_response.hpp"

namespace cage {

BeastRequest HttpRequestToBeast(HttpRequest const& http_request);
BeastRequest HttpRequestToBeast(HttpRequest&& http_request);

HttpRequest BeastRequestToHttp(BeastRequest const& beast_request);
HttpRequest BeastRequestToHttp(BeastRequest&& beast_request);

BeastResponse HttpResponseToBeast(HttpResponse const& http_response);
BeastResponse HttpResponseToBeast(HttpResponse&& http_response);

HttpResponse BeastResponseToHttp(BeastResponse const& beast_response);
HttpResponse BeastResponseToHttp(BeastResponse&& beast_response);

}  // namespace cage

#endif  // CAGE_BEAST_HTTP_HPP_
