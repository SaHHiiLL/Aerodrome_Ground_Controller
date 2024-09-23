
#include <cassert>
#include <cctype>
#include <string>
#include "Coordinates.h"

// Conveerts this messs 
//      N053.49.49.450 W001.12.18.620
// into 
//      53.8304, -1.2052

float parse(std::string s) {
     // 1. loop over the string
    // 2. push the number forward
    std::string y;
    float coords[4] = {};
    int idx = 0;
    int neg = 0;

    for (char x: s) {
        if (x == 'N' || x == 'E') {
            neg = 1;
            continue;
        } else if (x == 'S' || x == 'W') {
            neg = -1;
            continue;
        }

        if (x == '.') {
            //marks the end
            float num = stof(y);
            coords[idx] = num;
            if (idx < 3) {
                idx++;
                y.clear();
            }
            continue;
        }
        assert(isdigit(x) && "INVALID CHAR - NOT A NUMBER");
        y.push_back(x);
    }
    // convert the last part
    coords[3] = stof(y);
    return (float) neg * ( coords[0] + coords[1] / 60 + (coords[2] + (coords[3] / 1000)) / 3600);
}


Coordinates::Coordinates(std::string vertical, std::string lateral) {
    this->lateral = parse(lateral);
    this->vertical = parse(vertical);
}
