#include "./Aircraft.hpp"
#include "imgui.h"
#include "raylib.h"

Aircraft::Aircraft(const Vector2 start_pos, const Vector2 end_pos)
    : start_pos(start_pos), end_pos(end_pos), curr_pos(start_pos),
      move_speed(2) {}

void Aircraft::draw() const { DrawCircleV(this->curr_pos, 10, WHITE); }

void Aircraft::update(const float &delta_time) {
    this->curr_pos = Vector2{curr_pos.x + (move_speed * delta_time),
                             curr_pos.y + (move_speed * delta_time)};
}

void Aircraft::draw_imgui() {
    ImGui::SliderFloat("Move Speed", &this->move_speed, 0, 1000);
}
