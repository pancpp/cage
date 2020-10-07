/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief URL parser.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */
#ifndef CAGE_URL_HPP_
#define CAGE_URL_HPP_

#include <map>
#include <string>
#include <string_view>

namespace cage {

class Url {
 public:
  virtual ~Url() = default;
  Url() = default;
  explicit Url(std::string target);
  explicit Url(std::string_view target);

  void Parse(std::string target);
  void Parse(std::string_view target);

  std::string const& Target() const;
  std::string const& Path() const;
  std::string const& Query() const;
  std::string const& Fragment() const;

  std::map<std::string, std::string> QueryMap() const;

 protected:
  virtual void Parse();

 protected:
  std::string target_;
  std::string path_;
  std::string query_;
  std::string fragment_;

  std::map<std::string, std::string> query_map_;
};

}  // namespace cage

#endif  // CAGE_URL_HPP_
