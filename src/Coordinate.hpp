#pragma once

#include <raylib.h>
#include <string>

inline const float EARTH_RADIUS_METERS = 6378137.0f;

inline const float DRAW_SCALE = 0.013;

// Represents Coordinates from the real world
class Coordinate {
public:
    Coordinate(std::string lateral, std::string longitude);
    Coordinate(double longitude, double lateral)
        : lateral(lateral), longitude(longitude) {};

    // Creates a coord for "0, 0"
    Coordinate() {}

    std::string to_string() {
        return "Coordinates(" + std::to_string(lateral) + ", " +
               std::to_string(longitude) + ")";
    }

    Vector2 geo_to_screen_by_refrence(Coordinate center_ref,
                                      Vector2 screen_center);
    Vector2 geo_to_screen_by_refrence(Coordinate center_ref, float scale,
                                      Vector2 screen_center);
    // W/E - X
    double lon() { return this->longitude; }
    // N/S - Y
    double lat() { return this->lateral; }

    void lat(double lat) { this->lateral = lat; }
    void lat(std::string lat) { this->lateral = parse(lat); }
    void lon(double log) { this->longitude = log; }
    void lon(std::string log) { this->longitude = parse(log); }

    double parse(std::string s);

private:
    double lateral;
    double longitude;
};
