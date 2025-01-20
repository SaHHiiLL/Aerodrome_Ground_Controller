#pragma once

#include "../Coordinate.hpp"
#include "../colours/Colours.hpp"
#include "../labels/AirportLabel.hpp"
#include "../polygon/Polygon.hpp"
#include <vector>

class Airport {
private:
    std::vector<Polygon> polygons;
    std::vector<AirportLabel> airport_label;
    Coordinate airport_center_ref;
    Colours &colors;
    std::string airport_icao_code;
    std::string airport_name = "";

public:
    void draw();

    Airport(std::string airport_icao_code, Colours &colors);
    ~Airport() {}
};
