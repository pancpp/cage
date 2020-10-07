/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief TCP listener.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/listener.hpp"
#include "cage/http_session.hpp"

namespace cage {

Listener::Listener(asio::io_context &ioc, tcp::endpoint ep,
                   ControllerPtr p_controller)
    : ioc_(ioc),
      acceptor_(asio::make_strand(ioc)),
      p_controller_(std::move(p_controller)) {
  // Open the acceptor
  acceptor_.open(ep.protocol());

  // Allow address reuse
  acceptor_.set_option(asio::socket_base::reuse_address(true));

  // Bind to the local endpoint
  acceptor_.bind(ep);

  // Start listening for incoming connections
  acceptor_.listen(asio::socket_base::max_listen_connections);
}

void Listener::Run() {
  DoAccept();
}

void Listener::DoAccept() {
  // The new connection gets its own strand
  acceptor_.async_accept(
      asio::make_strand(ioc_),
      [self = shared_from_this()](beast::error_code ec, tcp::socket socket) {
        self->OnAccept(ec, std::move(socket));
      });
}

void Listener::OnAccept(beast::error_code ec, tcp::socket socket) {
  if (!ec) {
    // Create a http session and run it.
    auto p_http_session =
        std::make_shared<HttpSession>(std::move(socket), p_controller_);
    p_http_session->Run();
  }

  // Continue accepting for new connections
  DoAccept();
}

}  // namespace cage
