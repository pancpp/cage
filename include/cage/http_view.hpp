/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Abstract HTTP view.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_HTTP_VIEW_HPP_
#define CAGE_HTTP_VIEW_HPP_

#include <memory>
#include <string>
#include "cage/http_request.hpp"
#include "cage/http_response.hpp"

namespace cage {

class HttpView {
 public:
  using SelfPtr = std::shared_ptr<HttpView>;

 public:
  virtual ~HttpView() = 0;

  virtual HttpResponse Get(HttpRequest const &request);
  virtual HttpResponse Head(HttpRequest const &request);
  virtual HttpResponse Post(HttpRequest const &request);
  virtual HttpResponse Put(HttpRequest const &request);

  virtual HttpResponse Handle(HttpRequest const &request);

 protected:
  virtual HttpResponse BadRequest(HttpRequest const &request,
                                  std::string &&msg);
};

}  // namespace cage

#endif  // CAGE_HTTP_VIEW_HPP_
