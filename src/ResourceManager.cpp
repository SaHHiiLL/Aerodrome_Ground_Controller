#include "./ResourceManager.hpp"
#include <fstream>
#include <sstream>
#include <string>

std::string ResourceManager::read_file(std::filesystem::path path) {
    std::ifstream file(this->resource_dir / path);
    if (!file.is_open()) {
        throw std::invalid_argument(
            "[-]ERROR: ResourceManager: Invalid file path");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
void ResourceManager::set_resource_dir_path(std::filesystem::path path) {
    this->resource_dir = path;
}
