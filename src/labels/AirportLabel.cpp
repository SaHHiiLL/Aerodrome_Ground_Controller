#include "./AirportLabel.hpp"
#include "../Constants.hpp"
#include <utility>

AirportLabel::AirportLabel(std::string data, Coordinate coords,
                           Coordinate center_ref, const Color color)
    : data(std::move(data)), coords(coords), color(color),
      world_center_ref(center_ref) {

    this->position =
        coords.geo_to_screen_by_refrence(world_center_ref, SCREEN_CENTER);
}

void AirportLabel::draw(const Camera2D &cam) const {
    const Font *font = get_font();
    DrawTextEx(*font, this->data.c_str(), this->position,
               (14 * FONT_SCALE) / cam.zoom, 0, this->color);
}
