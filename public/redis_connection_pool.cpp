//
// Created by summer on 2024/9/7.
//

#include "redis_connection_pool.h"

RedisConnectionPool::RedisConnectionPool(const std::string& url,
    const std::size_t pool_size) : stop_(false), pool_size_(pool_size) {
  for (std::size_t i = 0; i < pool_size; i++) {
    pool_.emplace(std::make_unique<Redis>(url));
  }
}

void RedisConnectionPool::Stop() {
  stop_ = true;
  cond_.notify_all();
}

std::unique_ptr<Redis, std::function<void(Redis*)>>
RedisConnectionPool::GetRedis() {
  std::unique_lock<std::mutex> lock(mutex_);
  cond_.wait(lock, [this] {
    if (stop_) { return true; }
    return !pool_.empty();
  });

  if (stop_) { return nullptr; }

  auto redis = std::move(pool_.front());
  pool_.pop();

  return std::unique_ptr<Redis, std::function<void(Redis*)>>(redis.release(),
      [this](Redis* r) {
        this->ReturnRedis(std::unique_ptr<Redis>(r));
      });
}

std::size_t RedisConnectionPool::AvailableConnections() const {
  return pool_.size();
}

void RedisConnectionPool::ReturnRedis(std::unique_ptr<Redis> redis) {
  std::unique_lock<std::mutex> lock(mutex_);
  if (stop_) { return; }
  spdlog::info("Returning redis");
  pool_.push(std::move(redis));
  cond_.notify_one();
}

RedisConnectionPool::~RedisConnectionPool() {
  std::unique_lock<std::mutex> lock(mutex_);
  Stop();
  while (!pool_.empty()) {
    pool_.pop();
  }
}
