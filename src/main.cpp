#include "Coordinates.h"
#include "Game.h"
#include <iostream>

int main(void) {

    float screenWidth = 1000;
    float screenHeight = 600;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
     SetConfigFlags(FLAG_FULLSCREEN_MODE);

    raylib::Window window(screenWidth, screenHeight, "Aerodrome Ground Controller");
    SetTargetFPS(60);

    raylib::Camera2D camera = Camera2D();

    camera.SetZoom(1);
    Game game = Game(&camera, &window);

    while (!window.ShouldClose())
    {
        ClearBackground(DARKGRAY);
        DrawFPS(0, 0);
        game.update();

        BeginDrawing();
        {
            camera.BeginMode();
            game.draw();
            camera.EndMode();
        }
        EndDrawing();
    }

    return 0;
}
