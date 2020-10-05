/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP and WEBSOCKET controller.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/controller.hpp"

namespace cage {

Controller::HttpViewPtr Controller::GetHttpView(std::string url) {
  auto it = http_view_map_.find(url);
  if (it != http_view_map_.end()) {
    return it->second;
  }

  // Create a new http view instance
  auto it2 = http_view_maker_map_.find(url);
  if (it2 == http_view_maker_map_.end()) {
    return nullptr;
  }

  auto p_view = it2->second();
  http_view_map_.insert({url, p_view});

  return p_view;
}

Controller::WebsockViewPtr Controller::MakeWebsockView(HttpRequest request,
                                                       SenderType sender,
                                                       CloserType closer) {
  std::string url(request.target().data(), request.target().size());
  auto it = websock_view_maker_map_.find(url);
  if (it == websock_view_maker_map_.end()) {
    return nullptr;
  }
  return it->second(std::move(request), std::move(sender), std::move(closer));
}

std::string Controller::ServerName() { return "Beast in Cage"; }

std::size_t Controller::WebsockMsgQueCap() { return 1024; }

std::chrono::seconds Controller::SocketTimeout() {
  return std::chrono::seconds(30);
}

std::size_t Controller::HttpHeadLimit() { return 8 * 1024; }

std::size_t Controller::HttpBodyLimit() { return 1024 * 1024; }

void Controller::RegisterViewMaker(std::string url, HttpViewMaker view_maker) {
  http_view_maker_map_[url] = view_maker;
}

void Controller::RegisterViewMaker(std::string url,
                                   WebsockViewMaker view_maker) {
  websock_view_maker_map_[url] = view_maker;
}

} // namespace cage
