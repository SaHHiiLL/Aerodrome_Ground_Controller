#include "./Airport.hpp"
#include "../Constants.hpp"
#include "../Geo/GeoParser.hpp"
#include "../ResourceManager.hpp"
#include "../Utils.hpp"
#include "../labels/LabelParser.hpp"
#include "../polygon/PolygonParser.hpp"
#include "raylib.h"
#include <filesystem>
#include <ranges>
#include <spdlog/spdlog.h>
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

void Airport::imgui_draw() {
    for (auto &g : this->markings) {
        g.imgui_draw();
    }
}

void Airport::draw(const Camera2D &cam) const {
    for (auto &polygon : this->polygons) {
        polygon.draw();
    }

    for (auto &l : this->airport_label) {
        l.draw(cam);
    }

    for (auto &g : this->markings) {
        g.draw();
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

    for (auto &polygon : this->polygons) {
        polygon.triangulate(this->airport_center_ref);
    }

    std::string label_res =
        rm.read_file(AIRPORTS_DIR / this->airport_icao_code / LABELS_FILE);
    LabelParser lp =
        LabelParser(label_res, this->colors, this->airport_center_ref);
    this->airport_label = lp.parse_all();

    GeoParser gp = GeoParser(
        rm.read_file(AIRPORTS_DIR / this->airport_icao_code / GEO_FILE),
        this->colors, this->airport_center_ref);
    this->markings = gp.parse_all();
    spdlog::info("Loaded    airport:   {}", this->airport_name);
    spdlog::info("          icao:      {}", this->airport_icao_code);
    spdlog::info("          polygons:  {}", this->polygons.size());
    spdlog::info("          labels:    {}", this->airport_label.size());
    spdlog::info("          markings:  {}", this->markings.size());
}

Vector2 Airport::center_coord() {
    return this->airport_center_ref.geo_to_screen_by_refrence(
        this->airport_center_ref, SCREEN_CENTER);
}
