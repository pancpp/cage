/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief boost::asio and boost::beast namespace definition.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_BOOST_BEAST_HPP_
#define CAGE_BOOST_BEAST_HPP_

#include "boost/asio.hpp"
#include "boost/beast.hpp"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;
using BeastRequest = http::request<http::string_body>;
using BeastResponse = http::response<http::string_body>;

#endif  // CAGE_BOOST_BEAST_HPP_
