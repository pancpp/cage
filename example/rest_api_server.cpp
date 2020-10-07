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
#include "cage/beast.hpp"
#include "cage/controller.hpp"
#include "cage/http_request.hpp"
#include "cage/http_response.hpp"
#include "cage/router.hpp"
#include "cage/server.hpp"

using namespace cage;

class HttpView1 : public HttpView {
 public:
  HttpResponse Get(HttpRequest const& request) override {
    HttpResponse res{http::status::ok, request.version()};
    res.body() = "GET from " +
                 std::string(request.target().data(), request.target().size());

    return res;
  }
};

class HttpView2 : public HttpView {
 public:
  HttpResponse Post(HttpRequest const& request) override {
    HttpResponse res{http::status::ok, request.version()};
    res.body() = "POST from " +
                 std::string(request.target().data(), request.target().size()) +
                 ": " + request.body();
    return res;
  }
};

int main() {
  Server server(1234);
  std::cout << "Server created" << std::endl;

  std::shared_ptr<Router> p_router = std::make_shared<Router>();
  std::shared_ptr<Controller> p_controller = std::make_shared<Controller>();

  p_router->RegisterPath("/api/1/",
                         [] { return std::make_shared<HttpView1>(); });
  p_router->RegisterPath("/api/2/[0-9]+/",
                         [] { return std::make_shared<HttpView2>(); });
  p_controller->RegisterRouter(p_router);
  server.SetController(p_controller);

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
