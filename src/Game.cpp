//
// Created by Sahil on 9/18/24.
//

#include "Game.h"
#include "raylib-cpp.hpp"

void Game::draw() {
    DrawRectangle(0, 0, 100, 100, GREEN);
    if (IsKeyDown(KEY_C)) {
        DrawRectangle(10, 10, 100, 100, RED);
    }
}

void Game::update() {
    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        raylib::Vector2 delta = GetMouseDelta();
        delta = delta.Scale(-1.0f/this->camera->GetZoom());
        camera->SetTarget(Vector2Add(this->camera->GetTarget(),delta));
    }
}

Game::Game(raylib::Camera2D *cam) {
    this->camera = cam;
}
