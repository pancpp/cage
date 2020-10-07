/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Websocket session.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_WEBSOCK_SESSION_HPP_
#define CAGE_WEBSOCK_SESSION_HPP_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string_view>
#include "boost/circular_buffer.hpp"
#include "cage/beast.hpp"
#include "cage/boost.hpp"
#include "cage/controller.hpp"

namespace cage {

class WebsockSession : public std::enable_shared_from_this<WebsockSession> {
 public:
  using StreamType = websocket::stream<beast::tcp_stream>;
  using BufferType = beast::flat_buffer;

  // bool: true - is text, false - is binary
  using SendMsgType = std::tuple<std::string, bool>;
  using SendMsgPtr = std::shared_ptr<SendMsgType>;
  using MsgQueType = boost::circular_buffer<SendMsgPtr>;
  using ControllerPtr = Controller::SelfPtr;
  using WebsockViewPtr = WebsockView::SelfPtr;

 public:
  ~WebsockSession() = default;

  explicit WebsockSession(std::uint64_t session_id, tcp::socket socket,
                          ControllerPtr p_controller);

  void Run(HttpRequest request);

 private:
  void OnAccept(beast::error_code ec, HttpRequest request);

  void DoRead();
  void OnRead(beast::error_code ec, std::size_t);

  void DoSend(std::string_view msg, bool is_txt);
  void OnSend(SendMsgPtr p_send_msg);

  void DoWrite();
  void OnWrite(beast::error_code ec, std::size_t);

  void DoClose(websocket::close_reason rc);
  void OnClose(beast::error_code ec);

 private:
  std::uint64_t session_id_;

  StreamType ws_stream_;
  BufferType read_buff_;

  ControllerPtr p_controller_;
  WebsockViewPtr p_view_;

  MsgQueType send_msg_que_;
  SendMsgPtr p_msg_on_sending_;
};

}  // namespace cage

#endif  // CAGE_WEBSOCK_SESSION_HPP_
