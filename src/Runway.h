#ifndef AERODROME_GROUND_CONTROLLER_RUNWAY_H
#define AERODROME_GROUND_CONTROLLER_RUNWAY_H

#include "Coordinates.h"
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

#endif
