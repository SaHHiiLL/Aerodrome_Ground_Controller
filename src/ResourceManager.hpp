#pragma once

#include <filesystem>
#include <string>

// Singleton class
class ResourceManager {

public:
    std::string read_file(std::filesystem::path path);
    void set_resource_dir_path(std::filesystem::path path);

private:
    std::filesystem::path resourceDir = "../resource";

    static ResourceManager &Instance() {
        static ResourceManager Instance;
        return Instance;
    }

    ResourceManager(ResourceManager const &) = delete;
    void operator=(ResourceManager const &) = delete;

    ResourceManager() {}
};
