//
// Created by Sahil on 9/18/24.
//

#include "Runway.h"
#include "raylib.h"
#include "rlgl.h"

//void Runway::draw() {
//    // raylib::Rectangle rectangle( raylib::Vector2(this->runway_position.x, this->runway_position.y), raylib::Vector2(40, this->runway_length_px));
//    // DrawRectanglePro(rectangle, raylib::Vector2(20, this->runway_length_px / 2), this->runway_heading, BLUE);
//
//    // Calculate the top-left corner of the rectangle and its size
//
//    float rectX = std::min(this->runway_start_pos.x, this->runway_end_pos.x);          // X-coordinate of the rectangle
//    float rectY = std::min(this->runway_start_pos.y, this->runway_end_pos.y);          // Y-coordinate of the rectangle
//    float rectWidth = std::abs(this->runway_end_pos.x - this->runway_start_pos.x);     // Width of the rectangle
//    float rectHeight = std::abs(this->runway_end_pos.y - this->runway_start_pos.y);    // Height of the rectangle
//
//    DrawRectangle(rectX, rectY, rectWidth, rectHeight, ColorAlpha(DARKGREEN, 0.5f)); // Semi-transparent green
//    DrawCircleV(this->runway_start_pos, 5, RED);
//    DrawCircleV(this->runway_end_pos, 5, BLUE);
//
//    draw2();
//}

void Runway::draw() {
    // Calculate the midpoint of the rectangle
    raylib::Vector2 midpoint = {(this->runway_start_pos.x + this->runway_end_pos.x) / 2, (this->runway_start_pos.y + this->runway_end_pos.y) / 2};

    // Calculate the angle between the two points
    float angle = atan2(this->runway_end_pos.y - this->runway_start_pos.y, this->runway_end_pos.x - this->runway_start_pos.x) * (180.0f / M_PI);

    // Calculate the length and width of the rectangle
    float rectLength = (float) sqrt(pow(this->runway_end_pos.x - this->runway_start_pos.x, 2) + pow(this->runway_end_pos.y - this->runway_start_pos.y, 2));
    float rectWidth = 100.0f;  // Set the desired width of the rectangle
    // Draw the rotated rectangle between the two points
    DrawRectanglePro(
        Rectangle{midpoint.x, midpoint.y, rectLength, rectWidth},  // Rectangle properties
        raylib::Vector2{rectLength / 2, rectWidth / 2},            // Rotation origin (center of the rectangle)
        angle,                                                     // Rotation angle in degrees
        DARKGREEN                                                  // Color of the rectangle
    );

    // Optional: Draw the original points as small circles for reference
    DrawCircleV(this->runway_start_pos, 5, RED);
    DrawCircleV(this->runway_end_pos, 5, BLUE);
}


void Runway::update() {}


Runway::Runway(Coordinates runway_start, Coordinates runway_end, Coordinates center_ref) {
    float sH = GetScreenHeight();
    float sW = GetScreenWidth();
    raylib::Vector2 center = { sH / 2, sW / 2};
    this->runway_start_pos = runway_start.GeoToScreenInRefrence(center_ref, 0.02, center);
    this->runway_end_pos = runway_end.GeoToScreenInRefrence(center_ref, 0.02, center);
}
