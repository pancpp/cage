/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP session.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_HTTP_SESSION_HPP_
#define CAGE_HTTP_SESSION_HPP_

#include <cstddef>
#include <memory>
#include <optional>
#include "cage/beast.hpp"
#include "cage/boost.hpp"
#include "cage/controller.hpp"
#include "cage/http_request.hpp"
#include "cage/http_response.hpp"

namespace cage {

class HttpSession : public std::enable_shared_from_this<HttpSession> {
 public:
  using ControllerPtr = Controller::SelfPtr;
  using HttpViewPtr = HttpView::SelfPtr;

  using StreamType = beast::tcp_stream;
  using BufferType = beast::flat_buffer;

  using RequestParser = http::request_parser<http::string_body>;
  using RequestParserPtr = std::unique_ptr<RequestParser>;

 public:
  ~HttpSession() = default;

  HttpSession(tcp::socket socket, ControllerPtr p_controller);

  void Run();

 private:
  void DoRead();
  void OnRead(beast::error_code ec, std::size_t);

  void OnWrite(beast::error_code ec, std::size_t, bool close);

  void DoClose();

 private:
  HttpResponse NotFound(HttpRequest const &request, std::string &&msg);
  HttpResponse BadRequest(HttpRequest const &request, std::string &&msg);

 private:
  std::uint64_t session_id_;

  StreamType tcp_stream_;
  BufferType read_buff_;
  RequestParserPtr p_parser_;

  ControllerPtr p_controller_;
  HttpViewPtr p_view_;
};

}  // namespace cage

#endif  // CAGE_HTTP_SESSION_HPP_
