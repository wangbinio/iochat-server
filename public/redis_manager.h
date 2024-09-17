//
// Created by summer on 2024/9/7.
//

#ifndef REDIS_MANAGER_H
#define REDIS_MANAGER_H

#include "config_manager.h"
#include "singleton.h"
#include "redis_connection_pool.h"

class RedisManager : public Singleton<RedisManager> {
  friend class Singleton<RedisManager>;

public:
  [[nodiscard]] std::unique_ptr<Redis, std::function<void(Redis*)>>
  GetRedis() const {
    return pool_->GetRedis();
  }

private:
  RedisManager() {
    const auto host = ConfigManager::GetInstance().GetString("redis", "host");
    const auto port = ConfigManager::GetInstance().GetString("redis", "port");
    const auto passwd = ConfigManager::GetInstance().GetString("redis",
        "passwd");
    const auto url = "tcp://" + passwd + "@" + host + ":" + port;
    pool_ = std::make_unique<RedisConnectionPool>(url, 4);
  }

  std::unique_ptr<RedisConnectionPool> pool_;
};

#endif //REDIS_MANAGER_H
