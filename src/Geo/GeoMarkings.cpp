#include "./GeoMarkings.hpp"
void GeoMarkings::Line::add_points(Coordinate cstart, Coordinate cend) {
    this->start = cstart.geo_to_screen_by_refrence(center_ref, SCREEN_CENTER);
    this->end = cend.geo_to_screen_by_refrence(center_ref, SCREEN_CENTER);
}

GeoMarkings::Header::Header(const std::string &name, const std::string &icao,
                            const std::optional<std::string> &area)
    : airport_name(name), airport_icao_code(icao), area_name(area) {}

GeoMarkings::Header &GeoMarkings::Header::operator=(const Header &other) {
    this->airport_name = other.airport_name;
    this->airport_icao_code = other.airport_icao_code;
    this->area_name = other.area_name;
    return *this;
}

GeoMarkings::GeoMarkings(const Coordinate center_ref)
    : center_ref(center_ref) {};
void GeoMarkings::add_line(const Line &line) { this->lines.push_back(line); }

void GeoMarkings::draw() const {
    for (const auto &line : lines) {
        DrawLineEx(line.start, line.end, this->line_width, line.color);
    }
}

void GeoMarkings::imgui_draw() {
    ImGui::SliderFloat(
        std::format("Line Width {}", this->header.airport_name).data(),
        &line_width, 0.5f, 10.0f);
}

void GeoMarkings::set_center_ref(const Coordinate center_ref) {
    this->center_ref = center_ref;
}

void GeoMarkings::set_header(const Header &header) { this->header = header; }

GeoMarkings::Line::Line(Coordinate &c) : center_ref(c) {}
