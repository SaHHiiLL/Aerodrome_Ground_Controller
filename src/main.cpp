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
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Aerodrome Ground Controller");

    SetTargetFPS(60);

    Camera2D camera{};
    camera.zoom = 1;

    rlImGuiSetup(true);

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
                    ImGui::ShowDemoWindow(&open);
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
