/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief URL parser.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#include "cage/url.hpp"
#include <stdexcept>

namespace cage {

Url::Url(std::string target) : target_(std::move(target)) {
  Parse();
}

Url::Url(std::string_view target) : target_(target.data(), target.size()) {
  Parse();
}

void Url::Parse(std::string target) {
  target_ = std::move(target);
  Parse();
}

void Url::Parse(std::string_view target) {
  target_ = std::string(target.data(), target.size());
  Parse();
}

void Url::Parse() {
}

std::string const& Url::Path() const {
  return path_;
}

std::string const& Url::Query() const {
  return query_;
}

std::string const& Url::Fragment() const {
  return fragment_;
}

std::map<std::string, std::string> Url::QueryMap() const {
  return query_map_;
}

}  // namespace cage
