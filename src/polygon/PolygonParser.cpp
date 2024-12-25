#include "./PolygonParser.hpp"
#include <optional>
#include <regex>
#include <utility>

std::vector<std::pair<std::string, std::vector<Coordinates>>>
PolygonParser::parse_all() {
    // Moves the unwanted stuff to the back

    std::regex coord_regex_ns("[N|S]\\d{3}.\\d{2}.\\d{2}.\\d{3}");
    std::regex coord_regex_we("[W|E]\\d{3}.\\d{2}.\\d{2}.\\d{3}");

    std::vector<std::pair<std::string, std::vector<Coordinates>>> res;
    std::pair<std::string, std::vector<Coordinates>> curr;
    std::string coords[2];

    for (size_t i = 0; i < this->lines.size(); i++) {
        if (std::regex_match(lines[i], coord_regex_ns)) {
            coords[0] = lines[i];
        } else if (std::regex_match(lines[i], coord_regex_we)) {
            coords[1] = lines[i];
            curr.second.push_back(Coordinates(coords[0], coords[1]));
        } else {
            curr = std::make_pair(lines[i], std::vector<Coordinates>());
        }
    }

    return res;
}
