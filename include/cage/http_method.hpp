/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP method.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_HTTP_METHOD_HPP_
#define CAGE_HTTP_METHOD_HPP_

#include <cstdint>
#include <ostream>
#include <string>

namespace cage {

enum class HttpMethod : std::uint16_t {
  unknown = 0,
  delete_,
  get,
  head,
  post,
  put,
  connect,
  options,
  trace,
  max
};

constexpr HttpMethod operator++(HttpMethod& x) {
  return x = static_cast<HttpMethod>(static_cast<std::uint16_t>(x) + 1);
}

constexpr HttpMethod operator*(HttpMethod x) {
  return x;
}

constexpr HttpMethod begin(HttpMethod) {
  return HttpMethod::unknown;
}

constexpr HttpMethod end(HttpMethod) {
  return HttpMethod::max;
}

std::string HttpMethodToString(HttpMethod method);

HttpMethod HttpStringToMethod(std::string method_string);

std::ostream& operator<<(std::ostream& os, HttpMethod method);

}  // namespace cage

#endif  // CAGE_HTTP_METHOD_HPP_
