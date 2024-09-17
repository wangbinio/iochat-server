//
// Created by summer on 2024/9/9.
//

#ifndef MYSQL_MANAGER_H
#define MYSQL_MANAGER_H

#include "mysql_dao.h"
#include "singleton.h"

class PUBLIC_TOOLS_API MysqlManager : public Singleton<MysqlManager> {
  friend class Singleton<MysqlManager>;

public:
  [[nodiscard]] uint64_t RegisterUser(const std::string& username,
      const std::string& password, const std::string& email) const {
    return dao_->RegisterUser(username, password, email);
  }

  [[nodiscard]] bool ResetPassword(const std::string& name,
      const std::string& password, const std::string& email) const {
    return dao_->ResetPassword(name, password, email);
  }

  [[nodiscard]] bool Login(const std::string& username, const std::string&
      password, UserInfo& user_info) const {
    return dao_->Login(username, password, user_info);
  }

  ~MysqlManager();

private:
  MysqlManager();

  std::shared_ptr<MysqlConnectionPool> pool_;
  std::unique_ptr<MysqlDao> dao_;
};


#endif //MYSQL_MANAGER_H
