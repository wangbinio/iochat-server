//
// Created by summer on 2024/9/9.
//

#ifndef MYSQL_DAO_H
#define MYSQL_DAO_H

#include "mysql_connection_pool.h"

struct UserInfo {
  std::string name;
  std::string passwd;
  int uid{};
  std::string email;
};

class PUBLIC_TOOLS_API MysqlDao {
public:
  explicit MysqlDao(std::shared_ptr<MysqlConnectionPool> pool);
  ~MysqlDao();

  [[nodiscard]] uint64_t RegisterUser(const std::string& username,
      const std::string& password, const std::string& email) const;

  [[nodiscard]] bool ResetPassword(const std::string& username,
      const std::string& password, const std::string& email) const;

  [[nodiscard]] bool Login(const std::string& username, const std::string&
      password, UserInfo& user_info) const;

private:
  std::shared_ptr<MysqlConnectionPool> pool_;
};


#endif //MYSQL_DAO_H
