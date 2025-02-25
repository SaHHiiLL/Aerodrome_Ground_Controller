#pragma once

// #include <raylib.h>
#include "./Vec2.hpp"
#include <string>

// Represents Coordinates from the real world
// https://medium.com/@suverov.dmitriy/how-to-convert-latitude-and-longitude-coordinates-into-pixel-offsets-8461093cb9f5
class Coordinate {
public:
    Coordinate(std::string lateral, std::string longitude);
    Coordinate(double lateral, double longitude);

    // Creates a coord for "0, 0"
    Coordinate() = default;

    std::string to_string();

    Vec2 geo_to_screen_by_refrence(Coordinate center_ref) const;

    Vec2 geo_to_screen_by_refrence(Coordinate center_ref,
                                   Vector2 screen_center) const;
    Vec2 geo_to_screen_by_refrence(Coordinate center_ref, float scale,
                                   Vector2 screen_center) const;
    // W/E - X
    double lon();
    // N/S - Y
    double lat();

    void lat(double lat);
    void lat(std::string lat);
    void lon(double log);
    void lon(std::string log);

    double parse(std::string s);

    double get_distance_m(Coordinate &other);

    double lat_degree();
    double lon_degree();

private:
    double lateral;
    double longitude;
};
