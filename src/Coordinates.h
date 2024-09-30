#pragma once

#include <string>
#include <raylib.h>

inline const float EARTH_RADIUS_METERS = 6378137.0f;

// Represents Coordinates from the real world
class Coordinates {
public:
    Coordinates(std::string lateral, std::string longitude);
    Coordinates(float lateral, float longitude) : lateral(lateral), longitude(longitude) {};

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

    Vector2 GeoToScreenInRefrence(Coordinates center_ref, float scale, Vector2 screen_center );
    float lon() { return this->longitude; }
    float lat() { return this->lateral; }

private:
    float lateral;
    float longitude;
};
