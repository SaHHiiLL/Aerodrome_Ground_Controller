//
// Created by Sahil on 9/18/24.
//

#ifndef AERODROME_GROUND_CONTROLLER_RUNWAY_H
#define AERODROME_GROUND_CONTROLLER_RUNWAY_H


#include "Coordinates.h"
#include "raylib.h"

class Runway {
public:
    Runway();
    Runway(Coordinates runway_start, Coordinates runway_end, Coordinates center_ref);
    void update() ;

    void draw() ;

private:
    float runway_heading;

    Vector2 runway_start_pos;
    Vector2 runway_end_pos;
};


#endif //AERODROME_GROUND_CONTROLLER_RUNWAY_H
