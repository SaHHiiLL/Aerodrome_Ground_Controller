#pragma once

#include <filesystem>
#include <vector>

// Singleton class
class ResourceManager {

public:
    std::vector<std::string> readFile(std::filesystem::path path);
    void setResourceDirPath(std::filesystem::path path);

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
