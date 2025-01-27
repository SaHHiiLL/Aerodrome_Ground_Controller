#pragma once

#include "../Coordinate.hpp"
#include <utility>
#include <vector>

class GeoMarkings {
private:
    using Line = std::pair<Coordinate, Coordinate>;
    std::vector<Line> lines;
    Color color = YELLOW;

public:
};
