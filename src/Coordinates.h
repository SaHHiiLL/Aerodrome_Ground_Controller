#pragma once

#include <string>

// Represents Coordinates from the real world
class Coordinates {
public:
    Coordinates(std::string vertical, std::string lateral);
    Coordinates(float vertical, float lateral) : vertical(vertical), lateral(lateral) {};

    // Creates a coord for "0, 0" 
    Coordinates();

    std::string to_string() {
        std::string res;
        res.push_back(' ');
        res.append(std::to_string(this->vertical));
        res.push_back(',');
        res.push_back(' ');
        res.append(std::to_string(this->lateral));
        res.push_back(' ');
        return res;
    }

private:
    float lateral;
    float vertical;
};
