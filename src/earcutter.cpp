#include "./earcutter.hpp"
#include <raymath.h>
#include <stdexcept>

// Retuns true if a given angle `curr` is convex releative to `next` and `prev`
bool EarCut::is_convex(Vector2 prev, Vector2 curr, Vector2 next) {
    Vector2 curr_to_prev = Vector2Subtract(prev, curr);
    Vector2 curr_to_next = Vector2Subtract(next, curr);
    return crossproduct(curr_to_prev, curr_to_next) > 0;
}

//
// Returns the cross product for prev -> curr -> next
// in counter clock-wise
float EarCut::crossproduct(Vector2 a, Vector2 b) {
    return (a.x * b.y) - (a.y * b.x);
}

// TODO: do all the checks
std::vector<Triangle> EarCut::earcut(std::vector<Vector2> &polygon) {

    if (polygon.size() < 3) {
        throw std::invalid_argument("Polygon must have atleast 3 sizes!");
    }

    std::vector<Vector2> ver = polygon;

    std::vector<Triangle> out;
    out.reserve(polygon.size() - 2);
    size_t indexCount = polygon.size();

    // Do this process until we have the last three index
    while (indexCount > 3) {
        for (size_t i = 0; i < indexCount; i++) {
            size_t prev_idx = (i - 1 + indexCount) % indexCount;
            size_t next_idx = (i + 1) % indexCount;
            Vector2 prev = ver.at(prev_idx);
            Vector2 next = ver.at(next_idx);
            Vector2 curr = ver.at(i);

            if (!is_convex(prev, curr, next)) {
                continue;
            }

            // Can successful make a triangle;
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
                out.push_back({prev, curr, next});
                ver.erase(ver.begin() + i);
                indexCount--;
                break;
            }
        }
    }
    out.push_back({ver.at(0), ver.at(1), ver.at(2)});
    return out;
}
