/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP and WEBSOCKET controller.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_CONTROLLER_HPP_
#define CAGE_CONTROLLER_HPP_

#include "cage/http_view.hpp"
#include "cage/websock_view.hpp"
#include <chrono>
#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

namespace cage {

class Controller {
public:
  using SelfPtr = std::shared_ptr<Controller>;
  using HttpViewPtr = HttpView::SelfPtr;
  using WebsockViewPtr = WebsockView::SelfPtr;
  using SenderType = WebsockView::SenderType;
  using CloserType = WebsockView::CloserType;

  using HttpViewMaker = std::function<HttpViewPtr()>;
  using HttpViewMakerMap = std::unordered_map<std::string, HttpViewMaker>;
  using HttpViewMap = std::unordered_map<std::string, HttpViewPtr>;
  using WebsockViewMaker =
      std::function<WebsockViewPtr(HttpRequest, SenderType, CloserType)>;
  using WebsockViewMakerMap = std::unordered_map<std::string, WebsockViewMaker>;

public:
  virtual ~Controller() = default;
  Controller() = default;

  virtual HttpViewPtr GetHttpView(std::string url);
  virtual WebsockViewPtr MakeWebsockView(HttpRequest request, SenderType sender,
                                         CloserType closer);

  virtual std::string ServerName();
  virtual std::size_t WebsockMsgQueCap();

  virtual std::chrono::seconds SocketTimeout();
  virtual std::size_t HttpHeadLimit();
  virtual std::size_t HttpBodyLimit();

  virtual void RegisterViewMaker(std::string url, HttpViewMaker view_maker);
  virtual void RegisterViewMaker(std::string url, WebsockViewMaker view_maker);

private:
  HttpViewMakerMap http_view_maker_map_;
  WebsockViewMakerMap websock_view_maker_map_;

  HttpViewMap http_view_map_;
};

} // namespace cage

#endif // CAGE_CONTROLLER_HPP_
