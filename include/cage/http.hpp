/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP request and response.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_HTTP_HPP_
#define CAGE_HTTP_HPP_

#include "boost/beast/http/message.hpp"
#include "boost/beast/http/string_body.hpp"
#include <memory>

namespace cage {

using HttpRequest =
    boost::beast::http::request<boost::beast::http::string_body>;

using HttpRequestPtr = std::shared_ptr<HttpRequest>;

using HttpResponse =
    boost::beast::http::response<boost::beast::http::string_body>;

using HttpResponsePtr = std::shared_ptr<HttpResponse>;

} // namespace cage

#endif // CAGE_HTTP_HPP_
