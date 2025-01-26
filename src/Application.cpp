
#include "Application.hpp"
#include "./Constants.hpp"
#include "ResourceManager.hpp"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include "spdlog/spdlog.h"
#include <cmath>
#include <cstdarg>

static void custom_loggin(int log_level, const char *msg, va_list args) {
    switch (log_level) {
    case LOG_INFO: {
        spdlog::info(msg);
        break;
    }
    case LOG_ERROR: {
        spdlog::error(msg);
        break;
    }
    case LOG_FATAL: {
        spdlog::critical(msg);
        break;
    }
    case LOG_WARNING: {
        spdlog::warn(msg);
        break;
    }
    default:
        spdlog::debug(msg);
        break;
    }
}

Applicaiton::Applicaiton() {
    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_WINDOW_TOPMOST |
                   FLAG_MSAA_4X_HINT);
    SetTraceLogCallback(custom_loggin);
    InitWindow(this->screen_width, this->screen_height, this->title);
    SetTargetFPS(this->fps);
    rlImGuiSetup(this->imgui_dark_theme);

    const auto sH = static_cast<float>(GetScreenHeight());
    const auto sW = static_cast<float>(GetScreenWidth());
    SCREEN_CENTER = Vector2{sH / 2, sW / 2};
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
}
