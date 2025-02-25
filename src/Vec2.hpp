#pragma once
#include "raylib.h"
struct Vec2 {
private:
    double x;
    double y;

public:
    Vec2(double x, double y) : x(x), y(y) {};
    operator Vector2() const { return {(float)x, (float)y}; }
};
