#include "./Utils.hpp"
#include "Coordinates.hpp"
#include "Game.hpp"
#include "delaunator.hpp"
#include <iostream>
#include <raylib.h>
#include <rlgl.h>

#include <fstream>
#include <sstream>
#include <string>

std::string readFileToString(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str(); // Return the contents as a string
}

void Test() {
    std::string test = readFileToString("./resource/RMA.txt");

    Utils::StringSplit splitByNewLine(test, '\n');
    std::vector<std::string> coordsAsString = splitByNewLine.collect();
    std::vector<Coordinates> coords;

    for (size_t i = 0; i < coordsAsString.size(); i += 2) {
        std::string newStr =
            coordsAsString[i].append(" ").append(coordsAsString[i + 1]);
        coords.push_back(newStr);
    }

    Coordinates centerRef(0.0f, 0.0f);
    float x = 0;
    float y = 0;

    for (auto c : coords) {
        x += c.lon();
        y += c.lat();
    }

    centerRef = Coordinates(x / coords.size(), y / coords.size());

    // Coordinates centerRef = Coordinates("N053.21.13.480", "W002.16.29.820");

    std::vector<double> cc;

    for (auto c : coords) {
        float sH = GetScreenHeight();
        float sW = GetScreenWidth();
        Vector2 scree_center = {sH / 2, sW / 2};
        Vector2 xy =
            c.GeoToScreenInRefrence(centerRef, DRAW_SCALE, scree_center);
        cc.push_back(xy.x);
        cc.push_back(xy.y);
    }

    // Convert the coordinates to double;
    Delaunator d(cc);

    for (size_t i = 0; i < d.triangles.size(); i += 3) {
        Vector2 x1 = {
            (float)d.coords[2 * d.triangles[i]],
            /*tx0 */ (float)d.coords[2 * d.triangles[i] + 1]}; // ty0 };
        Vector2 x2 = {
            (float)d.coords[2 * d.triangles[i + 1]],
            /*tx1 */ (float)d.coords[2 * d.triangles[i + 1] + 1]}; // ty1 }:
        Vector2 x3 = {
            (float)d.coords[2 * d.triangles[i + 2]],
            /*tx2 */ (float)d.coords[2 * d.triangles[i + 2] + 1]}; // ty2 };

        DrawTriangle(x1, x2, x3, GREEN);
        DrawCircleV(x1, 5.0f, BLUE);
        DrawCircleV(x2, 5.0f, BLUE);
        DrawCircleV(x3, 5.0f, BLUE);
    }
}

int main(void) {
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Aerodrome Ground Controller");

    SetTargetFPS(60);

    Camera2D camera = {0};
    camera.zoom = 1;

    Game game = Game(&camera);

    while (!WindowShouldClose()) {
        game.handle_input();
        game.update();
        ClearBackground(DARKGRAY);
        BeginDrawing();
        {
            BeginMode2D(camera);
            {
                rlPushMatrix();
                rlTranslatef(0, 25 * 50, 0);
                rlRotatef(90, 1, 0, 0);
                DrawGrid(100, 50);
                rlPopMatrix();
                game.draw();
            }
            EndMode2D();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
