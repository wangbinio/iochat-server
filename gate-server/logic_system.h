//
// Created by summer on 2024/9/5.
//

#ifndef LOGIC_SYSTEM_H
#define LOGIC_SYSTEM_H
#include <functional>
#include <memory>
#include <string>

#include "singleton.h"

class HttpConnection;
using HttpConnectionPtr = std::shared_ptr<HttpConnection>;
using RequestHandler = std::function<void(HttpConnectionPtr)>;

class LogicSystem : public Singleton<LogicSystem> {
public:
  friend class Singleton<LogicSystem>;
  ~LogicSystem() = default;
  void RegisterGetRequest(std::string request_type, RequestHandler handler);
  void RegisterPostRequest(std::string request_type, RequestHandler handler);
  bool HandleGetRequest(const std::string& url, HttpConnectionPtr connection);
  bool HandlePostRequest(const std::string& url, HttpConnectionPtr connection);

private:
  LogicSystem();
  std::unordered_map<std::string, RequestHandler> post_handlers_;
  std::unordered_map<std::string, RequestHandler> get_handlers_;
};


#endif //LOGIC_SYSTEM_H
