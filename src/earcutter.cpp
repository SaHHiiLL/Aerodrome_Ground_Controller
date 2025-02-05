#include "./earcutter.hpp"
#include "raylib.h"
#ifdef DEBUG
#include <chrono>
#endif
#include <cstddef>
#include <raymath.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <sys/types.h>

// Retuns true if a given angle `curr` is convex releative to `next` and `prev`
bool EarCut::is_convex(Vector2 prev, Vector2 curr, Vector2 next) {
    Vector2 curr_to_prev = Vector2Subtract(prev, curr);
    Vector2 curr_to_next = Vector2Subtract(next, curr);
    return crossproduct(curr_to_prev, curr_to_next) > 0;
}

// Returns the cross product for prev -> curr -> next
// in counter clock-wise
float EarCut::crossproduct(Vector2 a, Vector2 b) {
    return (a.x * b.y) - (a.y * b.x);
}

static bool check_colinearpoints(Vector2 q, Vector2 w, Vector2 e) {
    float a = q.x;
    float b = q.y;

    float m = w.x;
    float n = w.y;

    float x = e.x;
    float y = e.y;

    return (n - b) * (x - m) == (y - n) * (m - a);
}

// TODO: Does not check if an edge is self-intersecting
std::vector<Triangle>
EarCut::earcut(const std::vector<Vector2> &polygon_vertices) {

    if (polygon_vertices.size() < 3) {
        throw std::invalid_argument("Polygon must have least 3 sizes!");
    }

    // check no co linear points exists
    size_t j = 0;
    size_t k = 1;

    for (size_t i = 2; i < polygon_vertices.size(); i++) {
        if (check_colinearpoints(polygon_vertices[j], polygon_vertices[k],
                                 polygon_vertices[i])) {
            // throw std::invalid_argument(
            //     "Polygon must not have co linear vertices");
            spdlog::warn("Polygon must not have co linear vertices, skipping");
            return {};
        }
        j++;
        k++;
    }

    std::vector<Vector2> ver = polygon_vertices;
    const size_t max_out_size = polygon_vertices.size() - 2;

    std::vector<Triangle> out;
    out.reserve(max_out_size);
    size_t indexCount = polygon_vertices.size();

#ifdef DEBUG
    auto start = std::chrono::system_clock::now();
#endif

    // Do this process until we have the last three index
    while (indexCount > 3) {
        for (size_t i = 0; i < indexCount; i++) {
            size_t prev_idx = (i - 1 + indexCount) % indexCount;
            size_t next_idx = (i + 1) % indexCount;
            Vector2 prev = ver.at(prev_idx);
            Vector2 next = ver.at(next_idx);
            Vector2 curr = ver.at(i);

#ifdef DEBUG
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            if (elapsed_seconds.count() > 2) {
                spdlog::warn("Time exceeded for earcut");
                return {};
            }
#endif

            if (!is_convex(prev, curr, next)) {
                continue;
            }

            // Can successfully make a triangle;
            Triangle t(prev, next, curr);
            bool is_inside = false;

            // Check if any of the points are inside triangle
            for (size_t j = 0; j < indexCount; j++) {
                // We continue if j equals any of the points of the triangle

                if (j == i || j == prev_idx || j == next_idx) {
                    continue;
                }

                if (t.is_point_inside(ver.at(j))) {
                    is_inside = true;
                    break;
                }
            }
            if (!is_inside) {
                if (out.size() > max_out_size) {
                    spdlog::critical(
                        "out size increased out:{}, max_out_size:{}",
                        out.size(), max_out_size);
                    throw std::invalid_argument("Invalid tree");
                } else {
                    out.emplace_back(prev, curr, next);
                    ver.erase(ver.begin() + i);
                    indexCount--;
                    break;
                }
            }
        }
    }
    out.emplace_back(ver.at(0), ver.at(1), ver.at(2));
    return out;
}
bool Triangle::is_point_inside(Vector2 p) const {
    Vector2 a = this->x1;
    Vector2 b = this->x2;
    Vector2 c = this->x3;
    const float area = 0.5f * (-b.y * c.x + a.y * (-b.x + c.x) +
                               a.x * (b.y - c.y) + b.x * c.y);
    const float s =
        1.f / (2.f * area) *
        (a.y * c.x - a.x * c.y + (c.y - a.y) * p.x + (a.x - c.x) * p.y);
    const float t =
        1.f / (2.f * area) *
        (a.x * b.y - a.y * b.x + (a.y - b.y) * p.x + (b.x - a.x) * p.y);

    return s > 0.f && t > 0.f && (s + t) < 1.f;
}
void Triangle::draw_outline() const {
    DrawLineV(this->x1, this->x2, RAYWHITE);
    DrawLineV(this->x2, this->x3, RAYWHITE);
    DrawLineV(this->x3, this->x1, RAYWHITE);
}

void Triangle::draw(Color color) const { DrawTriangle(x1, x2, x3, color); }

void Triangle::draw() const { DrawTriangle(x1, x2, x3, GREEN); }

Triangle::Triangle(const Vector2 prev, const Vector2 curr, const Vector2 next)
    : x1(prev), x2(curr), x3(next) {}
Triangle::Triangle(const float x1, const float y1, const float x2,
                   const float y2, const float x3, const float y3) {
    this->x1 = {.x = x1, .y = y1};
    this->x2 = {.x = x2, .y = y2};
    this->x3 = {.x = x3, .y = y3};
};
