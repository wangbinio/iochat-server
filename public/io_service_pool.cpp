//
// Created by summer on 2024/9/6.
//

#include "io_service_pool.h"

IoServicePool::~IoServicePool() {
  Stop();
  spdlog::info("IoServicePool::~IoServicePool");
}

IoServicePool::IoService& IoServicePool::GetIoService() {
  if (next_io_service_ >= io_services_.size()) {
    next_io_service_ = 0;
  }

  return io_services_[next_io_service_++];
}

void IoServicePool::Stop() {
  for (auto& work : works_) {
    work->get_io_context().stop();
    work.reset();
  }

  for (auto& thread : threads_) {
    thread.join();
  }
}

IoServicePool::IoServicePool(const std::size_t pool_size)
  : io_services_(pool_size), works_(pool_size), next_io_service_(0) {
  for (std::size_t i = 0; i < pool_size; i++) {
    works_[i] = std::make_unique<Work>(io_services_[i]);
  }

  for (std::size_t i = 0; i < pool_size; i++) {
    threads_.emplace_back([this, i]() {
      io_services_[i].run();
    });
  }
}
