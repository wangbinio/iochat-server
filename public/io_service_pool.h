//
// Created by summer on 2024/9/6.
//

#ifndef IO_SERVICE_POOL_H
#define IO_SERVICE_POOL_H

#include <vector>
#include <thread>
#include <boost/asio.hpp>

#include "singleton.h"


class PUBLIC_TOOLS_API IoServicePool : public Singleton<IoServicePool> {
  friend class Singleton<IoServicePool>;

public:
  using IoService = boost::asio::io_service;
  using Work = boost::asio::io_service::work;
  using WorkPtr = std::unique_ptr<Work>;

  ~IoServicePool();

  IoService& GetIoService();
  void Stop();

private:
  explicit IoServicePool(std::size_t pool_size = 2);

  std::vector<IoService> io_services_;
  std::vector<WorkPtr> works_;
  std::vector<std::thread> threads_;
  std::size_t next_io_service_;
};


#endif //IO_SERVICE_POOL_H
