#pragma once
#include "./earcutter.hpp"

class Sweepline {
public:
    std::vector<Triangle> sweepline(const std::vector<Vector2> &polygon);

private:
};
