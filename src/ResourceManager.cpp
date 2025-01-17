#include "./ResourceManager.hpp"
#include "AGCException.hpp"
#include <fstream>
#include <sstream>
#include <string>

std::string ResourceManager::read_file_abs(std::filesystem::path path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw AGCException("[-]ERROR: ResourceManager: Invalid file path");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}
void ResourceManager::set_resource_dir_path(std::filesystem::path path) {
    this->resource_dir = path;
}

Image ResourceManager::get_airplane() {
    std::string path(resource_dir / "images/airplane-logo-png_seeklogo.png");
    Image img = LoadImage(path.c_str());
    return img;
}
