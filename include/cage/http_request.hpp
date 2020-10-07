/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Conversion between beast http and cage http messages.
 * @author Leyuan Pan
 * @date Oct 06, 2020
 */
#ifndef CAGE_HTTP_REQUEST_HPP_
#define CAGE_HTTP_REQUEST_HPP_

#include "boost/beast/http/message.hpp"
#include "boost/beast/http/string_body.hpp"

namespace cage {

using HttpRequest =
    boost::beast::http::request<boost::beast::http::string_body>;

}  // namespace cage

#endif  // CAGE_HTTP_REQUEST_HPP_
