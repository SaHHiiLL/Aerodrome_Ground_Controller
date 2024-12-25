#pragma once
#include <filesystem>
#include <raylib.h>
#include <unordered_map>

class Colours {
private:
    std::unordered_map<std::string, std::uint64_t> colours;

public:
    Colours(std::filesystem::path resource_path);
    Color to_raylib(std::string key) { return GetColor(colours.at(key)); }
    bool is_valid(std::string key) { return this->colours.contains(key); }
};
