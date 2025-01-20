#include "./Airport.hpp"
#include "../Constants.hpp"
#include "../ResourceManager.hpp"
#include "../labels/LabelParser.hpp"
#include "../polygon/PolygonParser.hpp"
#include <filesystem>

void Airport::draw() {
    for (auto &polygon : this->polygons) {
        polygon.draw();
    }

    for (auto &l : this->airport_label) {
        l.draw();
    }
}

Airport::Airport(std::string airport_icao_code, Colours &colors)
    : colors(colors), airport_icao_code(airport_icao_code) {
    // Read region file;

    this->airport_center_ref = Coordinate("N055.57.09.000", "W003.21.41.000");

    ResourceManager &rm = ResourceManager::Instance();
    std::string region_res =
        rm.read_file(AIRPORTS_DIR / this->airport_icao_code / REGIONS_FILE);

    PolygonParser parser = PolygonParser(region_res);
    this->polygons = parser.parse(colors);
    const auto sH = static_cast<float>(GetScreenHeight());
    const auto sW = static_cast<float>(GetScreenWidth());
    const Vector2 screen_center = {sH / 2, sW / 2};

    for (auto &polygon : this->polygons) {
        polygon.triangulate(this->airport_center_ref, screen_center);
    }

    std::string label_res =
        rm.read_file(AIRPORTS_DIR / this->airport_icao_code / LABELS_FILE);
    LabelParser lp =
        LabelParser(label_res, this->colors, this->airport_center_ref);
    this->airport_label = lp.parse_all();
}
