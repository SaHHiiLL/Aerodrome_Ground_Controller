#pragma once
#include "./earcutter.hpp"
#include <cstdint>
#include <sys/types.h>

class Sweepline {

public:
    std::vector<Triangle> sweepline(const std::vector<Vector2> &polygon);

private:
    enum class VertexType : std::uint8_t { START, END, SPLIT, MERGE, REGULAR };

    VertexType classify_vertex(const Vector2 &prev, const Vector2 &curr,
                               const Vector2 &next);
    void make_y_monotone(std::vector<Vector2> &polygon,
                         std::vector<std::vector<Vector2>> &monotonePieces);
    void triangulate_monotone_polygon(const std::vector<Vector2> &polygon,
                                      std::vector<Triangle> &triangles);
};
