/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP and websocket URL router.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/router.hpp"

namespace cage {

void Router::RegisterPath(std::string const& regex_path,
                          HttpViewMaker http_view_maker) {
  std::regex r(regex_path, std::regex::ECMAScript | std::regex::icase);
  http_maker_routes_.push_back(std::tuple(r, std::move(http_view_maker)));
  http_view_route_.push_back(std::tuple(r, http_view_maker()));
}

void Router::RegisterPath(std::string const& regex_path,
                          WebsockViewMaker websock_view_maker) {
  std::regex r(regex_path, std::regex::ECMAScript | std::regex::icase);
  websock_maker_routes_.push_back(
      std::tuple(std::move(r), std::move(websock_view_maker)));
}

Router::HttpViewMaker Router::GetHttpViewMaker(std::string const& path) const {
  for (auto& view_maker : http_maker_routes_) {
    if (std::regex_match(path, std::get<0>(view_maker))) {
      return std::get<1>(view_maker);
    }
  }

  return HttpViewMaker();
}

Router::WebsockViewMaker Router::GetWebsockViewMaker(
    std::string const& path) const {
  for (auto& view_maker : websock_maker_routes_) {
    if (std::regex_match(path, std::get<0>(view_maker))) {
      return std::get<1>(view_maker);
    }
  }

  return WebsockViewMaker();
}

Router::HttpViewPtr Router::GetHttpView(std::string const& path) {
  for (auto& view : http_view_route_) {
    if (std::regex_match(path, std::get<0>(view))) {
      return std::get<1>(view);
    }
  }

  return nullptr;
}

}  // namespace cage
