/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP and WEBSOCKET server.
 * @details The server is implemented in the well-knonw MVC (Model, View,
 * Controller) pattern with the `boost::asio` and `boost::beast` libraries. The
 * naming of this server is `cage` which means to lock the `beast` in a `cage`.
 * The user do not need to have any knowledge in `boost::asio` and
 * `boost::beast`. The exposured APIs are pretty general and easy to use.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_SERVER_HPP_
#define CAGE_SERVER_HPP_

#include <cstdint>
#include <memory>
#include <string>
#include "boost/asio/io_context.hpp"
#include "cage/controller.hpp"
#include "jthread.hpp"

namespace cage {

class Server {
 public:
  using ControllerPtr = std::shared_ptr<Controller>;

 public:
  ~Server() = default;
  Server(std::uint16_t port = 80, std::size_t num_threads = 1);

  void SetController(ControllerPtr p_controller);

  void Start();
  void Stop();

 private:
  std::uint16_t port_;

  std::vector<std::jthread> thread_pool_;
  boost::asio::io_context ioc_;
  ControllerPtr p_controller_;
};

}  // namespace cage

#endif  // CAGE_SERVER_HPP_
