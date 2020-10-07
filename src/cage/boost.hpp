/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief boost namespace definition.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_BOOST_HPP_
#define CAGE_BOOST_HPP_

#include "boost/asio.hpp"
#include "cage/beast.hpp"

namespace cage {

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

}  // namespace cage

#endif  // CAGE_BOOST_HPP_
