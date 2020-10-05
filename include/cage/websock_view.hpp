/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Abstract websocket viewer.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_WEBSOCK_VIEW_HPP_
#define CAGE_WEBSOCK_VIEW_HPP_

#include "cage/http.hpp"
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <system_error>

namespace cage {

class WebsockView {
public:
  using SelfPtr = std::shared_ptr<WebsockView>;
  using SenderType = std::function<void(std::string_view msg, bool is_txt)>;
  using CloserType = std::function<void()>;

public:
  virtual ~WebsockView() = default;
  explicit WebsockView(HttpRequest request, SenderType sender,
                       CloserType closer);

  void Send(std::string_view msg, bool is_txt = true);
  void Close();

  virtual void OnReceive(std::string_view msg, bool is_txt) = 0;
  virtual void OnError(std::error_code ec) = 0;
  virtual void OnClose(std::error_code ec) = 0;

  virtual HttpRequest const &GetHttpRequest() const;

private:
  HttpRequest request_;
  SenderType sender_;
  CloserType closer_;
};

} // namespace cage

#endif // CAGE_WEBSOCK_VIEW_HPP_
