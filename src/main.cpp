#include "Game.hpp"
#include <execinfo.h>
#include <raylib.h>
#include <rlgl.h>
#include <stdlib.h>
#include <unistd.h>

#include "imgui.h"
#include "rlImGui.h"

int main(void) {
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    InitWindow(screenWidth, screenHeight, "Aerodrome Ground Controller");

    SetTargetFPS(60);

    Camera2D camera{};
    camera.zoom = 1;

    rlImGuiSetup(true);

#ifdef IMGUI_HAS_DOCK
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    TraceLog(LOG_INFO, "ImGui with Docking Loaded");
#else
    TraceLog(LOG_ERROR, "This application requires imgui with docking....");
    return -1;
#endif

    Game game = Game(&camera);
    while (!WindowShouldClose()) {
        game.handle_input();
        game.update();
        ClearBackground(BLACK);
        BeginDrawing();
        rlImGuiBegin();
        {
            BeginMode2D(camera);
            {
                game.draw();
                {
                    // show ImGui Content
                    bool open = true;
                    ImGui::Begin("HEllo ??");
                    ImGui::End();
                }
            }
            EndMode2D();
        }
        rlImGuiEnd();
        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
