#pragma once

#include "../Coordinates.hpp"
#include "../earcutter.hpp"
#include "raylib.h"
#include <vector>

class Polygon {
private:
    std::vector<Vector2> vertices;
    std::vector<Triangle> triangles;

    Color color = RED;
    std::vector<Coordinates> coordinates;

public:
    Polygon(std::vector<Coordinates> coords, Color color);
    Polygon() {};

    void add_coordinate(Coordinates coord) {
        this->coordinates.push_back(coord);
    }
    void set_color(Color color) { this->color = color; }
    bool is_empty() { return this->coordinates.empty(); }
    size_t size() { return this->coordinates.size(); }
    std::vector<Coordinates> &coords() { return this->coordinates; };

    void triangulate(Coordinates center_ref, Vector2 screen_center);
    void draw(Color color);
    void draw();
};
