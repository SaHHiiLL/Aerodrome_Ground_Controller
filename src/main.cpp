#include "Game.h"
#include <raylib.h>
#include <rlgl.h>

int main(void) {

    float screenWidth = 1000;
    float screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "Aerodrome Ground Controller");
    SetTargetFPS(60);

    Camera2D camera = { 0 };
    camera.zoom = 1;

    Game game = Game(&camera);

    while (!WindowShouldClose())
    {
        game.handle_input();
        ClearBackground(DARKGRAY);
        game.update();
        BeginDrawing();
        {
            BeginMode2D(camera);
                rlPushMatrix();
                    rlTranslatef(0, 25*50, 0);
                    rlRotatef(90, 1, 0, 0);
                    DrawGrid(100, 50);
                rlPopMatrix();
            game.draw();
            EndMode2D();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
