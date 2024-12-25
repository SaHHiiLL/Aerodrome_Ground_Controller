//
// Created by Sahil on 9/18/24.
//

#include "Game.hpp"
#include "./Utils.hpp"
#include "ResourceManager.hpp"
#include "Runway.hpp"
#include "colours/Colours.hpp"
#include "polygon/Polygon.hpp"
#include "polygon/PolygonParser.hpp"
#include <filesystem>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>

void Game::draw() {
    if (IsKeyDown(KEY_C)) {
        DrawRectangleV({0, 0}, {100, 100}, BLUE);
    } // Drawing runways

    for (auto t : this->polygons) {
        std::cout << "Draing " << std::endl;
        t.draw();
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

void add_polygons(std::vector<Polygon> &polygons, std::filesystem::path path) {}

void Game::update() {}

Game::Game(Camera2D *cam, Colours &colours) : colours(colours) {
    // EGCC - Center Poiint
    // TODO: will be replaced
    this->camera = cam;
    Coordinates center_ref("N053.21.13.480", "W002.16.29.820");
    float sH = GetScreenHeight();
    float sW = GetScreenWidth();
    Vector2 screen_center = {sH / 2, sW / 2};

    ResourceManager &rm = ResourceManager::Instance();
    std::string res = rm.read_file_abs("./resource/Regions.txt");
    PolygonParser pp(res);

    for (std::pair<std::string, std::vector<Coordinates>> p : pp.parse_all()) {
        Color c = this->colours.to_raylib(p.first);
        this->polygons.push_back(
            Polygon(p.second, center_ref, screen_center, c));
    }
}
