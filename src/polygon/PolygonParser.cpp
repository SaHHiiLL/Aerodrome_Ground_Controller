#include "./PolygonParser.hpp"
#include "../Utils.hpp"
#include <iostream>
#include <numeric>
#include <ranges>
#include <regex>

std::vector<Polygon>
PolygonParser::parse(std::unordered_map<std::string, uint64_t> &color_map) {

    std::vector<Polygon> polygons{};
    // split by newlines
    std::vector<std::string> lines =
        this->input | std::ranges::views::split('\n') |
        std::ranges::to<std::vector<std::string>>();

    // remove empty lines and comments
    std::erase_if(lines, [](const std::string line) {
        return line.empty() || line.starts_with(';');
    });

    const std::string words = std::accumulate(
        lines.begin(), lines.end(), std::string(),
        [](std::string l, std::string const &r) { return l += " " + r; });

    std::vector<std::string> words_split = Utils::split_whitespace(words);

    Polygon curr_polygon;
    std::string curr_lateral;

    const std::regex coord_regex_ns(R"([N|S]\d{3}.\d{2}.\d{2}.\d{3})");
    const std::regex coord_regex_we(R"([W|E]\d{3}.\d{2}.\d{2}.\d{3})");
    for (auto &word : words_split) {
        if (word == "REGIONNAME") {
            // start of a new polygon
            // add the last polygon to the list if it's not empty
            if (!curr_polygon.is_empty()) {
                polygons.push_back(curr_polygon);
            }
            curr_polygon = Polygon();
        } else if (std::regex_match(word, coord_regex_ns)) {
            curr_lateral = word;
        } else if (std::regex_match(word, coord_regex_we)) {
            const Coordinate coords(curr_lateral, word);
            curr_polygon.add_coordinate(coords);
        } else if (color_map.contains(word)) {
            curr_polygon.set_color(GetColor(color_map.at(word)));
        } else {
            std::cout << word << std::endl;
        }
    }

    return polygons;
}
