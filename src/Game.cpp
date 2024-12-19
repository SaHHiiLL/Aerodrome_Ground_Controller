//
// Created by Sahil on 9/18/24.
//

#include "Game.hpp"
#include "./Utils.hpp"
#include "Runway.hpp"
#include "raylib.h"
#include "raymath.h"

void Game::draw() {
    DrawRectangle(0, 0, 100, 100, GREEN);
    if (IsKeyDown(KEY_C)) {
        DrawRectangleV({0, 0}, {100, 100}, BLUE);
    } // Drawing runways
    for (auto &runway : this->runways) {
        runway->draw();
    }
}
void Game::handle_input() {

    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera->zoom);
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
        float scaleFactor = 1.0f + (0.25f * fabsf(mouse_wheel.y));
        if (mouse_wheel.y < 0)
            scaleFactor = 1.0f / scaleFactor;
        camera->zoom = Clamp(camera->zoom * scaleFactor, 0.125f, 20.0f);
    }
}

void Game::update() {}

Game::Game(Camera2D *cam) : camera(cam) {
    // EGCC - Center Poiint

    Coordinates center_coord = Coordinates("N053.21.13.480", "W002.16.29.820");

    // EGCC
    this->runways.push_back(new Runway(
        {
            Coordinates("N053.19.55.785", "W002.18.38.871"),
            Coordinates("N053.19.54.700", "W002.18.37.396"),
            Coordinates("N053.20.52.809", "W002.16.37.099"),
            Coordinates("N053.20.53.945 W002.16.38.633"),
        },
        center_coord, 230, RED));
    this->runways.push_back(
        new Runway({Coordinates("N053.21.41.336 W002.15.34.098"),
                    Coordinates("N053.20.51.775 W002.17.16.736"),
                    Coordinates("N053.20.50.647 W002.17.15.210"),
                    Coordinates("N053.21.40.177 W002.15.32.542")},
                   center_coord, 230, BLUE));
}
