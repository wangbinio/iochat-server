//
// Created by summer on 2024/9/6.
//

#ifndef VERIFY_GRPC_CLIENT_H
#define VERIFY_GRPC_CLIENT_H

#include <grpcpp/grpcpp.h>
#include "grpc_connection_pool.h"
#include "inc.h"
#include "singleton.h"
#include "message.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::GetVerifyRequest;
using message::GetVerifyResponse;
using message::VerifyService;

class VerifyGrpcClient : public Singleton<VerifyGrpcClient> {
  friend class Singleton<VerifyGrpcClient>;

  VerifyGrpcClient();

  std::unique_ptr<GrpcConnectionPool<VerifyService>> pool_;

public:
  GetVerifyResponse GetVerifyCode(const std::string& email) const;
};

#endif //VERIFY_GRPC_CLIENT_H
