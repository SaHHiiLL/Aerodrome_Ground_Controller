#include "./Quadrilateral.hpp"
#include "./Constants.hpp"
#include "raylib.h"
#include <delaunator.hpp>

Quadrilateral::Quadrilateral(std::vector<Vector2> vertices,
                             Coordinate center_ref, Color color) {
    std::vector<double> cc;

    for (auto &c : vertices) {
        cc.push_back(c.x);
        cc.push_back(c.y);
    }

    Delaunator d(cc);

    for (size_t i = 0; i < d.triangles.size(); i += 3) {
        Vector2 x1 = {
            (float)d.coords[2 * d.triangles[i]],
            /*tx0 */ (float)d.coords[(2 * d.triangles[i]) + 1]}; // ty0 };
        Vector2 x2 = {
            (float)d.coords[2 * d.triangles[i + 1]],
            /*tx1 */ (float)d.coords[(2 * d.triangles[i + 1]) + 1]}; // ty1 }:
        Vector2 x3 = {
            (float)d.coords[2 * d.triangles[i + 2]],
            /*tx2 */ (float)d.coords[(2 * d.triangles[i + 2]) + 1]}; // ty2 };

        this->triangles.emplace_back(x1, x2, x3);
    }
}

Quadrilateral::Quadrilateral(std::array<Coordinate, 4> coords,
                             Coordinate center_ref, Color color)
    : coords(coords), center_ref(center_ref), color(color) {
    std::vector<double> cc;

    for (auto &c : coords) {
        Vector2 xy =
            c.geo_to_screen_by_refrence(center_ref, DRAW_SCALE, SCREEN_CENTER);
        cc.push_back(xy.x);
        cc.push_back(xy.y);
    }

    // Convert the coordinates to double;
    Delaunator d(cc);

    for (size_t i = 0; i < d.triangles.size(); i += 3) {
        Vector2 x1 = {
            (float)d.coords[2 * d.triangles[i]],
            /*tx0 */ (float)d.coords[(2 * d.triangles[i]) + 1]}; // ty0 };
        Vector2 x2 = {
            (float)d.coords[2 * d.triangles[i + 1]],
            /*tx1 */ (float)d.coords[(2 * d.triangles[i + 1]) + 1]}; // ty1 }:
        Vector2 x3 = {
            (float)d.coords[2 * d.triangles[i + 2]],
            /*tx2 */ (float)d.coords[(2 * d.triangles[i + 2]) + 1]}; // ty2 };

        this->verties.push_back(x1);
        this->verties.push_back(x2);
        this->verties.push_back(x3);
    }
}

void Quadrilateral::draw() {
    for (size_t i = 0; i < this->verties.size(); i += 3) {
        DrawTriangle(this->verties[i], this->verties[i + 1],
                     this->verties[i + 2], this->color);
    }
}
std::vector<Triangle> Quadrilateral::triangle() {
    return std::move(this->triangles);
}
