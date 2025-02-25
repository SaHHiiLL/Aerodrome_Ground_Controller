#pragma once

#include "../Coordinate.hpp"
#include "raylib.h"
#include <optional>
#include <spdlog/spdlog.h>
#include <utility>
#include <vector>

///
/// A geomarking can have a section with the airport's
/// ICAO code followed by the name of the airport
/// followed by an optioanl `area_name`
/// followed by a maybe a calibration point??? - Not sure about this one
///

static std::pair<Coordinate, Coordinate> CALIBRATION_POINT =
    std::make_pair(Coordinate("S999.00.00.000", "E999.00.00.000"),
                   Coordinate("S999.00.00.000", "E999.00.00.000"));
class GeoMarkings {
private:
    float line_width = 1.0f;

public:
    struct Line {
        Color color = YELLOW;
        Vector2 start;
        Vector2 end;
        Coordinate &center_ref;

        Line(Coordinate &c);

        void add_points(Coordinate cstart, Coordinate cend);
    };

    // Header
    struct Header {
        std::string airport_name;
        std::string airport_icao_code;
        std::optional<std::string> area_name;

        // Constructor to initialize the Header
        Header(const std::string &name, const std::string &icao,
               const std::optional<std::string> &area = std::nullopt);

        Header() = default;

        Header &operator=(const Header &other);
    };

    explicit GeoMarkings(const Coordinate center_ref);

    void add_line(const Line &line);

    void draw() const;

    void imgui_draw();

    void set_header(const Header &header);
    void set_center_ref(const Coordinate center_ref);

private:
    Header header;
    Coordinate center_ref;
    // Body
    std::vector<Line> lines;
    Color color = YELLOW;
};
