/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Abstract websocket viewer.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/websock_view.hpp"

namespace cage {

WebsockView::WebsockView(HttpRequest request, SenderType sender,
                         CloserType closer)
    : request_(std::move(request)), sender_(std::move(sender)),
      closer_(std::move(closer)) {}

void WebsockView::Send(std::string_view msg, bool is_txt) {
  sender_(msg, is_txt);
}

void WebsockView::Close() { closer_(); }

HttpRequest const &WebsockView::GetHttpRequest() const { return request_; }

} // namespace cage
