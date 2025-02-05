#include "./sweepline.hpp"
#include "earcutter.hpp"

#include <algorithm>
#include <cmath>
#include <stack>
#include <vector>

// Classify a vertex as START, END, SPLIT, MERGE, or REGULAR
Sweepline::VertexType Sweepline::classify_vertex(const Vector2 &prev,
                                                 const Vector2 &curr,
                                                 const Vector2 &next) {
    if (prev.y > curr.y && next.y > curr.y) {
        if ((curr.x - prev.x) * (next.y - curr.y) -
                (curr.y - prev.y) * (next.x - curr.x) <
            0)
            return VertexType::SPLIT;
        else
            return VertexType::START;
    } else if (prev.y < curr.y && next.y < curr.y) {
        if ((curr.x - prev.x) * (next.y - curr.y) -
                (curr.y - prev.y) * (next.x - curr.x) <
            0)
            return VertexType::MERGE;
        else
            return VertexType::END;
    } else {
        return VertexType::REGULAR;
    }
}

// Make the polygon y-monotone by adding diagonals at split and merge vertices
void Sweepline::make_y_monotone(
    std::vector<Vector2> &polygon,
    std::vector<std::vector<Vector2>> &monotonePieces) {
    // Sort vertices by y-coordinate
    std::sort(polygon.begin(), polygon.end(),
              [](const Vector2 &a, const Vector2 &b) { return a.y < b.y; });

    // Add diagonals at split and merge vertices
    // (This is a simplified version; a full implementation requires handling
    // sweep-line events) For now, assume the polygon is already y-monotone
    monotonePieces.push_back(polygon);
}

// Triangulate a y-monotone polygon using a sweep-line algorithm
void Sweepline::triangulate_monotone_polygon(
    const std::vector<Vector2> &polygon, std::vector<Triangle> &triangles) {
    if (polygon.size() < 3)
        return;

    // Sort vertices by y-coordinate
    std::vector<Vector2> sortedVertices = polygon;
    std::sort(sortedVertices.begin(), sortedVertices.end(),
              [](const Vector2 &a, const Vector2 &b) { return a.y < b.y; });

    // Use a stack to process vertices
    std::stack<Vector2> stack;
    stack.push(sortedVertices[0]);
    stack.push(sortedVertices[1]);

    for (size_t i = 2; i < sortedVertices.size(); ++i) {
        Vector2 current = sortedVertices[i];
        Vector2 top = stack.top();
        stack.pop();

        // Check if the current vertex is on the same side as the top vertex
        if ((current.y > top.y && stack.top().y > top.y) ||
            (current.y < top.y && stack.top().y < top.y)) {
            // Add triangles until the stack is empty
            while (!stack.empty()) {
                Vector2 prev = stack.top();
                triangles.emplace_back(current.x, current.y, top.x, top.y,
                                       prev.x, prev.y);
                top = prev;
                stack.pop();
            }
        } else {
            // Add a triangle and push the current vertex to the stack
            triangles.emplace_back(current.x, current.y, top.x, top.y,
                                   stack.top().x, stack.top().y);
        }

        stack.push(top);
        stack.push(current);
    }
}

// Main function to divide the polygon into y-monotone pieces and triangulate
std::vector<Triangle>
Sweepline::sweepline(const std::vector<Vector2> &polygon) {
    std::vector<Triangle> triangles;

    // Step 1: Make the polygon y-monotone
    std::vector<std::vector<Vector2>> monotonePieces;
    std::vector<Vector2> mutablePolygon = polygon;
    make_y_monotone(mutablePolygon, monotonePieces);

    // Step 2: Triangulate each y-monotone piece
    for (const auto &piece : monotonePieces) {
        this->triangulate_monotone_polygon(piece, triangles);
    }

    return triangles;
}
