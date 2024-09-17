//
// Created by summer on 2024/9/8.
//

#include "mysql_connection_pool.h"
#include <mysql/jdbc.h>


using namespace sql;
using namespace sql::mysql;

MysqlConnectionPool::MysqlConnectionPool(const std::string& url,
    const std::string& user, const std::string& password,
    const std::string& database, const std::size_t pool_size)
  : pool_size_(pool_size) {
  const auto driver = get_mysql_driver_instance();
  for (std::size_t i = 0; i < pool_size; i++) {
    auto conn = driver->connect(url, user, password);
    conn->setSchema(database);
    connections_.emplace(conn);
  }
}

MysqlConnectionPool::~MysqlConnectionPool() {
  std::unique_lock<std::mutex> lock(mutex_);
  Stop();
  while (!connections_.empty()) {
    connections_.pop();
  }
}

std::unique_ptr<sql::Connection, std::function<void(sql::Connection*)>>
MysqlConnectionPool::GetConnection() {
  std::unique_lock<std::mutex> lock(mutex_);
  cond_.wait(lock, [this] {
    if (stop_) return true;
    return !connections_.empty();
  });

  if (stop_) return nullptr;

  auto conn = std::move(connections_.front());
  connections_.pop();

  return {conn.release(), [this](Connection* c) {
    ReturnConnection(std::unique_ptr<Connection>(c));
  }};
}

void MysqlConnectionPool::Stop() {
  stop_ = true;
  cond_.notify_all();
}

std::size_t MysqlConnectionPool::AvailableConnections() const {
  return connections_.size();
}

void MysqlConnectionPool::ReturnConnection(
    std::unique_ptr<sql::Connection> connection) {
  std::unique_lock<std::mutex> lock(mutex_);
  if (stop_) return;
  connections_.emplace(std::move(connection));
  cond_.notify_one();
}
