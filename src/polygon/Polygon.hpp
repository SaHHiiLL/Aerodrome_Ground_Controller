#pragma once

#include "../Coordinates.hpp"
#include "../earcutter.hpp"
#include "raylib.h"
#include <filesystem>
#include <vector>

class Polygon {
private:
    std::vector<Vector2> vertices;
    std::vector<Triangle> triangles;

public:
    Polygon();
    Polygon(std::vector<Coordinates> coords, Coordinates center_ref,
            Vector2 screen_center);

    Polygon(std::filesystem::path path, Coordinates center_ref,
            Vector2 screen_center);

    void triangulate();
    void draw(Color color);
    void draw();
};
