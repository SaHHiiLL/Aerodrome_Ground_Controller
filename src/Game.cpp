//
// Created by Sahil on 9/18/24.
//

#include "Game.h"
#include "Runway.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

void Game::draw() {
    DrawRectangle(0, 0, 100, 100, GREEN);
    if (IsKeyDown(KEY_C)) {
        DrawRectangleV({0, 0}, {100, 100}, BLUE);
    }

    // Drawing runways
    for (auto& runway: this->runways) {
        runway->draw();
    }

}

void Game::handle_input() {
    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera->zoom);
        camera->target = Vector2Add(camera->target, delta);
    }

    // reset the view
    if (IsKeyPressed(KEY_R)) {
        this->camera->target = Vector2{0, 0};
        this->camera->zoom = 1;
        this->camera->offset = Vector2{0, 0};
    }

    Vector2 mouse_wheel = GetMouseWheelMoveV();
    if (mouse_wheel.y != 0) {
        Vector2 mouse_pos = GetMousePosition();
        Vector2 zoom_pos = GetScreenToWorld2D(mouse_pos, *this->camera);
        this->camera->offset = mouse_pos;
        this->camera->target = zoom_pos;
        float scaleFactor = 1.0f + (0.25f*fabsf(mouse_wheel.y));
        if (mouse_wheel.y < 0) scaleFactor = 1.0f/scaleFactor;
        camera->zoom = Clamp(camera->zoom*scaleFactor, 0.125f, 20.0f);
    }
}

void Game::update() {
}

Game::Game(Camera2D *cam) : camera(cam){
    // EGCC - Center Poiint

    Coordinates center_coord = Coordinates("N053.21.13.480", "W002.16.29.820");
        
    // EGCC
    this->runways.push_back(
        new Runway(
            Coordinates("N053.20.51.200", "W002.17.15.950"),
            Coordinates("N053.21.40.750", "W002.15.33.410"),
            center_coord,
            100.0f
        )
    );
    this->runways.push_back(
        new Runway(
            Coordinates("N053.19.55.110", "W002.18.38.380"),
            Coordinates("N053.20.53.350", "W002.16.37.950"),
            center_coord,
            100.0f
        )
    );

}
