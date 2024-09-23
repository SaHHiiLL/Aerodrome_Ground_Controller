#pragma once

#include <string>
#include <utility>
#include <vector>

class Coordinates {
public:
Coordinates(std::string vertical, std::string lateral) :
        vertical(std::move(vertical)), lateral(std::move(lateral)) {
    }


    std::vector<float> convert_google_earth();

private:
    std::string lateral;
    std::string vertical;

    int lateral_i;
    int vertical_i;

    float parse(std::string s);
};
