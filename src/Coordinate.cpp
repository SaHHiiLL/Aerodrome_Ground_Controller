
#include "Coordinate.hpp"
#include "./Constants.hpp"
#include "raylib.h"
#include <cassert>
#include <cctype>
#include <cmath>
#include <string>

// Conveerts this messs
//      N053.49.49.450 W001.12.18.620
// into
//      53.8304, -1.2052
double Coordinate::parse(std::string s) {
    // 1. loop over the string
    // 2. push the number forward
    std::string y;
    double coords[4] = {};
    int idx = 0;
    int neg = 0;

    for (char &x : s) {
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

Coordinate::Coordinate(std::string lateral, std::string longitude) {
    this->lateral = parse(lateral);
    this->longitude = parse(longitude);
}

Vector2 Coordinate::geo_to_screen_by_refrence(Coordinate center_ref) const {
    return geo_to_screen_by_refrence(center_ref, DRAW_SCALE, SCREEN_CENTER);
}

Vector2 Coordinate::geo_to_screen_by_refrence(Coordinate center_ref,
                                              Vector2 screen_center) const {
    return geo_to_screen_by_refrence(center_ref, DRAW_SCALE, screen_center);
}

// Function to convert latitude and longitude to 2D screen coordinates
Vector2 Coordinate::geo_to_screen_by_refrence(Coordinate center_ref,
                                              float scale,
                                              Vector2 screen_center) const {
    // Convert latitude and longitude to radians
    float x = static_cast<float>(this->longitude - center_ref.lon()) *
              cos(center_ref.lat() * (DEG_2_RAD)) * EARTH_RADIUS_METERS;
    float y = static_cast<float>(this->lateral - center_ref.lat()) *
              EARTH_RADIUS_METERS;

    // Apply scaling and offset to fit within screen space
    x = x * scale + screen_center.x;
    y = -y * scale +
        screen_center.y; // Inverting y because screen y is downwards

    return {x, y};
}

std::string Coordinate::to_string() {
    return "Coordinates(" + std::format("{}", lateral) + ", " +
           std::format("{}", longitude) + ")";
}

double Coordinate::get_distance_m(Coordinate &other) {
    double d_lat = (other.lat() - this->lat()) * DEG2RAD;
    double d_lon = (other.lon() - this->lon()) * DEG2RAD;

    double lat1 = this->lat_degree();
    double lat2 = other.lat_degree();

    double a = (std::sin(d_lat / 2) * std::sin(d_lat / 2)) +
               (std::sin(d_lon / 2) * std::sin(d_lon / 2) * std::cos(lat1) *
                std::cos(lat2));

    return EARTH_RADIUS_METERS *
           (2 * std::atan2(std::sqrt(a), std::sqrt(1 - a)));
}

double Coordinate::lat_degree() { return this->lat() * DEG_2_RAD; }
double Coordinate::lon_degree() { return this->lon() * DEG_2_RAD; }

void Coordinate::lat(double lat) { this->lateral = lat; }

void Coordinate::lat(std::string lat) { this->lateral = parse(lat); }

void Coordinate::lon(double log) { this->longitude = log; }

void Coordinate::lon(std::string log) { this->longitude = parse(log); }

Coordinate::Coordinate(double lateral, double longitude)
    : lateral(lateral), longitude(longitude) {};
double Coordinate::lon() { return this->longitude; }

double Coordinate::lat() { return this->lateral; }
