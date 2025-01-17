#pragma once

#include "raylib.h"
#include <filesystem>
#include <string>
#include <sys/types.h>

// Singleton class
class ResourceManager {

public:
    std::string read_file_abs(std::filesystem::path path);
    void set_resource_dir_path(std::filesystem::path path);

    static ResourceManager &Instance() {
        static ResourceManager Instance;
        return Instance;
    }

    Image get_airplane();

private:
    std::filesystem::path resource_dir = "./resource";

    ResourceManager(ResourceManager const &) = delete;
    void operator=(ResourceManager const &) = delete;

    ResourceManager() {}
};
