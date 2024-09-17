//
// Created by summer on 2024/9/6.
//

#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "inc.h"
#include <INIReader.h>
#include <filesystem>
#include <memory>


class ConfigManager {
public:
  static ConfigManager& GetInstance() {
    static ConfigManager instance;
    return instance;
  }

  [[nodiscard]] std::string GetString(
      const std::string& section,
      const std::string& key,
      const std::string& default_value = "") const {
    return reader_->GetString(section, key, default_value);
  }

  [[nodiscard]] int GetInt(const std::string& section,
      const std::string& key,
      const int default_value = 0) const {
    return reader_->GetInteger(section, key, default_value);
  }

private:
  ConfigManager() {
    namespace fs = std::filesystem;
    const fs::path current_path = fs::current_path();
    const fs::path config_path = current_path / "config.ini";
    if (fs::exists(config_path)) {
      reader_ = std::make_unique<INIReader>("config.ini");
    } else {
      spdlog::error("Config File Not Found");
      assert(false);
    }
  }

  std::unique_ptr<INIReader> reader_;
};


#endif //CONFIG_MANAGER_H
