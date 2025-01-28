#pragma once

#include "./Coordinate.hpp"
#include "earcutter.hpp"
#include <array>
#include <vector>

// A class to represent a 4 sized Quadrilateral with acute angles
class Quadrilateral {
    std::array<Coordinate, 4> coords;
    std::vector<Vector2> verties;
    Coordinate center_ref;
    Color color;
    std::vector<Triangle> triangles;

public:
    std::vector<Triangle> triangle();
    Quadrilateral(std::array<Coordinate, 4> coords, Coordinate center_ref,
                  Color color);

    Quadrilateral(std::vector<Vector2> vertices, Coordinate center_ref,
                  Color color);
    void draw();
};
