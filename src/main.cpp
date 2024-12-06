#include "Game.h"
#include <raylib.h>
#include <rlgl.h>

int main(void) {
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Aerodrome Ground Controller");

    SetTargetFPS(60);

    Camera2D camera = { 0 };
    camera.zoom = 1;

    Game game = Game(&camera);

    while (!WindowShouldClose())
    {
        game.handle_input();
        game.update();
        ClearBackground(DARKGRAY);
        BeginDrawing();
        {
            BeginMode2D(camera);
            {
                rlPushMatrix();
                rlTranslatef(0, 25*50, 0);
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

    return 0;
}
