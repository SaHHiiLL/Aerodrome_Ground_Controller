#include "./ResourceManager.hpp"
#include "raylib.h"
#include <string>

std::string ResourceManager::read_file_abs(std::filesystem::path path) {
    return LoadFileText(path.c_str());
}

std::string ResourceManager::read_file(std::filesystem::path path) {
    return LoadFileText((this->resource_dir / path).c_str());
}

void ResourceManager::set_resource_dir_path(std::filesystem::path path) {
    this->resource_dir = path;
}

Image ResourceManager::get_airplane() const {
    std::string path(resource_dir / "images/airplane-logo-png_seeklogo.png");
    Image img = LoadImage(path.c_str());
    return img;
}
