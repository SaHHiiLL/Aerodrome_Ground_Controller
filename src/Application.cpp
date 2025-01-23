
#include "Application.hpp"
#include "ResourceManager.hpp"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
Applicaiton::Applicaiton() {
    InitWindow(this->screen_width, this->screen_height, this->title);
    SetTargetFPS(this->fps);
    rlImGuiSetup(this->imgui_dark_theme);
    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_MSAA_4X_HINT |
                   FLAG_BORDERLESS_WINDOWED_MODE);
    this->airplane_image = ResourceManager::instance().get_airplane();
    this->airplane_texture = LoadTextureFromImage(this->airplane_image);
    load_font();
    this->camera = Camera2D{};
    camera.zoom = 1;
    this->game = Game(&this->camera);

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    TraceLog(LOG_INFO, "ImGui with Docking Loaded");
};

void Applicaiton::run() {
    TraceLog(LOG_INFO, "Entering Main Game Loop");
    while (!WindowShouldClose() && !this->quit) {
        game.handle_input();
        game.update();
        ClearBackground(BLACK);
        BeginDrawing();
        rlImGuiBegin();
        BeginMode2D(camera);
        {
            game.draw();
            {
                // Imgui goes here
            }
        }

        EndMode2D();
        rlImGuiEnd();
        EndDrawing();
    }

    unload_font();
}
