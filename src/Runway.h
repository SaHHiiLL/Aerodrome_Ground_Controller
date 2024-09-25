//
// Created by Sahil on 9/18/24.
//

#ifndef AERODROME_GROUND_CONTROLLER_RUNWAY_H
#define AERODROME_GROUND_CONTROLLER_RUNWAY_H


#include "Coordinates.h"
#include "GameObject.h"

class Runway : public GameObject {
public:
    Runway();
    Runway(Coordinates runway_start, Coordinates runway_end, Coordinates center_ref);

    void update() override;

    void draw() override;
    void draw2();

private:
    float runway_heading;

    raylib::Vector2 runway_start_pos;
    raylib::Vector2 runway_end_pos;
};


#endif //AERODROME_GROUND_CONTROLLER_RUNWAY_H
