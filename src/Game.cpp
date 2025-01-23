//
// Created by Sahil on 9/18/24.
//

#include "Game.hpp"
#include <filesystem>
#include <raylib.h>
#include <raymath.h>

void Game::draw() const { this->airport->draw(); }
void Game::handle_input() const {

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
        if (mouse_wheel.y < 0) {
            scaleFactor = 1.0f / scaleFactor;
        }
        camera->zoom = Clamp(camera->zoom * scaleFactor, 0.125f, 20.0f);
    }
}

void Game::update() {}

Game::Game(Camera2D *cam)
    : camera(cam), colours(ColourManager(std::filesystem::path(
                       "./resource/UK-Sector-File/Colours.txt"))) {
    this->airport = new Airport("EGPH", this->colours);
}
