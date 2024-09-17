//
// Created by summer on 2024/9/4.
//

#include "server.h"

#include "http_connection.h"
#include "io_service_pool.h"

Server::Server(net::io_service& io_service, const unsigned short port)
  : io_service_(io_service),
    acceptor_(io_service_, tcp::endpoint(tcp::v4(), port)) {
}

void Server::Start() {
  auto self = shared_from_this();
  auto connection = std::make_shared<HttpConnection>(
      IoServicePool::GetInstance()->GetIoService());
  acceptor_.async_accept(connection->socket(), [self, connection]
  (boost::system::error_code ec) {
        if (!ec) {
          spdlog::info("Connection {} established.",
              connection->socket().remote_endpoint().address().to_string());
          connection->Start();
        } else {
          spdlog::error("accept error");
        }
        self->Start();
      });
}
