// Created by summer on 2024/9/6.
//

#include "verify_grpc_client.h"
#include "config_manager.h"

VerifyGrpcClient::VerifyGrpcClient() {
  std::string host = ConfigManager::GetInstance().GetString("verify-server",
      "host");
  std::string port = ConfigManager::GetInstance().GetString("verify-server",
      "port");
  pool_ = std::make_unique<GrpcConnectionPool<VerifyService>>(5, host, port);
}

GetVerifyResponse VerifyGrpcClient::GetVerifyCode(
    const std::string& email) const {
  ClientContext context;
  GetVerifyRequest request;
  GetVerifyResponse response;
  request.set_email(email);

  const auto status = pool_->GetConnection()->GetVerifyCode(&context,
      request, &response);
  if (!status.ok()) {
    response.set_error(ErrorCode::kRPCFailed);
  }

  return response;
}
