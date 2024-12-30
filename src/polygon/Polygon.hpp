#pragma once

#include "../Coordinate.hpp"
#include "../earcutter.hpp"
#include "raylib.h"
#include <vector>

class Polygon {
private:
    std::vector<Vector2> vertices;
    std::vector<Triangle> triangles;

    Color color = RED;
    std::vector<Coordinate> coordinates;

public:
    Polygon(std::vector<Coordinate> coords, Color color);
    Polygon() = default;

    void add_coordinate(const Coordinate coord) {
        this->coordinates.push_back(coord);
    }
    void set_color(const Color color) { this->color = color; }
    [[nodiscard]] bool is_empty() const { return this->coordinates.empty(); }
    [[nodiscard]] size_t size() const { return this->coordinates.size(); }
    std::vector<Coordinate> &coords() { return this->coordinates; };

    void triangulate(Coordinate center_ref, Vector2 screen_center);
    void draw(Color color);
    void draw();
    void draw_outline();
};
