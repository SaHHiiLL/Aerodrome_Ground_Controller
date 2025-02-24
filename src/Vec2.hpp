#pragma once
#include "raylib.h"
struct Vec2 {
private:
    double x;
    double y;

public:
    operator Vector2() const { return {(float)x, (float)y}; }
};
