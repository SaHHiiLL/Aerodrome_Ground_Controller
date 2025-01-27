#pragma once

#include "../Coordinate.hpp"
#include "raylib.h"
#include <optional>
#include <utility>
#include <vector>

///
/// A geomarking can have a section with the airport's
/// ICAO code followed by the name of the airport
/// followed by an optioanl `area_name`
/// followed by a maybe a calibration point??? - Not sure about this one
///
class GeoMarkings {
public:
    struct Line {
        Color color = YELLOW;
        Coordinate start;
        Coordinate end;
    };

    // Header
    struct Header {
        std::string airport_name;
        std::string airport_icao_code;
        std::optional<std::string> area_name;

        // Constructor to initialize the Header
        Header(const std::string name, const std::string icao,
               std::optional<std::string> area = std::nullopt)
            : airport_name(name), airport_icao_code(icao), area_name(area) {}

        Header() = default;

        Header &operator=(const Header &other) {
            this->airport_name = other.airport_name;
            this->airport_icao_code = other.airport_icao_code;
            this->area_name = other.area_name;
            return *this;
        }

        const std::pair<Coordinate, Coordinate> calibration_point =
            std::make_pair(Coordinate("S999.00.00.000", "E999.00.00.000"),
                           Coordinate("S999.00.00.000", "E999.00.00.000"));
    };

    GeoMarkings(Coordinate center_ref) : center_ref(center_ref) {};

    void add_line(Line line) { this->lines.push_back(line); }
    void draw() const {}

    void set_header(Header &header) { this->header = header; }
    void set_center_ref(Coordinate center_ref) {
        this->center_ref = center_ref;
    }

private:
    Header header;
    Coordinate center_ref;
    // Body
    std::vector<Line> lines;
    Color color = YELLOW;
};
