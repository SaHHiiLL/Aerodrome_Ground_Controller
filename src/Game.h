//
// Created by Sahil on 9/18/24.
//

#ifndef AERODROME_GROUND_CONTROLLER_GAME_H
#define AERODROME_GROUND_CONTROLLER_GAME_H

#include "raylib-cpp.hpp"

class Game {
private:
    raylib::Camera2D *camera;

public:
    Game(raylib::Camera2D *cam);
    void update();
    void draw();
};


#endif //AERODROME_GROUND_CONTROLLER_GAME_H
