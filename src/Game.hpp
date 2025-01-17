//
// Created by Sahil on 9/18/24.
//

#pragma once

#include "colours/Colours.hpp"
#include "polygon/Polygon.hpp"
#include <raylib.h>
#include <vector>

class Game {
private:
    Camera2D *camera;
    // Heap allocated colours;
    Colours *colours;
    std::vector<Polygon> polygons;

public:
    Game(Camera2D *cam);
    Game() {};
    ~Game();
    void update();
    void draw();
    void draw_outline();
    void handle_input();
    float zoom_factor = 1;
};
