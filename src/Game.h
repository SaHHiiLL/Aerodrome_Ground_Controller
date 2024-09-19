//
// Created by Sahil on 9/18/24.
//

#ifndef AERODROME_GROUND_CONTROLLER_GAME_H
#define AERODROME_GROUND_CONTROLLER_GAME_H

#include "raylib-cpp.hpp"
#include "Runway.h"

class Game {
private:
    raylib::Window *window;
    raylib::Camera2D *camera;
    std::vector<GameObject*> game_objects;

public:
    Game(raylib::Camera2D *cam, raylib::Window *window);
    void update();
    void draw();
};


#endif //AERODROME_GROUND_CONTROLLER_GAME_H
