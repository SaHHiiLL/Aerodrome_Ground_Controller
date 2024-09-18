#include <iostream>
#include "raylib-cpp.hpp"
#include "rlgl.h"
#include "Game.h"


int main(void) {
    float screenWidth = 800;
    float screenHeight = 450;

    raylib::Window window(screenWidth, screenHeight, "Aerodrome Ground Controller");
    SetTargetFPS(60);

    raylib::Camera2D camera = Camera2D();
    raylib::Vector2 zero = raylib::Vector2(screenWidth/2, screenHeight/2);

    camera.SetZoom(1);
    Game game = Game(&camera);

    while (!window.ShouldClose())
    {
        ClearBackground(DARKGRAY);
        DrawFPS(0, 0);
        game.update();

        BeginDrawing();
            camera.BeginMode();
                game.draw();
            camera.EndMode();
        EndDrawing();
    }

    return 0;
}