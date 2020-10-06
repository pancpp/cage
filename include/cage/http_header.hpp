/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP header.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_HTTP_HEADER_HPP_
#define CAGE_HTTP_HEADER_HPP_

#include <unordered_map>
#include "cage/http_field.hpp"

namespace cage {

using HttpHeader = std::unordered_map<HttpField, std::string>;

}  // namespace cage

#endif  // CAGE_HTTP_HEADER_HPP_
