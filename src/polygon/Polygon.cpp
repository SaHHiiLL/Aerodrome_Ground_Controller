
#include "./Polygon.hpp"
#include "../Coordinates.hpp"
#include "../earcutter.hpp"
#include "raylib.h"
#include <vector>

Polygon::Polygon(std::vector<Coordinates> coords, Color color)
    : coordinates(coords), color(color) {}

void Polygon::triangulate(Coordinates center_ref, Vector2 screen_center) {
    for (auto c : this->coordinates) {
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

void draw1(Vector2 x1, Vector2 x2, Vector2 x3, Color color) {
    DrawTriangle(x1, x2, x3, color);
}

void draw2(Vector2 x1, Vector2 x2, Vector2 x3, Color color) {
    DrawTriangle(x1, x2, x3, color);
}

void draw3(Vector2 x1, Vector2 x2, Vector2 x3, Color color) {
    DrawTriangle(x1, x2, x3, color);
}

void draw4(Vector2 x1, Vector2 x2, Vector2 x3, Color color) {
    DrawTriangle(x1, x2, x3, color);
}

void draw5(Vector2 x1, Vector2 x2, Vector2 x3, Color color) {
    DrawTriangle(x1, x2, x3, color);
}

void draw6(Vector2 x1, Vector2 x2, Vector2 x3, Color color) {
    DrawTriangle(x1, x2, x3, color);
}

void Polygon::draw() {
    for (size_t i = 0; i < this->triangles.size(); i++) {
        // DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
        //              this->triangles[i].x3, this->color);

        draw1(this->triangles[i].x1, this->triangles[i].x2,
              this->triangles[i].x3, this->color);
        draw2(this->triangles[i].x3, this->triangles[i].x2,
              this->triangles[i].x1, this->color);
        draw3(this->triangles[i].x1, this->triangles[i].x3,
              this->triangles[i].x2, this->color);
        draw4(this->triangles[i].x2, this->triangles[i].x1,
              this->triangles[i].x3, this->color);
        draw5(this->triangles[i].x2, this->triangles[i].x3,
              this->triangles[i].x1, this->color);
        draw6(this->triangles[i].x3, this->triangles[i].x1,
              this->triangles[i].x2, this->color);
    }
}
