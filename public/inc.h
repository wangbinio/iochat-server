//
// Created by summer on 2024/9/4.
//

#ifndef INC_H
#define INC_H
#include <queue>
#include <memory>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ranges.h>
#include <sw/redis++/redis++.h>
#include "export.h"

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

enum ErrorCode {
  kSuccess = 0,
  kErrorJson = 1, //Json解析错误
  kErrorNetwork = 2, //网络错误
  kRPCFailed = 1002, //RPC请求错误
  kVerifyExpired = 1003, //验证码过期
  kVerifyCodeErr = 1004, //验证码错误
  kUserExist = 1005, //用户已经存在
  kPasswdErr = 1006, //密码错误
  kEmailNotMatch = 1007, //邮箱不匹配
  kPasswdUpFailed = 1008, //更新密码失败
  kPasswdInvalid = 1009, //密码更新失败
  kTokenInvalid = 1010, //Token失效
  kUidInvalid = 1011, //uid无效
};

static const std::string kCodePrefix = "code_";
static const std::string kUserIpPrefix = "uip_";
static const std::string kUserTokenPrefix = "utoken_";
static const std::string kIpCountPrefix = "ipcount_";
static const std::string kUserBaseInfo = "ubaseinfo_";
static const std::string kLoginCount = "logincount";

template <typename T, typename Del>
struct UniquePtrDeleter {
  using pointer = T*;

  explicit UniquePtrDeleter(Del deleter) : deleter_(deleter) {
  }

  void operator()(pointer* ptr) const { deleter_(ptr); }

private:
  Del deleter_;
};

template <typename T, typename Del>
auto MakeUniquePtrWithDeleter(T* t, Del&& del) {
  using Deleter_t = UniquePtrDeleter<T, Del>;
  return std::unique_ptr<T, Deleter_t>(t, Deleter_t(std::forward<Del>(del)));
}

inline std::vector<std::string> split(const std::string& str, const
    std::string& delim = ",") {
  std::vector<std::string> res;
  for (auto first = str.data(), second = str.data(), last = first + str.size();
       second != last && first != last; first = second + 1) {
    second = std::find_first_of(first, last, std::cbegin(delim),
        std::cend(delim));
    if (first != second) {
      res.emplace_back(first, second);
    }
  }
  return res;
}

inline std::vector<std::string_view> split(std::string_view str,
    std::string_view delim = ",") {
  std::vector<std::string_view> res;
  for (auto first = str.data(), second = str.data(), last = first + str.size();
       second != last && first != last; first = second + 1) {
    if (first != second) {
      res.emplace_back(first, second - first);
    }
  }
  return res;
}
#endif //INC_H
