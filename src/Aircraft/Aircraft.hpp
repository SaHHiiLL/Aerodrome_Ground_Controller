#pragma once

#include <raylib.h>

class Aircraft {
public:
    void update(const float &delta_time);
    void draw() const;
    void draw_imgui();
    Aircraft(const Vector2 start_pos, const Vector2 end_pos);

private:
    float move_speed;
    Texture2D aircraft_texture;
    Vector2 start_pos;
    Vector2 end_pos;
    Vector2 curr_pos;
    float speed = 1.0f;
    Vector2 size = {10, 10};
    float last_distance;
};
