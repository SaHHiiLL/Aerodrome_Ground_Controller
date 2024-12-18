#pragma once

#include "./Coordinates.hpp"
#include <array>
#include <vector>

class Runway {
    std::array<Coordinates, 4> coords;
    std::vector<Vector2> verties;
    Coordinates center_ref;
    float runway_heading; // will always be the higher number
    Color color;

public:
    Runway(std::array<Coordinates, 4> coords, Coordinates center_ref,
           float runway_heading, Color color);

    void draw();

private:
};
