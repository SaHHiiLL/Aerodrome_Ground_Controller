//
// Created by Sahil on 9/18/24.
//

#pragma once

#include "airport/Airport.hpp"
#include "colours/Colours.hpp"
#include <raylib.h>

class Game {
private:
    Camera2D *camera;
    // Heap allocated colours;
    Colours colours;
    Airport *airport;

public:
    Game(Camera2D *cam);
    Game() {};

    void update();
    void draw();
    void draw_outline();
    void handle_input();
    float zoom_factor = 1;
};
