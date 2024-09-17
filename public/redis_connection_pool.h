//
// Created by summer on 2024/9/7.
//

#ifndef REDIS_CONNECTION_POOL_H
#define REDIS_CONNECTION_POOL_H


#include "inc.h"

using Redis = sw::redis::Redis;

class PUBLIC_TOOLS_API RedisConnectionPool : net::noncopyable {
public:
  explicit RedisConnectionPool(const std::string& url,
      std::size_t pool_size = std::thread::hardware_concurrency());

  void Stop();
  std::unique_ptr<Redis, std::function<void(Redis*)>> GetRedis();
  std::size_t AvailableConnections() const;
  ~RedisConnectionPool();

private:
  void ReturnRedis(std::unique_ptr<Redis> redis);
  std::queue<std::unique_ptr<Redis>> pool_;
  std::atomic_bool stop_;
  std::mutex mutex_;
  std::condition_variable cond_;
  std::size_t pool_size_;
};


#endif //REDIS_CONNECTION_POOL_H
