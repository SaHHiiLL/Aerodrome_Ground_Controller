//
// Created by Sahil on 9/18/24.
//

#pragma once

#include "airport/Airport.hpp"
#include "colours/ColourManager.hpp"
#include <raylib.h>

class Game {
private:
    Camera2D *camera;
    // Heap allocated colours;
    ColourManager colours;
    Airport *airport;

public:
    Game(Camera2D *cam);
    Game() = default;

    void update();
    void draw() const;
    void draw_outline();
    void handle_input() const;
    float zoom_factor = 1;
};
