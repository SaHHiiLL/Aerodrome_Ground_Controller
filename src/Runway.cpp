//
// Created by Sahil on 9/18/24.
//

#include "Runway.h"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

void Runway::draw() {

    // Draw the rotated rectangle between the two points
    DrawRectanglePro(
        Rectangle{this->runway_midpoint.x, this->runway_midpoint.y, this->runway_length, this->runway_width},      // Rectangle properties
        Vector2{this->runway_length/ 2, this->runway_width/ 2},                                                   // Rotation origin (center of the rectangle)
        this->runway_angle,                                                                                      // Rotation angle in degrees
        this->runway_color                                                                 // Color of the rectangle
    );

    // DEBUG_INFO:
    // draw shapes at the end of two side of the rectangle to indicate the center for the shape.
    // DrawCircleV(this->runway_start_pos, 5, RED);
    // DrawCircleV(this->runway_end_pos, 5, BLUE);
}

Runway::Runway(Coordinates runway_start, Coordinates runway_end, Coordinates center_ref, float runway_width, Color color) : runway_width(runway_width), runway_color(color) {
    float sH = GetScreenHeight();
    float sW = GetScreenWidth();
    Vector2 scree_center = { sH / 2, sW / 2};
    this->runway_start_pos = runway_start.GeoToScreenInRefrence(center_ref, 0.013, scree_center);
    this->runway_end_pos = runway_end.GeoToScreenInRefrence(center_ref, 0.013, scree_center);
    this->runway_midpoint = {(this->runway_start_pos.x + this->runway_end_pos.x) / 2, (this->runway_start_pos.y + this->runway_end_pos.y) / 2};
    this->runway_angle = atan2(this->runway_end_pos.y - this->runway_start_pos.y, this->runway_end_pos.x - this->runway_start_pos.x) * (180.0f / M_PI);
    this->runway_length = (float) sqrt(pow(this->runway_end_pos.x - this->runway_start_pos.x, 2) + pow(this->runway_end_pos.y - this->runway_start_pos.y, 2));
}

Runway::Runway(Coordinates runway_start, Coordinates runway_end, Coordinates center_ref, float runway_width) : runway_width(runway_width) {
    float sH = GetScreenHeight();
    float sW = GetScreenWidth();
    Vector2 scree_center = { sH / 2, sW / 2};
    this->runway_start_pos = runway_start.GeoToScreenInRefrence(center_ref, 0.013, scree_center);
    this->runway_end_pos = runway_end.GeoToScreenInRefrence(center_ref, 0.013, scree_center);
    this->runway_midpoint = {(this->runway_start_pos.x + this->runway_end_pos.x) / 2, (this->runway_start_pos.y + this->runway_end_pos.y) / 2};
    this->runway_angle = atan2(this->runway_end_pos.y - this->runway_start_pos.y, this->runway_end_pos.x - this->runway_start_pos.x) * (180.0f / M_PI);
    this->runway_length = (float) sqrt(pow(this->runway_end_pos.x - this->runway_start_pos.x, 2) + pow(this->runway_end_pos.y - this->runway_start_pos.y, 2));
}
