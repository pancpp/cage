/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief HTTP session.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/http_session.hpp"
#include <atomic>
#include <chrono>
#include <cstdint>
#include <string_view>
#include "cage/websock_session.hpp"

namespace cage {

namespace {
std::atomic<std::uint64_t> g_session_id(0);
};  // namespace

HttpSession::HttpSession(tcp::socket socket, ControllerPtr p_controller)
    : session_id_(++g_session_id),
      tcp_stream_(std::move(socket)),
      p_controller_(std::move(p_controller)) {
  // Set the timeout
  tcp_stream_.expires_after(p_controller_->SocketTimeout());
}

void HttpSession::Run() {
  DoRead();
}

void HttpSession::DoRead() {
  // Construct a new parser for each message
  p_parser_ = std::make_unique<RequestParser>();

  // Apply a reasonable limit to the allowed size of the header and body in
  // bytes to prevent abuse
  p_parser_->header_limit(p_controller_->HttpHeadLimit());
  p_parser_->body_limit(p_controller_->HttpBodyLimit());

  // Read a request
  http::async_read(
      tcp_stream_, read_buff_, *p_parser_,
      [self = shared_from_this()](beast::error_code ec, std::size_t len) {
        self->OnRead(ec, len);
      });
}

void HttpSession::OnRead(beast::error_code ec, std::size_t) {
  // This means they closed the connection
  if (ec == http::error::end_of_stream) {
    DoClose();
    return;
  }

  // Handle the error, if any
  if (ec) {
    return;
  }

  // Get the http request
  auto request = std::move(p_parser_->get());

  // Check whether it is a websocket upgrade
  if (websocket::is_upgrade(request)) {
    // Create a websocket session, transferring ownership of both the socket and
    // the HTTP request
    auto p_ws_session = std::make_shared<WebsockSession>(
        session_id_, tcp_stream_.release_socket(), std::move(p_controller_));
    p_ws_session->Run(std::move(request));
    return;
  }

  // Handle the HTTP request
  HttpResponse response;

  p_view_ = p_controller_->GetHttpView(
      std::string(request.target().data(), request.target().size()));
  if (p_view_) {
    switch (request.method()) {
      case http::verb::get:
        response = p_view_->Get(request);
        break;
      case http::verb::head:
        response = p_view_->Head(request);
        break;
      case http::verb::post:
        response = p_view_->Post(request);
        break;
      case http::verb::put:
        response = p_view_->Put(request);
        break;
      default:
        response = BadRequest(
            request,
            "HTTP method " +
                std::string(request.target().data(), request.target().size()) +
                " not supported");
        break;
    }
  } else {
    // respond not found
    response = NotFound(request, "HTTP method " +
                                     std::string(request.target().data(),
                                                 request.target().size()) +
                                     " not found");
  }

  response.set(http::field::server, p_controller_->ServerName());
  response.keep_alive(request.keep_alive());

  auto p_response = std::make_shared<HttpResponse>(std::move(response));
  http::async_write(tcp_stream_, *p_response,
                    [self = shared_from_this(), p_response](
                        beast::error_code ec, std::size_t len) {
                      self->OnWrite(ec, len, p_response->need_eof());
                    });
}

void HttpSession::OnWrite(beast::error_code ec, std::size_t, bool close) {
  // Handle the error, if any
  if (ec) {
    return;
  }

  if (close) {
    // This means we should close the connection, usually because
    // the response indicated the "Connection: close" semantic.
    tcp_stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
    return;
  }

  // Read another request
  DoRead();
}

void HttpSession::DoClose() {
  // Send a TCP shutdown
  beast::error_code ec;
  tcp_stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
  // At this point, the connection is closed gracefylly.
}

HttpResponse HttpSession::NotFound(HttpRequest const &request,
                                   std::string &&msg) {
  HttpResponse response{http::status::not_found, request.version()};
  response.set(http::field::content_type, "text/plain");
  response.body() = std::move(msg);

  return response;
}

HttpResponse HttpSession::BadRequest(HttpRequest const &request,
                                     std::string &&msg) {
  HttpResponse response{http::status::bad_request, request.version()};
  response.set(http::field::content_type, "text/plain");
  response.body() = std::move(msg);
  return response;
}

}  // namespace cage
