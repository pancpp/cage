/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP and WEBSOCKET controller.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/controller.hpp"

namespace cage {

void Controller::RegisterRouter(RouterPtr p_router) {
  router_vec_.push_back(std::move(p_router));
}

Controller::HttpViewPtr Controller::GetHttpView(std::string const& target) {
  std::string url = ParseUrl(target);
  for (auto& p_router : router_vec_) {
    auto p_view = p_router->GetHttpView(url);
    if (p_view) {
      return p_view;
    }
  }

  return nullptr;
}

Controller::WebsockViewPtr Controller::MakeWebsockView(HttpRequest request,
                                                       SenderType sender,
                                                       CloserType closer) {
  std::string url = ParseUrl(
      std::string_view(request.target().data(), request.target().size()));

  for (auto& p_router : router_vec_) {
    auto view_maker = p_router->GetWebsockViewMaker(url);
    if (view_maker) {
      return view_maker(std::move(request), std::move(sender),
                        std::move(closer));
    }
  }
  return nullptr;
}

std::string Controller::ServerName() {
  return "BeastInCage/0.0.1";
}

std::size_t Controller::WebsockMsgQueCap() {
  return 1024;
}

std::chrono::seconds Controller::SocketTimeout() {
  return std::chrono::seconds(30);
}

std::size_t Controller::HttpHeadLimit() {
  return 8 * 1024;
}

std::size_t Controller::HttpBodyLimit() {
  return 1024 * 1024;
}

std::string Controller::ParseUrl(std::string_view target) {
  return std::string(target.data(), target.size());
}

}  // namespace cage
