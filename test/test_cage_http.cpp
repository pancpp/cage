/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include <iostream>
#include <string>
#include "boost/asio/io_context.hpp"
#include "boost/asio/signal_set.hpp"
#include "cage/controller.hpp"
#include "cage/server.hpp"

using namespace cage;

class HttpViewRoot : public HttpView {
 public:
  ~HttpViewRoot() = default;
  HttpViewRoot() {
  }

  HttpResponse Get(HttpRequest const& request) override {
    HttpResponse res{HttpStatus::ok, request.Version()};
    res.Body("hello, world");
    return res;
  }

  static std::shared_ptr<HttpView> MakeView() {
    return std::make_shared<HttpViewRoot>();
  }
};

int main() {
  Server server(1234);
  std::cout << "Server created" << std::endl;

  std::shared_ptr<Controller> p_controller = std::make_shared<Controller>();
  p_controller->RegisterViewMaker("/", std::bind(&HttpViewRoot::MakeView));
  server.SetController(p_controller);
  std::cout << "Set controller" << std::endl;

  server.Start();
  std::cout << "Server started" << std::endl;

  boost::asio::io_context ioc;
  boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
  signals.async_wait([&ioc](std::error_code, int) { ioc.stop(); });
  ioc.run();

  server.Stop();
  std::cout << "Server stopped" << std::endl;

  return 0;
}
