#pragma once

#include "../Coordinate.hpp"
#include "../Geo/GeoMarkings.hpp"
#include "../colours/ColourManager.hpp"
#include "../labels/AirportLabel.hpp"
#include "../polygon/Polygon.hpp"

#include <vector>

class Airport {
private:
    std::vector<Polygon> polygons;
    std::vector<AirportLabel> airport_label;
    std::vector<GeoMarkings> markings;
    Coordinate airport_center_ref;
    ColourManager &colors;
    std::string airport_icao_code;
    std::string airport_name = "";
    void parse_basic_file(std::string input);

public:
    void draw(const Camera2D &cam) const;
    void imgui_draw();
    Vector2 center_coord();
    Airport(std::string airport_icao_code, ColourManager &colors);
    ~Airport() = default;
};
