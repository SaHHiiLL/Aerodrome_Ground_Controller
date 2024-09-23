//
// Created by Sahil on 9/18/24.
//

#include "Runway.h"
#include "rlgl.h"

Runway::Runway(float runway_heading, int runway_length_meters, raylib::Vector2 runway_position) {
    this->runway_heading = runway_heading;
    this->runway_length_px = runway_length_meters;
    this->runway_position = runway_position;
}

void Runway::draw() {
    raylib::Rectangle rectangle( raylib::Vector2(this->runway_position.x, this->runway_position.y), raylib::Vector2(40, this->runway_length_px));
    DrawRectanglePro(rectangle, raylib::Vector2(20, this->runway_length_px / 2), this->runway_heading, BLUE);
}

void Runway::update() {
    
}
