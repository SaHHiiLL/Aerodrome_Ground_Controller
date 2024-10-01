//
// Created by Sahil on 9/18/24.
//

#include "Runway.h"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

void Runway::draw() {
    // Calculate the midpoint of the rectangle
    Vector2 midpoint = {(this->runway_start_pos.x + this->runway_end_pos.x) / 2, (this->runway_start_pos.y + this->runway_end_pos.y) / 2};

    // Calculate the angle between the two points
    float angle = atan2(this->runway_end_pos.y - this->runway_start_pos.y, this->runway_end_pos.x - this->runway_start_pos.x) * (180.0f / M_PI);

    // Calculate the length and width of the rectangle
    float rectLength = (float) sqrt(pow(this->runway_end_pos.x - this->runway_start_pos.x, 2) + pow(this->runway_end_pos.y - this->runway_start_pos.y, 2));
    float rectWidth = 100.0f;  // Set the desired width of the rectangle
    // Draw the rotated rectangle between the two points
    DrawRectanglePro(
        Rectangle{midpoint.x, midpoint.y, rectLength, rectWidth},  // Rectangle properties
        Vector2{rectLength / 2, rectWidth / 2},            // Rotation origin (center of the rectangle)
        angle,                                                     // Rotation angle in degrees
        DARKGREEN                                                  // Color of the rectangle
    );

    // DEBUG_INFO:
    // draw shapes at the end of two side of the rectangle to indicate the center for the shape.
    DrawCircleV(this->runway_start_pos, 5, RED);
    DrawCircleV(this->runway_end_pos, 5, BLUE);
}


void Runway::update() {}


Runway::Runway(Coordinates runway_start, Coordinates runway_end, Coordinates center_ref) {
    float sH = GetScreenHeight();
    float sW = GetScreenWidth();
    Vector2 center = { sH / 2, sW / 2};
    this->runway_start_pos = runway_start.GeoToScreenInRefrence(center_ref, 0.02, center);
    this->runway_end_pos = runway_end.GeoToScreenInRefrence(center_ref, 0.02, center);
}
