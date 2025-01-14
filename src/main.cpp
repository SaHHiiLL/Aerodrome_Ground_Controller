#include "Game.hpp"
#include <execinfo.h>
#include <raylib.h>
#include <rlgl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Aerodrome Ground Controller");

    SetTargetFPS(60);

    Camera2D camera{};
    camera.zoom = 1;

    Game game = Game(&camera);
    while (!WindowShouldClose()) {
        game.handle_input();
        game.update();
        ClearBackground(BLACK);
        BeginDrawing();
        {
            BeginMode2D(camera);
            {
                game.draw();
            }
            EndMode2D();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
