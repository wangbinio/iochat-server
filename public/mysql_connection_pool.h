//
// Created by summer on 2024/9/8.
//

#ifndef MYSQL_CONNECTION_POOL_H
#define MYSQL_CONNECTION_POOL_H

#include "inc.h"

namespace sql {
class Connection;
}

class PUBLIC_TOOLS_API MysqlConnectionPool : net::noncopyable {
public:
  MysqlConnectionPool(const std::string& url, const std::string& user,
      const std::string& password, const std::string& database, std::size_t
      pool_size = 4);

  ~MysqlConnectionPool();

  std::unique_ptr<sql::Connection, std::function<void(sql::Connection*)>>
  GetConnection();

  void Stop();

  std::size_t AvailableConnections() const;

private:
  void ReturnConnection(std::unique_ptr<sql::Connection> connection);

  std::queue<std::unique_ptr<sql::Connection>> connections_;
  std::atomic_bool stop_;
  std::size_t pool_size_;
  std::mutex mutex_;
  std::condition_variable cond_;
};


#endif //MYSQL_CONNECTION_POOL_H
