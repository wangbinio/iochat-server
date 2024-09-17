//
// Created by summer on 2024/9/14.
//
#include "inc.h"
#include "config_manager.h"
#include "status_server_impl.h"

int main() {
  const auto server_address =
      ConfigManager::GetInstance().GetString("status-server", "host") + ":" +
      ConfigManager::GetInstance().GetString("status-server", "port");

  StatusServerImpl service;
  grpc::ServerBuilder builder;
  builder.RegisterService(&service);
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  spdlog::info("Server listening on {}", server_address);

  net::io_context io_context;
  net::signal_set signals(io_context, SIGINT, SIGTERM);

  signals.async_wait([&server, &io_context](
      const boost::system::error_code& error,
      int signal) {
        if (error) {
          spdlog::error(error.message());
        }
        spdlog::info("Received signal {}, Shutting down server...", signal);
        server->Shutdown();
        io_context.stop();
      });

  std::thread([&io_context]() { io_context.run(); }).detach();

  server->Wait();

  return 0;
}
