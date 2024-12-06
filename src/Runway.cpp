#include "./Runway.h"
#include <delaunator.hpp>
#include "./Utils.h"


Runway::Runway(std::array<Coordinates, 4> coords, Coordinates center_ref, float runway_heading, Color color)
: coords(coords), center_ref(center_ref), runway_heading(runway_heading), color(color)
{
    std::vector<double> cc;
    for (auto c : coords) {
        float sH = GetScreenHeight();
        float sW = GetScreenWidth();
        Vector2 scree_center = { sH / 2, sW / 2};
        Vector2 xy = c.GeoToScreenInRefrence(center_ref, DRAW_SCALE, scree_center);
        cc.push_back(xy.x);
        cc.push_back(xy.y);
    }


    // Convert the coordinates to double;
    Delaunator d(cc);

    for (size_t i = 0; i < d.triangles.size(); i += 3) {
        Vector2 x1 =    {(float)d.coords[2 * d.triangles[i]],        /*tx0 */ (float)d.coords[2 * d.triangles[i] + 1]    }; //ty0 };
        Vector2 x2 =    {(float)d.coords[2 * d.triangles[i + 1]],    /*tx1 */ (float)d.coords[2 * d.triangles[i + 1] + 1]}; //ty1 }:
        Vector2 x3 =    {(float)d.coords[2 * d.triangles[i + 2]],    /*tx2 */ (float)d.coords[2 * d.triangles[i + 2] + 1]}; //ty2 };

        this->verties.push_back(x1);
        this->verties.push_back(x2);
        this->verties.push_back(x3);
    }

}

void Runway::draw() {
    for (size_t i = 0; i < this->verties.size(); i += 3) {
        DrawTriangle(this->verties[i], this->verties[i + 1], this->verties[i + 2], this->color);
    }
}
