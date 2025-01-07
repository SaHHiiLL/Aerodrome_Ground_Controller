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

    // INFO: this function should only be used for debugging
    // it just converts the outeredges of the polygon
    // effectivly useful for visualizing the polygon when paried with
    // `draw_triangle_outlines`
    void convert_coordinates_to_vertices(Coordinate centre_ref,
                                         Vector2 screen_center);
    void set_color(const Color color) { this->color = color; }
    [[nodiscard]] bool is_empty() const { return this->coordinates.empty(); }
    [[nodiscard]] size_t size() const { return this->coordinates.size(); }
    std::vector<Coordinate> &coords() { return this->coordinates; };

    void triangulate(Coordinate center_ref, Vector2 screen_center);
    void draw(Color color);
    void draw();
    void draw_triangle_outlines();
    void draw_outline();
};
