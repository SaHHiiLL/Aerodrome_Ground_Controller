#include "Game.hpp"
#include "colours/Colours.hpp"
#include <filesystem>
#include <iostream>
#include <raylib.h>
#include <rlgl.h>

int main(void) {
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Aerodrome Ground Controller");

    SetTargetFPS(60);

    Camera2D camera{};
    camera.zoom = 1;

    Colours *colours =
        new Colours(std::filesystem::path("./resource/Colours.txt"));

    Game game = Game(&camera, *colours);
    while (!WindowShouldClose()) {
        game.handle_input();
        game.update();
        ClearBackground(DARKGRAY);
        BeginDrawing();
        {
            BeginMode2D(camera);
            {
                rlPushMatrix();
                rlTranslatef(0, 25 * 50, 0);
                rlRotatef(90, 1, 0, 0);
                DrawGrid(100, 50);
                rlPopMatrix();
                game.draw();
            }
            EndMode2D();
        }
        EndDrawing();
    }

    CloseWindow();
    delete colours;

    return 0;
}
