#pragma once
#include <filesystem>
#include <raylib.h>
#include <unordered_map>

class Colours {
public:
    std::unordered_map<std::string, std::uint64_t> colours{};
    explicit Colours(std::filesystem::path resource_path);
    Colours() = default;
    ~Colours();
    Color to_raylib(std::string key) { return GetColor(colours.at(key)); }
    bool is_valid(const std::string &key) const {
        return this->colours.contains(key);
    }
};
