#include "./Airport.hpp"
#include "../Constants.hpp"
#include "../ResourceManager.hpp"
#include "../Utils.hpp"
#include "../labels/LabelParser.hpp"
#include "../polygon/PolygonParser.hpp"
#include <filesystem>
#include <ranges>
#include <utility>

void Airport::parse_basic_file(std::string input) {
    // split by newlines
    std::vector<std::string> lines =
        input | std::ranges::views::split('\n') |
        std::ranges::to<std::vector<std::string>>();

    // split second line
    std::vector<std::string> coords_str = Utils::split_whitespace(lines.at(1));

    this->airport_name = lines.front();
    this->airport_center_ref =
        Coordinate(coords_str.front(), coords_str.back());
}

void Airport::draw() const {
    for (auto &polygon : this->polygons) {
        polygon.draw();
    }

    for (auto &l : this->airport_label) {
        l.draw();
    }
}

Airport::Airport(std::string airport_icao_code, ColourManager &colors)
    : colors(colors), airport_icao_code(std::move(airport_icao_code)) {
    // Read region file;

    ResourceManager &rm = ResourceManager::instance();
    std::string basic_res =
            rm.read_file(AIRPORTS_DIR / this->airport_icao_code / BASIC_FILE);

    this->parse_basic_file(basic_res);

    std::string region_res =
            rm.read_file(AIRPORTS_DIR / this->airport_icao_code / REGIONS_FILE);

    PolygonParser parser = PolygonParser(region_res);
    this->polygons = parser.parse(colors);
    const auto sH = static_cast<float>(GetScreenHeight());
    const auto sW = static_cast<float>(GetScreenWidth());
    const Vector2 screen_center = {sH / 2, sW / 2};

    for (auto &polygon: this->polygons) {
        polygon.triangulate(this->airport_center_ref, screen_center);
    }

    std::string label_res =
            rm.read_file(AIRPORTS_DIR / this->airport_icao_code / LABELS_FILE);
    LabelParser lp =
            LabelParser(label_res, this->colors, this->airport_center_ref);
    this->airport_label = lp.parse_all();
}
