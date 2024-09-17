//
// Created by summer on 2024/9/9.
//

#include "mysql_manager.h"

#include "config_manager.h"

MysqlManager::MysqlManager() {
  const auto host = ConfigManager::GetInstance().GetString("mysql", "host");
  const auto port = ConfigManager::GetInstance().GetString("mysql", "port");
  const auto user = ConfigManager::GetInstance().GetString("mysql", "user");
  const auto passwd = ConfigManager::GetInstance().GetString("mysql", "passwd");
  const auto schema = ConfigManager::GetInstance().GetString("mysql", "schema");

  pool_ = std::make_unique<MysqlConnectionPool>(host + ":" + port, user, passwd,
      schema);
  dao_ = std::make_unique<MysqlDao>(pool_);
}

MysqlManager::~MysqlManager() {
  pool_->Stop();
}
