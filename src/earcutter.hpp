#pragma once

#include "raylib.h"
#include <vector>

struct Triangle {
    Vector2 x1, x2, x3;

public:
    void draw() { DrawTriangle(x1, x2, x3, GREEN); }
    void draw(Color color) { DrawTriangle(x1, x2, x3, color); }
    bool is_point_inside(Vector2 point);
};
class EarCut {
    bool is_convex();
    std::vector<Triangle> earcut(std::vector<Vector2> &polygon);
};
