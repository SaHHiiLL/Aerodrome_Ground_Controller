#pragma once
#include <utility>

#include "../Constants.hpp"
#include "../Coordinate.hpp"
#include "raylib.h"

class AirportLabel {
    std::string data;
    Coordinate coords;
    Color color;
    Coordinate world_center_ref;
    Vector2 position;

public:
    AirportLabel() {};
    AirportLabel(std::string data, Coordinate coords, Coordinate center_ref,
                 Color color)
        : world_center_ref(center_ref), data(std::move(data)), coords(coords) {
        this->color = color;
        float sH = GetScreenHeight();
        float sW = GetScreenWidth();
        Vector2 screen_center = {sH / 2, sW / 2};
        this->position =
            coords.geo_to_screen_by_refrence(world_center_ref, screen_center);
    }
    void draw() const {
        const Font *font = Get_Font();
        DrawTextEx(*font, this->data.c_str(), this->position, 12, 0,
                   this->color);
    }
};
