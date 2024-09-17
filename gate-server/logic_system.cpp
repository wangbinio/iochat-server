//
// Created by summer on 2024/9/5.
//

#include "logic_system.h"
#include "inc.h"
#include "http_connection.h"
#include "mysql_manager.h"
#include "redis_manager.h"
#include "status_grpc_client.h"
#include "nlohmann/json.hpp"
#include "verify_grpc_client.h"

void LogicSystem::RegisterGetRequest(std::string request_type,
    RequestHandler handler) {
  get_handlers_.emplace(request_type, handler);
}

void LogicSystem::RegisterPostRequest(std::string request_type,
    RequestHandler handler) {
  post_handlers_.emplace(request_type, handler);
}

bool LogicSystem::HandleGetRequest(const std::string& url,
    HttpConnectionPtr connection) {
  const auto iter = get_handlers_.find(url);
  if (iter == get_handlers_.end()) {
    spdlog::error("Request handler does not exist: {}", url);
    return false;
  }

  iter->second(connection);
  return true;
}

bool LogicSystem::HandlePostRequest(const std::string& url,
    HttpConnectionPtr connection) {
  const auto iter = post_handlers_.find(url);
  if (iter == post_handlers_.end()) {
    spdlog::error("Request handler does not exist: {}", url);
    return false;
  }
  iter->second(connection);
  return true;
}

LogicSystem::LogicSystem() {
  RegisterGetRequest("/get_test", [](HttpConnectionPtr connection) {
    spdlog::info("handling get_test request...");
    beast::ostream(connection->response_.body()) << "receive get_test request";
    int index = 0;
    for (const auto& elem : connection->get_params_) {
      beast::ostream(connection->response_.body()) << '\n' << ++index << "\t" <<
          elem.first << "=" << elem.second;
    }
  });

  RegisterPostRequest("/get_verifycode", [](HttpConnectionPtr connection) {
    auto body_str = beast::buffers_to_string(
        connection->request_.body().data());
    spdlog::info("receive get_verifycode request: {}", body_str);
    nlohmann::json json = nlohmann::json::parse(body_str);
    nlohmann::json response;
    if (json.is_null() || !json.contains("email")) {
      spdlog::error("Received get_verifycode request failed: invalid json");
      response["error"] = ErrorCode::kErrorJson;
    } else {
      std::string email = json["email"];
      const auto& verify_response = VerifyGrpcClient::GetInstance()->
          GetVerifyCode(email);
      response["verifycode"] = verify_response.code();
      response["email"] = email;
      response["error"] = verify_response.error();
      spdlog::info("verify_code is: {}", verify_response.code());
    }
    beast::ostream(connection->response_.body()) << response.dump();
  });

  RegisterPostRequest("/user_register", [](HttpConnectionPtr connection) {
    auto body_str = beast::buffers_to_string(
        connection->request_.body().data());
    spdlog::info("receive user_register request: {}", body_str);
    nlohmann::json json = nlohmann::json::parse(body_str);
    nlohmann::json response;
    if (json.is_null() || !json.contains("email") || !json.contains("user") ||
        !json.contains("passwd") || !json.contains("confirm") || !json.
        contains("verifycode")) {
      spdlog::error("Received user_register request failed: invalid json");
      response["error"] = ErrorCode::kErrorJson;
    } else {
      std::string email = json["email"];
      std::string user = json["user"];
      std::string passwd = json["passwd"];
      std::string verifycode = json["verifycode"];
      spdlog::info("email is: {}", email);

      auto verify_code_in_redis = RedisManager::GetInstance()->GetRedis()->get(
          kCodePrefix + email);
      // check verify code in redis
      if (!verify_code_in_redis) {
        response["error"] = ErrorCode::kVerifyExpired;
      } else if (verify_code_in_redis.value() != verifycode) {
        response["error"] = ErrorCode::kVerifyCodeErr;
      } else {
        auto uid = MysqlManager::GetInstance()->RegisterUser(user, passwd,
            email);
        if (uid == 0) {
          response["error"] = ErrorCode::kUserExist;
        } else {
          spdlog::info("Register user success. uid = {}", uid);
          response["email"] = email;
          response["error"] = kSuccess;
          response["uid"] = uid;
        }
      }
    }
    beast::ostream(connection->response_.body()) << response.dump();
  });

  RegisterPostRequest("/reset_passwd", [](HttpConnectionPtr connection) {
    auto body_str =
        beast::buffers_to_string(connection->request_.body().data());
    spdlog::info("receive reset password request: {}", body_str);
    nlohmann::json json = nlohmann::json::parse(body_str);
    nlohmann::json response;
    if (json.is_null() || !json.contains("user") || !json.contains("passwd")
        || !json.contains("email") || !json.contains("verifycode")) {
      spdlog::error("Received reset password request failed: invalid json");
      response["error"] = ErrorCode::kErrorJson;
      beast::ostream(connection->response_.body()) << response.dump();
      return;
    }

    std::string user = json["user"];
    std::string passwd = json["passwd"];
    std::string email = json["email"];
    std::string verifycode = json["verifycode"];

    auto verify_code_in_redis = RedisManager::GetInstance()->GetRedis()->get
        (kCodePrefix + email);
    if (!verify_code_in_redis) {
      response["error"] = ErrorCode::kVerifyExpired;
    } else if (verify_code_in_redis.value() != verifycode) {
      response["error"] = ErrorCode::kVerifyCodeErr;
    } else {
      if (MysqlManager::GetInstance()->ResetPassword(user, passwd, email)) {
        spdlog::info("reset password success");
        response["email"] = email;
        response["error"] = ErrorCode::kSuccess;
      } else {
        response["error"] = ErrorCode::kPasswdErr;
      }
    }
    beast::ostream(connection->response_.body()) << response.dump();
  });

  RegisterPostRequest("/user_login", [](HttpConnectionPtr connection) {
    auto body_str =
        beast::buffers_to_string(connection->request_.body().data());
    spdlog::info("receive user login request: {}", body_str);
    nlohmann::json json = nlohmann::json::parse(body_str);
    nlohmann::json response;
    if (json.is_null() || !json.contains("user") || !json.contains("passwd")) {
      spdlog::error("Received reset password request failed: invalid json");
      response["error"] = ErrorCode::kErrorJson;
      beast::ostream(connection->response_.body()) << response.dump();
      return;
    }

    std::string user = json["user"];
    std::string passwd = json["passwd"];
    UserInfo user_info;
    if (!MysqlManager::GetInstance()->Login(user, passwd, user_info)) {
      spdlog::error("login failed");
      response["error"] = ErrorCode::kPasswdErr;
      beast::ostream(connection->response_.body()) << response.dump();
      return;
    }

    // query status server
    auto reply = StatusGrpcClient::GetInstance()->GetChatServer(user_info.uid);
    if (reply.error() != ErrorCode::kSuccess) {
      spdlog::error("get chat server failed");
      response["error"] = ErrorCode::kRPCFailed;
      beast::ostream(connection->response_.body()) << response.dump();
      return;
    }
    spdlog::info("{} login success", user_info.uid);

    response["user"] = user;
    response["uid"] = user_info.uid;
    response["token"] = reply.token();
    response["host"] = reply.host();
    response["port"] = reply.port();
    response["error"] = ErrorCode::kSuccess;
    beast::ostream(connection->response_.body()) << response.dump();
  });
}
