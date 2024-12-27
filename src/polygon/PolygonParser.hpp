#pragma once
#include "../polygon/Polygon.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class PolygonParser {
private:
    std::string input;

public:
    PolygonParser(std::string input) { this->input = input; }

    std::vector<Polygon>
    parse(std::unordered_map<std::string, uint64_t> &color_map);
};
