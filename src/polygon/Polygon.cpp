
#include "./Polygon.hpp"
#include "../Coordinates.hpp"
#include "../ResourceManager.hpp"
#include "../earcutter.hpp"
#include "PolygonParser.hpp"
#include "raylib.h"
#include <filesystem>
#include <vector>

void Polygon::triangulate() {
    EarCut earcut;
    this->triangles = earcut.earcut(vertices);
}

Polygon::Polygon(std::vector<Coordinates> coords, Coordinates center_ref,
                 Vector2 screen_center) {
    this->vertices.reserve(coords.size());
    for (auto c : coords) {
        this->vertices.push_back(
            c.geo_to_screen_by_refrence(center_ref, screen_center));
    }

    this->triangulate();
}

Polygon::Polygon(std::filesystem::path path, Coordinates center_ref,
                 Vector2 screen_center) {

    ResourceManager &rm = ResourceManager::Instance();
    std::string res = rm.read_file_abs(path);
    PolygonParser parser = PolygonParser(res);

    for (PolygonParser::Token toke = parser.next_token(); toke.type > 0;
         toke = parser.next_token()) {

        // TODO: make a new class that can create multiple polygons
        // using the parser since, the `Regions.txt` files contains more than
        // one polygon
        if (toke.type == PolygonParser::TokenType::ColourKey) {
        }
    }

    // this->vertices.reserve(coords.size());
}

void Polygon::draw(Color color) {
    for (size_t i = 0; i < this->triangles.size(); i++)
        DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
                     this->triangles[i].x3, color);
}

void Polygon::draw() {
    for (size_t i = 0; i < this->triangles.size(); i++)
        DrawTriangle(this->triangles[i].x1, this->triangles[i].x2,
                     this->triangles[i].x3, RED);
}
