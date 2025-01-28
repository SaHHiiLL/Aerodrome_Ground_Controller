#pragma once

#include <raylib.h>
#include <string>

// Represents Coordinates from the real world
class Coordinate {
public:
    Coordinate(std::string lateral, std::string longitude);
    Coordinate(double longitude, double lateral);

    // Creates a coord for "0, 0"
    Coordinate() = default;

    std::string to_string();

    Vector2 geo_to_screen_by_refrence(Coordinate center_ref) const;

    Vector2 geo_to_screen_by_refrence(Coordinate center_ref,
                                      Vector2 screen_center) const;
    Vector2 geo_to_screen_by_refrence(Coordinate center_ref, float scale,
                                      Vector2 screen_center) const;
    // W/E - X
    double lon() { return this->longitude; }
    // N/S - Y
    double lat() { return this->lateral; }

    void lat(double lat);
    void lat(std::string lat);
    void lon(double log);
    void lon(std::string log);

    double parse(std::string s);

private:
    double lateral;
    double longitude;
};
