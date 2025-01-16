//
// Created by Sahil on 9/18/24.
//

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "colours/Colours.hpp"
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

    for (size_t i = 0; i < this->polygons.size(); i++) {
        DrawTriangle({1, 0}, {0, -1}, {0, 0}, RED);
        this->polygons[i].draw();
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

Game::~Game() { delete this->colours; }

Game::Game(Camera2D *cam) {
    this->camera = cam;
    this->colours =
        new Colours(std::filesystem::path("./resource/Colours.txt"));
    // EGCC - Center Poiint
    // TODO: will be replaced
    Coordinate center_ref("N055.57.09.000", "W003.21.41.000");
    float sH = GetScreenHeight();
    float sW = GetScreenWidth();
    Vector2 screen_center = {sH / 2, sW / 2};

    ResourceManager &rm = ResourceManager::Instance();
    std::string res = rm.read_file_abs(
        "/home/Sahil/programing/cpp/Aerodrome_Ground_Controller/resource/"
        "UK-Sector-File-2024-13/Airports/EGPH/SMR/Regions.txt");
    PolygonParser pp(res);
    this->polygons = pp.parse(colours->colours);
    TraceLog(LOG_DEBUG, "Parsing complete, total of : ", this->polygons.size());

    for (auto & polygon : this->polygons) {
        polygon.triangulate(center_ref, screen_center);
    }
    TraceLog(LOG_DEBUG, "Triangulation complete");
}
