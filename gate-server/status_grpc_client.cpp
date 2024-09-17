//
// Created by summer on 2024/9/14.
//

#include "status_grpc_client.h"
#include "config_manager.h"


GetChatServerResponse StatusGrpcClient::GetChatServer(const int uid) const {
  GetChatServerResponse response;
  GetChatServerRequest request;
  ClientContext context;
  request.set_uid(uid);
  const auto stub = pool_->GetConnection();
  const auto status = stub->GetChatServer(&context, request, &response);
  if (!status.ok())
    response.set_error(ErrorCode::kRPCFailed);
  return response;
}

StatusGrpcClient::StatusGrpcClient() {
  const auto host = ConfigManager::GetInstance().GetString("status-server",
      "host");
  const auto port = ConfigManager::GetInstance().GetString("status-server",
      "port");

  pool_ = std::make_unique<GrpcConnectionPool<StatusService>>(4, host, port);
}
