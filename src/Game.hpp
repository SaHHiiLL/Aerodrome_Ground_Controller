//
// Created by Sahil on 9/18/24.
//

#pragma once

#include "Runway.hpp"
#include "colours/Colours.hpp"
#include <raylib.h>
#include <vector>

class Game {
private:
    Camera2D *camera;
    std::vector<Runway *> runways;
    Colours &colours;

public:
    Game(Camera2D *cam, Colours &colours);
    void update();
    void draw();
    void handle_input();
    float zoom_factor = 1;
};
