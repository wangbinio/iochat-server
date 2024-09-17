#include <jdbc/cppconn/connection.h>

#include "inc.h"
#include "server.h"
#include "config_manager.h"
#include "mysql_connection_pool.h"
#include "redis_manager.h"
#include <mysql/jdbc.h>

#include "mysql_manager.h"

void TestRedis();
void TestMysql();

int main() {
  spdlog::info("Hello World!");
  // TestRedis();
  // TestMysql();
  // return 0;
  try {
    uint16_t port = ConfigManager::GetInstance().GetInt("gate-server", "port");
    net::io_context io_context{1};

    net::signal_set signals(io_context, SIGINT, SIGTERM);
    signals.async_wait(
        [&io_context](boost::system::error_code, int signal_num) {
          spdlog::info("Signal {}", signal_num);
          io_context.stop();
        });

    std::make_shared<Server>(io_context, port)->Start();
    spdlog::info("Server started");
    io_context.run();
  } catch (std::exception& e) {
    spdlog::error("Error in main(): {}", e.what());
  }

  return 0;
}

void TestRedis() {
  using namespace sw::redis;

  // auto redis = Redis("tcp://123456@127.0.0.1:6379");
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back([i] {
      auto redis = RedisManager::GetInstance()->GetRedis();
      spdlog::info("redis address: {}", static_cast<void*>(redis.get()));

      std::string key = "key" + std::to_string(i);
      redis->set(key, std::to_string(i));
      auto val = redis->get(key);
      spdlog::info("{} : {}", key, val.value());

      std::string list = "list" + std::to_string(i);
      std::vector<std::string> vec{"a", "b", "c"};
      redis->del(list);
      redis->rpush(list, vec.begin(), vec.end());
      vec.clear();
      redis->lrange(list, 0, -1, std::back_inserter(vec));

      spdlog::info("{} {}", list, vec);
      // std::this_thread::sleep_for(std::chrono::seconds(1));
    });
  }
  for (auto&& thread : threads) thread.join();
}

void TestMysql() {
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back([i] {
      const auto str = std::to_string(i);
      auto uid = MysqlManager::GetInstance()->RegisterUser(str, str, str);
      spdlog::info("{} {}", str, uid);
    });
  }
  for (auto&& thread : threads) thread.join();
}
