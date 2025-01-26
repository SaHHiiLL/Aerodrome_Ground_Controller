
#include "Application.hpp"
#include "./Constants.hpp"
#include "ResourceManager.hpp"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

Applicaiton::Applicaiton() {
    InitWindow(this->screen_width, this->screen_height, this->title);
    SetTargetFPS(this->fps);
    rlImGuiSetup(this->imgui_dark_theme);
    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_WINDOW_TOPMOST |
                   FLAG_MSAA_4X_HINT);
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

static std::vector<std::string> ALL_AIRPORTS = {"EGLL", "EGPH", "EGCC", "EGLC"};

void Applicaiton::handle_input() {
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    if (io.WantCaptureMouse) {
        return;
    }
    game.handle_input();
}

void Applicaiton::draw_ui() {
    // Imgui goes here
    ImGui::Begin("Debug Menu");
    ImGui::SliderFloat("Draw Scale", &DRAW_SCALE, 0.01, 1.0f);
    ImGui::SameLine();
    if (ImGui::Button("Apply")) {
        this->game = Game(&this->camera);
    }
    ImGui::SliderFloat("Font Scale", &FONT_SCALE, 0.1, 50.0f);
    for (const auto &airport : ALL_AIRPORTS) {
        if (ImGui::Button(airport.data())) {
            this->game.set_airport(airport);
        }
        ImGui::SameLine();
    }

    ImGui::End();
}

void Applicaiton::run() {
    TraceLog(LOG_INFO, "Entering Main Game Loop");
    while (!WindowShouldClose() && !this->quit) {
        this->handle_input();
        game.update();
        ClearBackground(BLACK);
        BeginDrawing();
        rlImGuiBegin();
        draw_ui();
        BeginMode2D(camera);
        {
            game.draw();
        }

        EndMode2D();
        rlImGuiEnd();
        EndDrawing();
    }

    unload_font();
}
