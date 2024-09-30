//
// Created by Sahil on 9/18/24.
//

#ifndef AERODROME_GROUND_CONTROLLER_GAME_H
#define AERODROME_GROUND_CONTROLLER_GAME_H

#include "Runway.h"
#include <vector>
#include <raylib.h>

class Game {
private:
    Camera2D *camera;
    std::vector<Runway*> runways;

public:
    Game(Camera2D *cam);
    void update();
    void draw();
    void handle_input();
};


#endif //AERODROME_GROUND_CONTROLLER_GAME_H
