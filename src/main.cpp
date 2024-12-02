#include "Game.h"
#include "raymath.h"
#include <raylib.h>
#include <rlgl.h>
#include <iostream>
#include <delaunator.hpp>

void test() {
    std::vector<double> coords = {0.73, 0.267, 0.812, 0.542, 0.108, 0.49, 0.34, 0, -0.028, 0.082};
    coords.reserve(coords.size());

    //triangulation happens here
    delaunator::Delaunator d(coords);

    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
        // Vector2 t1 = {(float)d.coords[2 * d.triangles[i]],      (float)d.coords[2 * d.triangles[i] + 1]};
        // Vector2 t2 = {(float)d.coords[2 * d.triangles[i + 1]],  (float)d.coords[2 * d.triangles[i + 1] + 1]};
        // Vector2 t3 = {(float)d.coords[2 * d.triangles[i + 2]],  (float)d.coords[2 * d.triangles[i + 2] + 1]};
        //

            Vector2 x1 =    {(float)d.coords[2 * d.triangles[i]],        /*tx0 */ (float)d.coords[2 * d.triangles[i] + 1]    }; //ty0 };
            Vector2 x2 =    {(float)d.coords[2 * d.triangles[i + 1]],    /*tx1 */ (float)d.coords[2 * d.triangles[i + 1] + 1]};//ty1 }:
            Vector2 x3 =    {(float)d.coords[2 * d.triangles[i + 2]],    /*tx2 */ (float)d.coords[2 * d.triangles[i + 2] + 1]};//ty2 };

        // Vector2 t1 = {0, 0};
        // Vector2 t2 = {10, 0};
        // Vector2 t3 = {5, 10};
        x1 = Vector2Scale(x1, 122.0f);
        x2 = Vector2Scale(x2, 122.0f);
        x3 = Vector2Scale(x3, 122.0f);

        printf("Triangle Points: [[%f, %f], [%f, %f], [%f, %f]]\n",
               x1.x, x1.y,
               x2.x, x2.y,
               x3.x, x3.y);


        DrawTriangle(x1, x2, x3, RED);
        // printf(
        //     "Triangle points: [[%f, %f], [%f, %f], [%f, %f]]\n",
        //     d.coords[2 * d.triangles[i]],        /*tx0 */ d.coords[2 * d.triangles[i] + 1],    //ty0
        //     d.coords[2 * d.triangles[i + 1]],    /*tx1 */ d.coords[2 * d.triangles[i + 1] + 1],//ty1
        //     d.coords[2 * d.triangles[i + 2]],    /*tx2 */ d.coords[2 * d.triangles[i + 2] + 1] //ty2
        // );
    }
}

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
            rlPushMatrix();
            rlTranslatef(0, 25*50, 0);
            rlRotatef(90, 1, 0, 0);
            DrawGrid(100, 50);
            rlPopMatrix();
            game.draw();
            test();
            EndMode2D();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
