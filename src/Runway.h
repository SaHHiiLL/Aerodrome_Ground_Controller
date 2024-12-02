//
// Created by Sahil on 9/18/24.
//

#ifndef AERODROME_GROUND_CONTROLLER_RUNWAY_H
#define AERODROME_GROUND_CONTROLLER_RUNWAY_H


#include "Coordinates.h"
#include "raylib.h"
#include "raymath.h"

class Runway {
public:
    Runway();
    Runway(Coordinates runway_start, Coordinates runway_end, Coordinates center_ref, float runway_width);
    Runway(Coordinates runway_start, Coordinates runway_end, Coordinates center_ref, float runway_width, Color color);
    Runway(std::array<Coordinates, 4> points, Coordinates center_ref, float runway_heading, Color color);
    void update() ;
    void draw() ;

private:
    float runway_heading;
    float runway_width;
    Vector2 runway_midpoint;
    float runway_length;
    // the angle between the two points
    float runway_angle;
    Vector2 runway_start_pos;
    Vector2 runway_end_pos;
    Color runway_color = {26, 26, 26, 0xFF};

};


#endif //AERODROME_GROUND_CONTROLLER_RUNWAY_H
