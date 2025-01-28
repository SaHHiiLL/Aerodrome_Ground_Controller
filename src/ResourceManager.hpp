#pragma once

#include "raylib.h"
#include <filesystem>
#include <string>

// Singleton class
class ResourceManager {

public:
    // Reads a file from absolute path
    [[nodiscard]] static std::string read_file_abs(std::filesystem::path path);

    // Reads a file relative to [`ResourceManager::resource_dir`]
    [[nodiscard]] std::string read_file(std::filesystem::path path);
    void set_resource_dir_path(std::filesystem::path path);

    static ResourceManager &instance();

    Image get_airplane() const;

    ResourceManager(ResourceManager const &) = delete;
    void operator=(ResourceManager const &) = delete;

private:
    std::filesystem::path resource_dir = "./resource";

    ResourceManager() = default;
};
