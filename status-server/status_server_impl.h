//
// Created by summer on 2024/9/15.
//

#ifndef STATUS_SERVER_IMPL_H
#define STATUS_SERVER_IMPL_H

#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include <boost/uuid/uuid_generators.hpp>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using message::StatusService;
using message::GetChatServerRequest;
using message::GetChatServerResponse;

struct ChatServer {
  std::string host;
  std::string port;
  std::string name;
  int conn_count = 0;
};

class StatusServerImpl final : public StatusService::Service {
public:
  StatusServerImpl();
  Status GetChatServer(ServerContext* context,
      const GetChatServerRequest* request,
      GetChatServerResponse* response) override;

private:
  void InsertToken(int uid, const std::string& token);
  ChatServer GetIdlestChatServer();
  boost::uuids::random_generator gen;
  std::unordered_map<std::string, ChatServer> chat_servers_;
  std::mutex mutex_;
};


#endif //STATUS_SERVER_IMPL_H
