#pragma once

#include "raylib.h"
#include <filesystem>
#include <string>

// Singleton class
class ResourceManager {

public:
    static std::string read_file(std::filesystem::path path);
    void set_resource_dir_path(std::filesystem::path path);

    static ResourceManager &Instance() {
        static ResourceManager Instance;
        return Instance;
    }

    Image get_airplane() const;

private:
    std::filesystem::path resource_dir = "./resource";

    ResourceManager(ResourceManager const &) = delete;
    void operator=(ResourceManager const &) = delete;

    ResourceManager() = default;
};
