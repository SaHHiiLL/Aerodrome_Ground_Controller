#pragma once

#include <raylib.h>
#include <string>

inline const float EARTH_RADIUS_METERS = 6378137.0f;

inline const float DRAW_SCALE = 0.013;

// Represents Coordinates from the real world
class Coordinates {
public:
    Coordinates(std::string lateral, std::string longitude);
    Coordinates(double longitude, double lateral)
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

    Vector2 geo_to_screen_by_refrence(Coordinates center_ref,
                                      Vector2 screen_center);
    Vector2 geo_to_screen_by_refrence(Coordinates center_ref, float scale,
                                      Vector2 screen_center);
    // W/E - X
    double lon() { return this->longitude; }
    // N/S - Y
    double lat() { return this->lateral; }

private:
    double lateral;
    double longitude;
};
