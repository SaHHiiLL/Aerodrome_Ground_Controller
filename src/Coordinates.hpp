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
    Coordinates() {}

    std::string to_string() {
        return "Coordinates(" + std::to_string(lateral) + ", " +
               std::to_string(longitude) + ")";
    }

    Vector2 geo_to_screen_by_refrence(Coordinates center_ref,
                                      Vector2 screen_center);
    Vector2 geo_to_screen_by_refrence(Coordinates center_ref, float scale,
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
