#pragma once
#include "../colours/ColourManager.hpp"
#include "../polygon/Polygon.hpp"
#include <string>
#include <vector>

class PolygonParser {
private:
    std::string input;

public:
    PolygonParser(std::string input) : input(input) {}

    [[nodiscard]] std::vector<Polygon> parse(ColourManager &colors);
};
