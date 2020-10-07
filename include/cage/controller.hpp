/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP and WEBSOCKET controller.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_CONTROLLER_HPP_
#define CAGE_CONTROLLER_HPP_

#include <chrono>
#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include "cage/http_view.hpp"
#include "cage/router.hpp"
#include "cage/websock_view.hpp"

namespace cage {

class Controller {
 public:
  using SelfPtr = std::shared_ptr<Controller>;

  using RouterPtr = Router::SelfPtr;
  using HttpViewPtr = HttpView::SelfPtr;
  using WebsockViewPtr = WebsockView::SelfPtr;
  using SenderType = WebsockView::SenderType;
  using CloserType = WebsockView::CloserType;

 public:
  virtual ~Controller() = default;
  Controller() = default;

  virtual void RegisterRouter(RouterPtr p_router);

  virtual HttpViewPtr GetHttpView(std::string const& target);
  virtual WebsockViewPtr MakeWebsockView(HttpRequest request, SenderType sender,
                                         CloserType closer);

  virtual std::string ServerName();
  virtual std::size_t WebsockMsgQueCap();

  virtual std::chrono::seconds SocketTimeout();
  virtual std::size_t HttpHeadLimit();
  virtual std::size_t HttpBodyLimit();

 protected:
  std::string ParseUrl(std::string_view target);

 private:
  std::vector<RouterPtr> router_vec_;
};

}  // namespace cage

#endif  // CAGE_CONTROLLER_HPP_
