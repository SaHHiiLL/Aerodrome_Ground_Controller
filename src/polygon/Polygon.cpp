
#include "./Polygon.hpp"
#include "../Coordinate.hpp"
#include "../Quadrilateral.hpp"
#include "../earcutter.hpp"
#include "raylib.h"
#include <vector>

Polygon::Polygon(std::vector<Coordinate> coords, Color color)
    : coordinates(coords), color(color) {}

void Polygon::triangulate(Coordinate center_ref, Vector2 screen_center) {
    for (size_t i = 0; i < coordinates.size(); i++) {
        this->vertices.push_back(coordinates[i].geo_to_screen_by_refrence(
            center_ref, screen_center));
    }
    if (this->vertices.size() > 4) {
        EarCut earcut;
        this->triangles = earcut.earcut(this->vertices);
    } else {
        // Quadd
        Quadrilateral quad = Quadrilateral{this->vertices, center_ref, color};
        this->triangles = quad.triangle();
    }
}

void Polygon::draw_triangle_outlines() {
    for (size_t i = 0; i < this->triangles.size(); i++) {
        this->triangles[i].draw_outline();
    }
}

void Polygon::draw_outline() {
    for (size_t i = 1; i < this->vertices.size(); i++) {
        DrawLineV(this->vertices[i - 1], this->vertices[i], WHITE);
    }
    DrawLineV(this->vertices[0], this->vertices[this->vertices.size() - 1],
              WHITE);
}

void Polygon::convert_coordinates_to_vertices(Coordinate centre_ref,
                                              Vector2 screen_center) {
    for (auto &coords : this->coordinates) {
        this->vertices.push_back(
            coords.geo_to_screen_by_refrence(centre_ref, screen_center));
    }
}

void Polygon::draw(Color color) {
    for (size_t i = 0; i < this->triangles.size(); i++)
        DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
                     this->triangles[i].x3, color);
}

void Polygon::draw() {
    for (size_t i = 0; i < this->triangles.size(); i++) {
        DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
                     this->triangles[i].x3, this->color);
    }
}
