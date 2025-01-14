#pragma once
#include "../Coordinate.hpp"
#include "raylib.h"

struct Label {
    const std::string data;
    const Coordinate coords;
    const Color &color;
};
