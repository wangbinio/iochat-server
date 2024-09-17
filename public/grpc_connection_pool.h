//
// Created by summer on 2024/9/14.
//

#ifndef GRPC_CONNECTION_POOL_H
#define GRPC_CONNECTION_POOL_H

#include "inc.h"
#include <grpcpp/grpcpp.h>

template <typename T,
  typename SFINEA=std::void_t<typename T::Stub, decltype(&T::NewStub)>>
class GrpcConnectionPool {
public:
  using Stub = typename T::Stub;

  GrpcConnectionPool(const std::size_t pool_size, const std::string& host,
      const std::string& port) {
    const auto url = host + ":" + port;
    for (std::size_t i = 0; i < pool_size; ++i) {
      connections_.emplace(T::NewStub(grpc::CreateChannel(url,
          grpc::InsecureChannelCredentials())));
    }
  }

  ~GrpcConnectionPool() {
    std::unique_lock<std::mutex> lock(mutex_);
    Close();
    while (!connections_.empty()) {
      connections_.pop();
    }
  }

  std::unique_ptr<Stub, std::function<void(Stub*)>> GetConnection() {
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this] {
      if (stop_) return true;
      return !connections_.empty();
    });

    if (stop_) return nullptr;
    auto connection = std::move(connections_.front());
    connections_.pop();
    // spdlog::info("Rpc Connection Get {}, address = {}\n",
    //     typeid(*(connection.get())).name(),
    //     static_cast<void*>(connection.get()));
    return {connection.release(), [this](Stub* stub) {
      ReturnConnection(std::unique_ptr<Stub>(stub));
    }};
  }

  void Close() {
    stop_ = true;
    cond_.notify_all();
  }

private:
  void ReturnConnection(std::unique_ptr<Stub> stub) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (stop_) return;
    // spdlog::info("Rpc Connection Return {}, address = {}\n",
    //     typeid(*(stub.get())).name(), static_cast<void*>(stub.get()));
    connections_.emplace(std::move(stub));
    cond_.notify_all();
  }

  std::atomic_bool stop_{false};
  std::mutex mutex_;
  std::condition_variable cond_;
  std::queue<std::unique_ptr<Stub>> connections_;
};

#endif //GRPC_CONNECTION_POOL_H
