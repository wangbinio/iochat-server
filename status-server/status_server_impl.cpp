//
// Created by summer on 2024/9/15.
//
#include <boost/uuid/uuid_io.hpp>
#include "status_server_impl.h"
#include "config_manager.h"
#include "inc.h"
#include "redis_manager.h"

Status StatusServerImpl::GetChatServer(ServerContext* context,
    const GetChatServerRequest* request, GetChatServerResponse* response) {
  spdlog::info("Received GetChatServerRequest uid = {}", request->uid());
  const auto& server = GetIdlestChatServer();
  response->set_host(server.host);
  response->set_port(server.port);
  response->set_error(ErrorCode::kSuccess);
  response->set_token(to_string(gen()));

  InsertToken(request->uid(), response->token());
  return Status::OK;
}

StatusServerImpl::StatusServerImpl() {
  const auto str_servers = ConfigManager::GetInstance().GetString(
      "chat-servers", "name");
  const auto servers = split(str_servers, ",");
  for (const auto& server : servers) {
    ChatServer chat_server;
    chat_server.name = server;
    chat_server.host = ConfigManager::GetInstance().GetString(server, "host");
    chat_server.port = ConfigManager::GetInstance().GetString(server, "port");
    chat_servers_[server] = chat_server;
  }
}

void StatusServerImpl::InsertToken(const int uid, const std::string& token) {
  RedisManager::GetInstance()->GetRedis()->set(std::to_string(uid),
      kUserTokenPrefix + token);
}

ChatServer StatusServerImpl::GetIdlestChatServer() {
  std::lock_guard<std::mutex> lock(mutex_);

  auto idlest_server = chat_servers_.begin()->second;
  const auto redis = RedisManager::GetInstance()->GetRedis();
  for (auto& chat_server : chat_servers_) {
    auto count_str = redis->hget(kLoginCount, chat_server.second.name);
    if (!count_str) chat_server.second.conn_count = INT_MAX;
    else chat_server.second.conn_count = std::stoi(count_str.value());
    if (chat_server.second.conn_count < idlest_server.conn_count) {
      idlest_server = chat_server.second;
    }
  }

  return idlest_server;
}
