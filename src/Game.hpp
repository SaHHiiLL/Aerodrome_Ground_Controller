#pragma once

#include "Aircraft/Aircraft.hpp"
#include "airport/Airport.hpp"
#include "colours/ColourManager.hpp"
#include <raylib.h>

class Game {
private:
    float last_time = GetTime();

    Camera2D *camera;
    // Heap allocated colours;
    ColourManager colours;
    Airport *airport;
    std::vector<Aircraft> aircrafts;

public:
    Game(Camera2D *cam);
    Game(Camera2D *cam, std::string airport_name);
    Game() = default;

    void update();
    void draw() const;
    void draw_outline();
    void handle_input() const;
    float zoom_factor = 1;
    void set_airport(std::string airport_name);
    void imgui_draw();
};
