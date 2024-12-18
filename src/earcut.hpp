#pragma once

//
//
//  -
//  https://www.youtube.com/watch?v=QAdfkylpYwc&list=PLSlpr6o9vURx4vjomFuwrFhvhV1nhJ_Jc&index=2
//
//  Earcut algorithm
//      - Checks if an edge is convex from the two adjacent vertices
//      - No three edge must be co-liner aka - angle must never be 180 exactly
//

#include "raylib.h"
#include <cmath>
#include <iostream>
#include <vector>

struct Triangle {
    Vector2 p1, p2, p3;
};

class Earcut {
    // Function to check if point P is inside the triangle ABC
    bool PointInTriangle(Vector2 p, Vector2 a, Vector2 b, Vector2 c) {
        float area = 0.5f * (-b.y * c.x + a.y * (-b.x + c.x) +
                             a.x * (b.y - c.y) + b.x * c.y);
        float s =
            1.f / (2.f * area) *
            (a.y * c.x - a.x * c.y + (c.y - a.y) * p.x + (a.x - c.x) * p.y);
        float t =
            1.f / (2.f * area) *
            (a.x * b.y - a.y * b.x + (a.y - b.y) * p.x + (b.x - a.x) * p.y);

        return s > 0.f && t > 0.f && (s + t) < 1.f;
    }

    // Function to check if the angle between three points is convex
    // (counter-clockwise)
    bool IsConvex(Vector2 prev, Vector2 p, Vector2 next) {
        float crossProduct =
            (next.x - p.x) * (p.y - prev.y) - (next.y - p.y) * (p.x - prev.x);
        return crossProduct > 0; // Counter-clockwise (convex)
    }

public:
    void EarClipTriangulate(const std::vector<Vector2> &polygon,
                            std::vector<Triangle> &outTriangles) {
        std::vector<Vector2> vertices = polygon;
        int vertexCount = vertices.size();

        while (vertexCount > 3) {
            for (int i = 0; i < vertexCount; i++) {
                int prevIdx = (i - 1 + vertexCount) % vertexCount;
                int nextIdx = (i + 1) % vertexCount;
                Vector2 prev = vertices[prevIdx];
                Vector2 current = vertices[i];
                Vector2 next = vertices[nextIdx];

                // Check if the angle is convex
                if (!IsConvex(prev, current, next))
                    continue;

                // Check if no points are inside the triangle formed by prev,
                // current, next
                bool isEar = true;
                for (int j = 0; j < vertexCount; j++) {
                    if (j != prevIdx && j != i && j != nextIdx) {
                        if (PointInTriangle(vertices[j], prev, current, next)) {
                            isEar = false;
                            break;
                        }
                    }
                }

                // If it's an ear, clip it
                if (isEar) {
                    // Store the triangle
                    outTriangles.push_back({prev, current, next});

                    // Remove the vertex at 'i'
                    vertices.erase(vertices.begin() + i);
                    vertexCount--;
                    break;
                }
            }
        }

        // Add the last triangle
        outTriangles.push_back({vertices[0], vertices[1], vertices[2]});
    }
};
