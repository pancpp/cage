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
#include "cage/beast_http.hpp"
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
  auto beast_request = std::move(p_parser_->get());

  // Check whether it is a websocket upgrade
  if (websocket::is_upgrade(beast_request)) {
    // Create a websocket session, transferring ownership of both the socket and
    // the HTTP request
    auto p_ws_session = std::make_shared<WebsockSession>(
        session_id_, tcp_stream_.release_socket(), std::move(p_controller_));
    p_ws_session->Run(std::move(beast_request));
    return;
  }

  // Handle the HTTP request
  HttpRequest http_request = BeastRequestToHttp(std::move(beast_request));
  HttpResponse http_response;

  p_view_ = p_controller_->GetHttpView(http_request.Path());
  if (p_view_) {
    switch (http_request.Method()) {
      case HttpMethod::get:
        http_response = p_view_->Get(http_request);
        break;
      case HttpMethod::head:
        http_response = p_view_->Head(http_request);
        break;
      case HttpMethod::post:
        http_response = p_view_->Post(http_request);
        break;
      case HttpMethod::put:
        http_response = p_view_->Put(http_request);
        break;
      default:
        http_response = BadRequest(
            http_request,
            "HTTP method " + http_request.MethodString() + " not supported");
        break;
    }
  } else {
    // respond not found
    http_response =
        NotFound(http_request,
                 "HTTP method " + http_request.MethodString() + " not found");
  }

  http_response.Set(HttpField::server, p_controller_->ServerName());
  http_response.KeepAlive(http_request.KeepAlive());

  auto p_beast_response = std::make_shared<BeastResponse>(
      HttpResponseToBeast(std::move(http_response)));
  http::async_write(tcp_stream_, *p_beast_response,
                    [self = shared_from_this(), p_beast_response](
                        beast::error_code ec, std::size_t len) {
                      self->OnWrite(ec, len, p_beast_response->need_eof());
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
  HttpResponse response{HttpStatus::not_found, request.Version()};
  response.Set(HttpField::content_type, "text/plain");
  response.Body(std::move(msg));
  return response;
}

HttpResponse HttpSession::BadRequest(HttpRequest const &request,
                                     std::string &&msg) {
  HttpResponse response{HttpStatus::bad_request, request.Version()};
  response.Set(HttpField::content_type, "text/plain");
  response.Body(std::move(msg));
  return response;
}

}  // namespace cage
