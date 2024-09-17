//
// Created by summer on 2024/9/14.
//

#ifndef STATUS_GRPC_CLIENT_H
#define STATUS_GRPC_CLIENT_H
#include "inc.h"
#include <grpcpp/grpcpp.h>
#include "grpc_connection_pool.h"
#include "message.grpc.pb.h"
#include "singleton.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::StatusService;
using message::GetChatServerRequest;
using message::GetChatServerResponse;


class StatusGrpcClient : public Singleton<StatusGrpcClient> {
  friend class Singleton<StatusGrpcClient>;

  StatusGrpcClient();

  std::unique_ptr<GrpcConnectionPool<StatusService>> pool_;

public:
  GetChatServerResponse GetChatServer(int uid) const;
};


#endif //STATUS_GRPC_CLIENT_H
