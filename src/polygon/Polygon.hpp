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
    void convert_coordinates_to_vertices(Coordinate centre_ref);

    void set_color(const Color color);
    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] size_t size() const;
    std::vector<Coordinate> &coords();

    // Uses `earcut` algorithm to triangulate screeen space vertices
    // @param center_ref - centre of the polygon
    void triangulate(Coordinate center_ref);

    // Draws the triangle in solid color
    void draw(Color color);
    void draw() const;
    // Draws each triangle's border
    void draw_triangle_outlines() const;
    // Draws the perimeter of the polygon
    void draw_outline() const;
};
