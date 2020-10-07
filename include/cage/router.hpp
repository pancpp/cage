/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP and websocket URL router.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_ROUTER_HPP_
#define CAGE_ROUTER_HPP_

#include <functional>
#include <memory>
#include <regex>
#include <tuple>
#include <vector>
#include "cage/http_request.hpp"
#include "cage/http_view.hpp"
#include "cage/websock_view.hpp"

namespace cage {

class Router {
 public:
  using SelfPtr = std::shared_ptr<Router>;

  using HttpViewPtr = HttpView::SelfPtr;
  using WebsockViewPtr = WebsockView::SelfPtr;

  using HttpViewMaker = std::function<HttpViewPtr()>;
  using WebsockViewMaker = std::function<WebsockViewPtr(
      HttpRequest, WebsockView::SenderType, WebsockView::CloserType)>;

  using HttpMakerRoute = std::tuple<std::regex, HttpViewMaker>;
  using WebsockMakerRoute = std::tuple<std::regex, WebsockViewMaker>;

  using HttpViewRoute = std::tuple<std::regex, HttpViewPtr>;

  using HttpViewMakerOpt = std::optional<HttpViewMaker>;
  using WebsockViewMakerOpt = std::optional<WebsockViewMaker>;

 public:
  virtual ~Router() = default;

  virtual void RegisterPath(std::string const& regex_path,
                            HttpViewMaker http_view_maker);
  virtual void RegisterPath(std::string const& regex_path,
                            WebsockViewMaker websock_view_maker);

  virtual HttpViewMaker GetHttpViewMaker(std::string const& path) const;
  virtual WebsockViewMaker GetWebsockViewMaker(std::string const& path) const;

  virtual HttpViewPtr GetHttpView(std::string const& path);

 private:
  std::vector<HttpMakerRoute> http_maker_routes_;
  std::vector<WebsockMakerRoute> websock_maker_routes_;

  std::vector<HttpViewRoute> http_view_route_;
};

}  // namespace cage

#endif  // CAGE_ROUTER_HPP_
