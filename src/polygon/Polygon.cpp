
#include "./Polygon.hpp"
#include "../Constants.hpp"
#include "../Coordinate.hpp"
#include "../Quadrilateral.hpp"
#include "../earcutter.hpp"

#include "raylib.h"
#include <vector>

Polygon::Polygon(std::vector<Coordinate> coords, Color color)
    : coordinates(coords), color(color) {}

void Polygon::triangulate(Coordinate center_ref) {
    this->convert_coordinates_to_vertices(center_ref);
    if (this->vertices.size() > 4) {
        EarCut earcut;
        this->triangles = earcut.earcut(this->vertices);
    } else {
        // Quad
        Quadrilateral quad = Quadrilateral{this->vertices, center_ref, color};
        this->triangles = quad.triangle();
    }
}

void Polygon::draw_triangle_outlines() const {
    for (auto &triangle : this->triangles) {
        triangle.draw_outline();
    }
}

void Polygon::draw_outline() const {
    for (size_t i = 1; i < this->vertices.size(); i++) {
        DrawLineV(this->vertices[i - 1], this->vertices[i], WHITE);
    }
    DrawLineV(this->vertices[0], this->vertices[this->vertices.size() - 1],
              WHITE);
}

void Polygon::convert_coordinates_to_vertices(Coordinate centre_ref) {
    this->vertices.reserve(this->coords().size());
    for (auto &coords : this->coordinates) {
        this->vertices.push_back(
            coords.geo_to_screen_by_refrence(centre_ref, SCREEN_CENTER));
    }
}

void Polygon::draw(Color color) {
    for (auto &triangle : this->triangles)
        DrawTriangle(triangle.x1, triangle.x2, triangle.x3, color);
}

void Polygon::draw() const {
    for (const auto &triangle : this->triangles) {
        DrawTriangle(triangle.x1, triangle.x2, triangle.x3, this->color);
    }
}
void Polygon::set_color(const Color color) { this->color = color; }

bool Polygon::is_empty() const { return this->coordinates.empty(); }

size_t Polygon::size() const { return this->coordinates.size(); }

std::vector<Coordinate> &Polygon::coords() { return this->coordinates; };
