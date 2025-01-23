#pragma once
#include <filesystem>
#include <raylib.h>
#include <unordered_map>

class ColourManager {
public:
    std::unordered_map<std::string, std::uint64_t> colours{};
    explicit ColourManager(std::filesystem::path resource_path);
    ColourManager() = default;
    ~ColourManager() = default;
    Color to_raylib(std::string key) { return GetColor(colours.at(key)); }
    bool is_valid(const std::string &key) const {
        return this->colours.contains(key);
    }
};
