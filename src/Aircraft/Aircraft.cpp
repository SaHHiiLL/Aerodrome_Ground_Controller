#include "./Aircraft.hpp"
#include "imgui.h"
#include "raylib.h"
#include "raymath.h"
#include <fmt/base.h>

Aircraft::Aircraft(const Vector2 start_pos, const Vector2 end_pos)
    : start_pos(start_pos), end_pos(end_pos), curr_pos(start_pos),
      last_distance(Vector2Distance(this->curr_pos, this->end_pos)),
      move_speed(100) {}

void Aircraft::draw() const { DrawCircleV(this->curr_pos, 10, WHITE); }

void Aircraft::update(const float &delta_time) {
    this->curr_pos = Vector2MoveTowards(this->curr_pos, this->end_pos,
                                        this->move_speed * delta_time);
}

void Aircraft::draw_imgui() {
    ImGui::SliderFloat("Move Speed", &this->move_speed, 1, 1000.0);
}
