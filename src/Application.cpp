
#include "Application.hpp"
#include "./Constants.hpp"
#include "ResourceManager.hpp"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include "spdlog/spdlog.h"
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <format>

static void custom_loggin(int log_level, const char *msg, va_list args) {
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), msg, args);
    switch (log_level) {
    case LOG_INFO: {
        spdlog::info(buffer);
        break;
    }
    case LOG_ERROR: {
        spdlog::error(buffer);
        break;
    }
    case LOG_FATAL: {
        spdlog::critical(buffer);
        break;
    }
    case LOG_WARNING: {
        spdlog::warn(buffer);
        break;
    }
    default:
        spdlog::debug(buffer);
        break;
    }
}

Application::Application() {
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

static inline const std::vector<std::string> ALL_AIRPORTS = {
    "EGLL", "EGPH", "EGCC", "EGLC", "EGNX", "EGGW", "EGPF"};

void Application::handle_input() const {
    const ImGuiIO &io = ImGui::GetIO();
    (void)io;
    if (io.WantCaptureMouse) {
        return;
    }

    game.handle_input();
}

void Application::draw_ui() {
// Imgui goes here
#ifdef DEBUG
    ImGui::Begin("Debug Menu");
    ImGui::Text("FPS: %d", GetFPS());
    ImGui::SliderFloat("Font Scale", &FONT_SCALE, 1.0f, 50.0f);
    ImGui::SliderFloat("Camera Rotation", &this->camera.rotation, 0, 360.0f);
    ImGui::Text(
        "%s",
        std::format("Pixel Speed {}", AIRCRAFT_SPEED_PIXEL_PER_SECOND).c_str());
    this->game.imgui_draw();
    ImGui::End();
#endif

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Airport")) {
            for (const std::string &airport : ALL_AIRPORTS) {
                if (ImGui::MenuItem(airport.c_str())) {
                    this->current_airport = airport;
                    this->game.set_airport(this->current_airport);
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Application::run() {
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
Application::~Application() {
    rlImGuiShutdown();
    CloseWindow();
}
