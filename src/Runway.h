//
// Created by Sahil on 9/18/24.
//

#ifndef AERODROME_GROUND_CONTROLLER_RUNWAY_H
#define AERODROME_GROUND_CONTROLLER_RUNWAY_H


#include "raylib-cpp.hpp"
#include "GameObject.h"

class Runway : public GameObject {
public:
    Runway();
    Runway(float runway_heading, int runway_length_meter, raylib::Vector2 runway_position);

    void update() override;

    void draw() override;

private:
    float runway_heading;
    int runway_length_px;
    int runway_lenght_meter;
    raylib::Vector2 runway_position;
};


#endif //AERODROME_GROUND_CONTROLLER_RUNWAY_H
