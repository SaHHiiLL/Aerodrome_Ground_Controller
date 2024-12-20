
#include "Coordinates.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

// Conveerts this messs
//      N053.49.49.450 W001.12.18.620
// into
//      53.8304, -1.2052

double parse(std::string s) {
    // 1. loop over the string
    // 2. push the number forward
    std::string y;
    double coords[4] = {};
    int idx = 0;
    int neg = 0;

    for (char x : s) {
        if (x == 'N' || x == 'E') {
            neg = 1;
            continue;
        } else if (x == 'S' || x == 'W') {
            neg = -1;
            continue;
        }

        if (x == '.') {
            // marks the end
            double num = stof(y);
            coords[idx] = num;
            if (idx < 3) {
                idx++;
                y.clear();
            }
            continue;
        }
        assert(isdigit(x) && "INVALID CHAR - NOT A NUMBER");
        y.push_back(x);
    }
    // convert the last part
    coords[3] = stof(y);
    return (double)neg * (coords[0] + coords[1] / 60 +
                          (coords[2] + (coords[3] / 1000)) / 3600);
}

Coordinates::Coordinates(std::string lateral, std::string longitude) {
    this->lateral = parse(lateral);
    this->longitude = parse(longitude);
}

Coordinates::Coordinates(std::string coords) {
    Utils::StringSplit split(coords, ' ');
    auto s = split.collect();
    if (s.size() != 2) {
        throw std::invalid_argument(
            std::string("Invalid Coordinates: ").append(coords));
    }
    this->lateral = parse(s[0]);
    this->longitude = parse(s[1]);
}

// Function to convert latitude and longitude to 2D screen coordinates
Vector2 Coordinates::geo_to_screen_by_refrence(Coordinates center_ref,
                                               Vector2 screen_center) {
    return geo_to_screen_by_refrence(center_ref, DRAW_SCALE, screen_center);
}

// Function to convert latitude and longitude to 2D screen coordinates
Vector2 Coordinates::geo_to_screen_by_refrence(Coordinates center_ref,
                                               float scale,
                                               Vector2 screen_center) {
    // Convert latitude and longitude to radians
    float x = (float)(this->longitude - center_ref.lon()) *
              cos(center_ref.lat() * (M_PI / 180.0)) * EARTH_RADIUS_METERS;
    float y = (float)(this->lateral - center_ref.lat()) * EARTH_RADIUS_METERS;

    // Apply scaling and offset to fit within screen space
    x = x * scale + screen_center.x;
    y = -y * scale +
        screen_center.y; // Inverting y because screen y is downwards

    return {x, y};
}
