
#include "./Polygon.hpp"
#include "../Coordinates.hpp"
#include "../earcutter.hpp"
#include "raylib.h"
#include <vector>

Polygon::Polygon(std::vector<Coordinates> coords, Color color)
    : coords(coords), color(color) {}

void Polygon::triangulate(Coordinates center_ref, Vector2 screen_center) {
    for (auto c : this->coords) {
        this->vertices.push_back(
            c.geo_to_screen_by_refrence(center_ref, screen_center));
    }
    EarCut earcut;
    this->triangles = earcut.earcut(this->vertices);
}

void Polygon::draw(Color color) {
    for (size_t i = 0; i < this->triangles.size(); i++)
        DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
                     this->triangles[i].x3, color);
}

void Polygon::draw() {
    for (size_t i = 0; i < this->triangles.size(); i++)
        DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
                     this->triangles[i].x3, this->color);
}
