#pragma once

#include <algorithm>
#include <array>
#include <earcut.hpp>
#include <raylib.h>
#include <string>

inline const float EARTH_RADIUS_METERS = 6378137.0f;

// Represents Coordinates from the real world
class Coordinates {
public:
    Coordinates(std::string lateral, std::string longitude);
    Coordinates(float longitude, float lateral)
        : lateral(lateral), longitude(longitude) {};

    /// expects a string in the format of: "N053.19.55.785 W002.18.38.871"
    Coordinates(std::string);

    // Creates a coord for "0, 0"
    Coordinates();

    std::string to_string() {
        std::string res;
        res.push_back(' ');
        res.append(std::to_string(this->lateral));
        res.push_back(',');
        res.push_back(' ');
        res.append(std::to_string(this->longitude));
        res.push_back(' ');
        return res;
    }

    Vector2 GeoToScreenInRefrence(Coordinates center_ref, float scale,
                                  Vector2 screen_center);
    // W/E - X
    float lon() { return this->longitude; }
    // N/S - Y
    float lat() { return this->lateral; }

    std::array<double, 2> innerDouble() {
        std::array<double, 2> d = {1.3, 2.3};
        return d;
    }

private:
    float lateral;
    float longitude;
};
