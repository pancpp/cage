/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP and WEBSOCKET server.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/server.hpp"
#include <memory>
#include "cage/beast.hpp"
#include "cage/boost.hpp"
#include "cage/listener.hpp"

namespace cage {

Server::Server(std::uint16_t port, std::size_t num_threads)
    : port_(port), thread_pool_(num_threads) {
}

void Server::SetController(ControllerPtr p_controller) {
  p_controller_ = std::move(p_controller);
}

void Server::Start() {
  std::make_shared<Listener>(
      ioc_, tcp::endpoint(asio::ip::address_v4::any(), port_), p_controller_)
      ->Run();

  for (auto &t : thread_pool_) {
    t = std::jthread([this] { ioc_.run(); });
  }
}

void Server::Stop() {
  ioc_.stop();
}

}  // namespace cage
