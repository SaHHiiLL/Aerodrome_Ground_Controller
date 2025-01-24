#pragma once
#include "Game.hpp"
#include "raylib.h"
#include "rlImGui.h"

class Applicaiton {
public:
    Applicaiton();
    void run();
    ~Applicaiton() {
        rlImGuiShutdown();
        CloseWindow();
    }

private:
    void load_fonts();
    void handle_input();
    void draw_ui();

    // Need Init
    Game game;
    Camera2D camera;
    Texture2D airplane_texture;
    Image airplane_image;

    // Have default values;
    const char *title = "Aerodrome Ground Controller";
    const float screen_height = GetScreenHeight();
    const float screen_width = GetScreenWidth();
    const int fps = 60;
    bool imgui_dark_theme = true;

    bool quit = false;
};
