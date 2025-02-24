#pragma once
#include "../Coordinate.hpp"
#include "raylib.h"

class AirportLabel {
    std::string data;
    Coordinate coords;
    Color color;
    Coordinate world_center_ref;
    Vector2 position;

public:
    AirportLabel() = default;
    AirportLabel(std::string data, Coordinate coords, Coordinate center_ref,
                 const Color color);
    void draw(const Camera2D &cam) const;
};
