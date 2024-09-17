//
// Created by summer on 2024/9/9.
//

#include "mysql_dao.h"
#include <mysql/jdbc.h>

#include <utility>

MysqlDao::MysqlDao(std::shared_ptr<MysqlConnectionPool> pool) : pool_(
    std::move(pool)) {
}

MysqlDao::~MysqlDao() = default;

uint64_t MysqlDao::RegisterUser(const std::string& username,
    const std::string& password, const std::string& email) const {
  const auto conn = pool_->GetConnection();
  if (conn == nullptr) {
    return 0;
  }
  try {
    conn->setAutoCommit(false);

    std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(
        "INSERT INTO `user` (`name`, `email`, `passwd`) VALUES (?, ?, ?)"));
    stmt->setString(1, username);
    stmt->setString(2, email);
    stmt->setString(3, password);

    if (!stmt->executeUpdate()) {
      spdlog::error("user registered failed!");
      return 0;
    }

    std::unique_ptr<sql::Statement> query_stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> result(
        query_stmt->executeQuery("SELECT LAST_INSERT_ID()"));
    result->absolute(1);
    const auto uid = result->getUInt64(1);
    conn->commit();
    return uid;
  } catch (sql::SQLException& e) {
    conn->rollback();
    spdlog::error(
        "SQLException in MysqlDao::RegisterUser: {} (MySQL error code: {}, SQLState: {})",
        e.what(), e.getErrorCode(), e.getSQLState());
  }
  return 0;
}

bool MysqlDao::ResetPassword(const std::string& username,
    const std::string& password, const std::string& email) const {
  const auto conn = pool_->GetConnection();
  if (conn == nullptr) {
    return false;
  }

  try {
    std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(
        "SELECT COUNT(*) FROM `user` WHERE `name` = ? and `email` = ?"));
    stmt->setString(1, username);
    stmt->setString(2, email);
    auto result_set = stmt->executeQuery();
    if (!result_set->absolute(1) || result_set->getInt(1) == 0) {
      spdlog::error("user {} not match email {}!", username, email);
      return false;
    }

    stmt.reset(conn->prepareStatement(
        "UPDATE `user` SET `passwd` = ? WHERE `name` = ? and `email` = ?"));
    stmt->setString(1, password);
    stmt->setString(2, username);
    stmt->setString(3, email);
    if (!stmt->executeUpdate()) {
      spdlog::error("user reset password failed!");
      return false;
    }
    return true;
  } catch (sql::SQLException& e) {
    spdlog::error(
        "SQLException in MysqlDao::ResetPassword: {} (MySQL error code: {}, SQLState: {})",
        e.what(), e.getErrorCode(), e.getSQLState());
  }

  return false;
}

bool MysqlDao::Login(const std::string& username,
    const std::string& password, UserInfo& user_info) const {
  const auto conn = pool_->GetConnection();
  if (conn == nullptr) return false;

  try {
    std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(
        "SELECT * FROM `user` WHERE `name`=? and `passwd` = ?"));
    stmt->setString(1, username);
    stmt->setString(2, password);
    auto result_set = stmt->executeQuery();
    if (!result_set->next()) {
      spdlog::error("user {} not match passwd {}!", username, password);
      return false;
    }

    user_info.name = username;
    user_info.passwd = password;
    user_info.email = result_set->getString("email");
    user_info.uid = result_set->getInt("uid");
    return true;
  } catch (sql::SQLException& e) {
    spdlog::error(
        "SQLException in MysqlDao::Login: {} (MySQL error code: {}, SQLState: {})",
        e.what(), e.getErrorCode(), e.getSQLState());
  }
  return false;
}
