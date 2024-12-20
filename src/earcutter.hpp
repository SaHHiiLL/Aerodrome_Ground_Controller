#pragma once

#include "raylib.h"
#include <vector>

// WATCH: https://youtu.be/QAdfkylpYwc?si=kLimEaWqmi67CX6l

struct Triangle {
    Vector2 x1, x2, x3;

public:
    //
    // https://www.youtube.com/watch?v=HYAgJN3x4GA&t=224s
    bool is_point_inside(Vector2 p) {
        Vector2 a = this->x1;
        Vector2 b = this->x2;
        Vector2 c = this->x3;
        float area = 0.5f * (-b.y * c.x + a.y * (-b.x + c.x) +
                             a.x * (b.y - c.y) + b.x * c.y);
        float s =
            1.f / (2.f * area) *
            (a.y * c.x - a.x * c.y + (c.y - a.y) * p.x + (a.x - c.x) * p.y);
        float t =
            1.f / (2.f * area) *
            (a.x * b.y - a.y * b.x + (a.y - b.y) * p.x + (b.x - a.x) * p.y);

        return s > 0.f && t > 0.f && (s + t) < 1.f;
    }

    Triangle(Vector2 prev, Vector2 curr, Vector2 next)
        : x1(prev), x2(curr), x3(next) {}
    // TODO: this works for current set of points - However, some might present
    // themselves as clockwise - I must sort them aswell
    void draw() { DrawTriangle(x1, x2, x3, GREEN); }
    void draw(Color color) { DrawTriangle(x1, x2, x3, color); }
    void draw_outline() {
        DrawLineV(this->x1, this->x2, RAYWHITE);
        DrawLineV(this->x2, this->x3, RAYWHITE);
        DrawLineV(this->x3, this->x1, RAYWHITE);
    }
};

class EarCut {
private:
    bool is_convex(Vector2 prev, Vector2 curr, Vector2 next);
    float crossproduct(Vector2 a, Vector2 b);
    bool is_point_inside(Triangle triangle, Vector2 point);

public:
    std::vector<Triangle> earcut(std::vector<Vector2> &polygon);
};
