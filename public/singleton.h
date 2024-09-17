#pragma once
#include <typeinfo>
#include "inc.h"

template <typename T>
class Singleton {
public:
  static std::shared_ptr<T> GetInstance() {
    static std::shared_ptr<T> instance(new T);
    return instance;
  }

  void PrintAddress() {
    spdlog::info("{}'s address={}\n", typeid(*this).name(),
        static_cast<void*>(this));
  }

  ~Singleton() { spdlog::info("{} destructed\n", typeid(*this).name()); }

  Singleton(const Singleton<T>&) = delete;
  Singleton(Singleton<T>&&) = delete;
  Singleton& operator=(const Singleton<T>&) = delete;
  Singleton& operator=(Singleton<T>&&) = delete;

protected:
  Singleton() = default;
};
