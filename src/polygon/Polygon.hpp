#pragma once

#include "../Coordinate.hpp"
#include "../earcutter.hpp"
#include "raylib.h"
#include <vector>

class Polygon {
private:
    // Vertices converted to screen space
    std::vector<Vector2> vertices;
    // triangles that makeup the polygon
    std::vector<Triangle> triangles;

    // Default color
    Color color = RED;
    // Vertices as real world space
    std::vector<Coordinate> coordinates;

public:
    Polygon(std::vector<Coordinate> coords, Color color);
    Polygon() = default;

    // Adds more world space vertices
    void add_coordinate(const Coordinate coord) {
        this->coordinates.push_back(coord);
    }

    // Converts real words space vertices to screen space vertices
    // NOTE: appends to `this->vertices`
    void convert_coordinates_to_vertices(Coordinate centre_ref,
                                         Vector2 screen_center);

    void set_color(const Color color) { this->color = color; }
    [[nodiscard]] bool is_empty() const { return this->coordinates.empty(); }
    [[nodiscard]] size_t size() const { return this->coordinates.size(); }
    std::vector<Coordinate> &coords() { return this->coordinates; };

    // Uses `earcut` algorithm to triangulate screeen space vertices
    // @param center_ref - centre of the polygon
    // @param screen_center - centre of the window
    void triangulate(Coordinate center_ref, Vector2 screen_center);

    // Draws the triangle in solid color
    void draw(Color color);
    void draw();
    // Draws each triangle's border
    void draw_triangle_outlines();
    // Draws the perimeter of the polygon
    void draw_outline();
};
