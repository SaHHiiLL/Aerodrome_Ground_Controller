#include "Game.hpp"
#include "colours/Colours.hpp"
#include <execinfo.h>
#include <filesystem>
#include <iostream>
#include <raylib.h>
#include <rlgl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void handler(int sig) {
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

int main(void) {
    signal(SIGSEGV, handler);
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
    delete colours;

    return 0;
}
