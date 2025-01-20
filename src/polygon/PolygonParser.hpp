#pragma once
#include "../colours/Colours.hpp"
#include "../polygon/Polygon.hpp"
#include <string>
#include <vector>

class PolygonParser {
private:
    std::string input;

public:
    PolygonParser(std::string input) { this->input = input; }

    [[nodiscard]] std::vector<Polygon> parse(Colours &colors);
};
