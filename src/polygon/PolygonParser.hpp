#pragma once
#include "../Coordinates.hpp"
#include "../Utils.hpp"
#include <algorithm>

class PolygonParser {
private:
    std::vector<std::string> lines;
    size_t curr = 0;

public:
    PolygonParser(std::string input) {
        Utils::StringSplit spliter(input, '\n');
        this->lines = spliter.collect();
        auto new_lines = std::remove_if(
            this->lines.begin(), this->lines.end(),
            [](const std::string x) { return x.starts_with(';'); });
        this->lines.erase(new_lines, this->lines.end());

        Utils::StringSplit xx(input, ' ');
        this->lines = xx.collect();

        auto no_regionname = std::remove_if(
            this->lines.begin(), this->lines.end(),
            [](const std::string x) { return x == "REGIONNAME"; });
        this->lines.erase(no_regionname, this->lines.end());

        auto no_man = std::remove_if(
            this->lines.begin(), this->lines.end(),
            [](const std::string x) { return x == "Manchester"; });
        this->lines.erase(no_man, this->lines.end());
    }

    std::vector<std::pair<std::string, std::vector<Coordinates>>> parse_all();
    std::string get_current_line() { return this->lines[curr]; }
};
