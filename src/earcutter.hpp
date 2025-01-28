#pragma once

#include "raylib.h"
#include <vector>

// TODO: use the sweep line algorithm

// WATCH: https://youtu.be/QAdfkylpYwc?si=kLimEaWqmi67CX6l

struct Triangle {
    Vector2 x1, x2, x3;

public:
    //
    // https://www.youtube.com/watch?v=HYAgJN3x4GA&t=224s
    bool is_point_inside(Vector2 p) const;

    Triangle(const Vector2 prev, const Vector2 curr, const Vector2 next);
    // TODO: this works for current set of points - However, some might present
    // themselves as clockwise - I must sort them aswell
    void draw() const;
    void draw(Color color) const;
    void draw_outline() const;
};

class EarCut {
private:
    bool is_convex(Vector2 prev, Vector2 curr, Vector2 next);
    float crossproduct(Vector2 a, Vector2 b);
    bool is_point_inside(Triangle triangle, Vector2 point);

public:
    std::vector<Triangle> earcut(const std::vector<Vector2> &polygon);
};
