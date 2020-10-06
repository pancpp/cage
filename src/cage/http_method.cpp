/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP method.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/http_method.hpp"
#include <algorithm>
#include <array>
#include <cctype>
#include <string>
#include <unordered_map>

namespace cage {
namespace {
inline void ToLowerInplace(std::string& s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

struct MethodMap {
  std::array<std::string, static_cast<std::uint16_t>(HttpMethod::max)>
      method_string_array;
  std::unordered_map<std::string, HttpMethod> method_string_map;

  MethodMap()
      : method_string_array{
            "DELETE", "GET",     "HEAD",    "POST",
            "PUT",    "CONNECT", "OPTIONS", "TRACE",
        } {
    for (auto method : HttpMethod()) {
      auto s = method_string_array[static_cast<std::uint16_t>(method)];
      ToLowerInplace(s);
      method_string_map.insert({s, method});
    }
  }
};
MethodMap g_method_map;
}  // namespace

std::string HttpMethodToString(HttpMethod method) {
  return g_method_map.method_string_array.at(
      static_cast<std::uint16_t>(method));
}

HttpMethod HttpStringToMethod(std::string method_string) {
  ToLowerInplace(method_string);
  return g_method_map.method_string_map.at(method_string);
}

std::ostream& operator<<(std::ostream& os, HttpMethod method) {
  return os << HttpMethodToString(method);
}

}  // namespace cage
