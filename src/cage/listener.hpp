/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief TCP listener.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_LISTENER_HPP_
#define CAGE_LISTENER_HPP_

#include <memory>
#include "cage/beast.hpp"
#include "cage/controller.hpp"

namespace cage {

class Listener : public std::enable_shared_from_this<Listener> {
 public:
  using ControllerPtr = Controller::SelfPtr;

 public:
  ~Listener() = default;

  explicit Listener(asio::io_context &ioc, tcp::endpoint ep,
                    ControllerPtr p_controller);

  void Run();

 private:
  void DoAccept();
  void OnAccept(beast::error_code ec, tcp::socket socket);

 private:
  asio::io_context &ioc_;
  tcp::acceptor acceptor_;
  ControllerPtr p_controller_;
};

}  // namespace cage

#endif  // CAGE_LISTENER_HPP_
