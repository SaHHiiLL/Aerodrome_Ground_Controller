#pragma once

#include "./Coordinates.hpp"
#include "earcutter.hpp"
#include <array>
#include <vector>

class Quadrilateral {
    std::array<Coordinates, 4> coords;
    std::vector<Vector2> verties;
    Coordinates center_ref;
    Color color;
    std::vector<Triangle> triangles;

public:
    std::vector<Triangle> triangle() { return this->triangles; }
    Quadrilateral(std::array<Coordinates, 4> coords, Coordinates center_ref,
                  Color color);

    Quadrilateral(std::vector<Vector2> vertices, Coordinates center_ref,
                  Color color);
    void draw();
};
