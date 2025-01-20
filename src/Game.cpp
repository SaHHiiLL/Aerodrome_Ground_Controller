//
// Created by Sahil on 9/18/24.
//

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "colours/Colours.hpp"
#include "labels/LabelParser.hpp"
#include "polygon/PolygonParser.hpp"
#include <filesystem>
#include <raylib.h>
#include <raymath.h>
#include <vector>

void Game::draw() {
    for (size_t i = 0; i < this->polygons.size(); i++) {
        this->polygons[i].draw();
    }

    for (auto &l : this->labels) {
        l.draw();
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
        if (mouse_wheel.y < 0) {
            scaleFactor = 1.0f / scaleFactor;
        }
        camera->zoom = Clamp(camera->zoom * scaleFactor, 0.125f, 20.0f);
    }
}

void Game::update() {}

Game::Game(Camera2D *cam)
    : camera(cam), colours(Colours(std::filesystem::path(
                       "./resource/UK-Sector-File/Colours.txt"))) {

    Coordinate center_ref("N055.57.09.000", "W003.21.41.000");
    const auto sH = static_cast<float>(GetScreenHeight());
    const auto sW = static_cast<float>(GetScreenWidth());
    const Vector2 screen_center = {sH / 2, sW / 2};

    // Parsing polygons
    const std::string res = ResourceManager::read_file(
        "/home/Sahil/programing/cpp/Aerodrome_Ground_Controller/resource/"
        "UK-Sector-File/Airports/EGPH/SMR/Regions.txt");
    PolygonParser pp(res);
    this->polygons = pp.parse(colours.colours);
    for (auto &polygon : this->polygons) {
        polygon.triangulate(center_ref, screen_center);
    }

    const std::string label_res = ResourceManager::read_file(
        "/home/Sahil/programing/cpp/Aerodrome_Ground_Controller/resource/"
        "UK-Sector-File/Airports/EGPH/SMR/Labels.txt");

    LabelParser l_parser(label_res, this->colours, center_ref);
    this->labels = l_parser.parse_all();
}
