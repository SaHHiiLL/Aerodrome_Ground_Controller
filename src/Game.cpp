//
// Created by Sahil on 9/18/24.
//

#include "Game.h"
#include "raylib-cpp.hpp"
#include "Runway.h"

void Game::draw() {
    DrawRectangle(0, 0, 100, 100, GREEN);
    if (IsKeyDown(KEY_C)) {
        DrawRectangle(10, 10, 100, 100, RED);
    }
    for (auto & game_object : this->game_objects) {
        game_object->draw();
    }
}

void Game::update() {
    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        raylib::Vector2 delta = GetMouseDelta();
        delta = delta.Scale(-1.0f/this->camera->GetZoom());
        this->camera->SetTarget(Vector2Add(this->camera->GetTarget(),delta));
    }

    // Zoom based on mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        raylib::Vector2 mouseWorldPos = this->camera->GetScreenToWorld(GetMousePosition());

        // Set the offset to where the mouse is
        camera->offset = GetMousePosition();

        // Set the target to match, so that the camera maps the world space point
        // under the cursor to the screen space point under the cursor at any zoom
        camera->target = mouseWorldPos;

        // Zoom increment
        float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
        if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
        camera->zoom = Clamp(camera->zoom*scaleFactor, 0.25f, 40.0f);
    }

    if (IsKeyPressed(KEY_R)) {
        this->camera->SetZoom(1);
        this->camera->SetTarget(raylib::Vector2(GetWindowPosition().x / 2, GetWindowPosition().y / 2 ));
        this->camera->SetRotation(0);
    }

    for (auto & game_object : this->game_objects) {
        game_object->update();
    }
}

Game::Game(raylib::Camera2D *cam, raylib::Window *window) {
    this->camera = cam;
    this->game_objects.push_back(new Runway(166, 1508, raylib::Vector2(0, 0)));
    this->window = window;
}
