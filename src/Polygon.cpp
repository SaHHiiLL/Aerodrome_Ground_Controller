
#include "./Polygon.hpp"
#include "./earcutter.hpp"
#include "Coordinates.hpp"
#include "raylib.h"

void Polygon::triangulate() {
    EarCut earcut;
    this->triangles = earcut.earcut(vertices);
}

Polygon::Polygon(std::vector<Coordinates> coords, Coordinates center_ref,
                 Vector2 screen_center) {
    vertices.reserve(coords.size());
    for (auto c : coords) {
        vertices.push_back(c.GeoToScreenInRefrence(center_ref, screen_center));
    }

    this->triangulate();
}

void Polygon::draw(Color color) {
    for (size_t i = 0; i < this->triangles.size(); i++)
        DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
                     this->triangles[i].x3, color);
}

void Polygon::draw() {
    for (size_t i = 0; i < this->triangles.size(); i++)
        DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
                     this->triangles[i].x3, RED);
}
