//
// Created by summer on 2024/9/4.
//

#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include "inc.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
public:
  friend class LogicSystem;
  explicit HttpConnection(net::io_context& io_context);
  tcp::socket& socket();
  void Start();
  void HandleRequest();
  void WriteResponse();
  void CheckDeadline();
  void PreParseGetParam();

private:
  tcp::socket socket_;
  beast::flat_buffer buffer_{8192};
  http::request<http::dynamic_body> request_;
  http::response<http::dynamic_body> response_;
  net::steady_timer deadline_;
  std::string get_url_;
  std::unordered_map<std::string, std::string> get_params_;
};


#endif //HTTP_CONNECTION_H
