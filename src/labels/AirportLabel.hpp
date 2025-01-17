#pragma once
#include "../Coordinate.hpp"
#include "raylib.h"
#include <iterator>

class AirportLabel {
    std::string data;
    Coordinate coords;
    Color color;
    Coordinate world_center_ref;
    Vector2 position;

public:
    AirportLabel() {};
    AirportLabel(std::string data, Coordinate coords, Coordinate center_ref,
                 Color color = RED)
        : world_center_ref(center_ref), data(data), coords(coords),
          color(color) {
        float sH = GetScreenHeight();
        float sW = GetScreenWidth();
        Vector2 screen_center = {sH / 2, sW / 2};
        this->position =
            coords.geo_to_screen_by_refrence(world_center_ref, screen_center);
    }
    void draw() {
        DrawText(this->data.c_str(), this->position.x, this->position.y, 12,
                 this->color);
    }
};
