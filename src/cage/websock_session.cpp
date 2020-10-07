/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Websocket session.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/websock_session.hpp"
#include <string>
#include <string_view>
#include "cage/http_request.hpp"

namespace cage {

WebsockSession::WebsockSession(std::uint64_t session_id, tcp::socket socket,
                               ControllerPtr p_controller)
    : session_id_(session_id),
      ws_stream_(std::move(socket)),
      p_controller_(std::move(p_controller)),
      send_msg_que_(1024) {
}

void WebsockSession::Run(HttpRequest request) {
  // Set suggested timeout settings for the websocket
  ws_stream_.set_option(
      websocket::stream_base::timeout::suggested(beast::role_type::server));

  // Set a decorator to change the server of the handshake
  ws_stream_.set_option(websocket::stream_base::decorator(
      [self = shared_from_this()](websocket::response_type &res) {
        res.set(http::field::server, self->p_controller_->ServerName());
      }));

  // Accept the websocket handshake
  ws_stream_.async_accept(
      request, [self = shared_from_this(), request](beast::error_code ec) {
        self->OnAccept(ec, std::move(request));
      });
}

void WebsockSession::OnAccept(beast::error_code ec, HttpRequest request) {
  // Handle the error, if any
  if (ec) {
    return;
  }

  // Create viewer
  p_view_ = p_controller_->MakeWebsockView(
      std::move(request),
      [self = shared_from_this()](std::string_view msg, bool is_txt) {
        self->DoSend(msg, is_txt);
      },
      [self = shared_from_this()]() {
        self->DoClose(websocket::close_code::normal);
      });
  if (!p_view_) {
    return;
  }
  std::size_t send_msg_que_cap = p_controller_->WebsockMsgQueCap();
  if (send_msg_que_cap) {
    send_msg_que_.set_capacity(send_msg_que_cap);
  }

  // Do reading
  DoRead();
}

void WebsockSession::DoRead() {
  ws_stream_.async_read(read_buff_, [self = shared_from_this()](
                                        beast::error_code ec, std::size_t len) {
    self->OnRead(ec, len);
  });
}

void WebsockSession::OnRead(beast::error_code ec, std::size_t) {
  // Handle the error, if any
  if (ec) {
    p_view_->OnError(ec);
    return;
  }

  // Handle the read message
  p_view_->OnReceive(
      std::string_view(static_cast<char *>(read_buff_.data().data()),
                       read_buff_.data().size()),
      ws_stream_.got_text());
  read_buff_.consume(read_buff_.size());

  // Continue reading to keep the life of the session.
  DoRead();
}

void WebsockSession::DoSend(std::string_view msg, bool is_txt) {
  // Create the shared_ptr for the send msg
  SendMsgPtr p_send_msg =
      std::make_shared<SendMsgType>(std::tuple<std::string, bool>(
          std::string(msg.data(), msg.size()), is_txt));

  // Add the send msg to message queue
  asio::post(ws_stream_.get_executor(),
             [self = shared_from_this(), p_send_msg] {
               self->OnSend(std::move(p_send_msg));
             });
}

void WebsockSession::OnSend(SendMsgPtr p_send_msg) {
  // Always add to queue
  send_msg_que_.push_back(std::move(p_send_msg));

  // Are we already writing?
  if (!p_msg_on_sending_) {
    // We are not currently writing, so write it immediately.
    DoWrite();
  }
}

void WebsockSession::DoWrite() {
  p_msg_on_sending_ = std::move(send_msg_que_.front());
  send_msg_que_.pop_front();

  ws_stream_.text(std::get<1>(*p_msg_on_sending_));
  ws_stream_.async_write(
      asio::buffer(std::get<0>(*p_msg_on_sending_)),
      [self = shared_from_this()](beast::error_code ec, std::size_t len) {
        self->OnWrite(ec, len);
      });
}

void WebsockSession::OnWrite(beast::error_code ec, std::size_t) {
  if (ec) {
    p_view_->OnError(ec);
    return;
  }

  if (!send_msg_que_.empty()) {
    // Continue writing
    DoWrite();
  } else {
    p_msg_on_sending_.reset();
  }
}

void WebsockSession::DoClose(websocket::close_reason rc) {
  ws_stream_.async_close(rc, [self = shared_from_this()](beast::error_code ec) {
    self->OnClose(ec);
  });
}

void WebsockSession::OnClose(beast::error_code ec) {
  p_view_->OnClose(ec);
}

}  // namespace cage
