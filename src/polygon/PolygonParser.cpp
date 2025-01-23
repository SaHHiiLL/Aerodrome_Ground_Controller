#include "./PolygonParser.hpp"
#include "../Utils.hpp"
#include <numeric>
#include <ranges>
#include <regex>

// TODO: change this is `Lexer.cpp` implementation
std::vector<Polygon> PolygonParser::parse(ColourManager &colors) {

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
    for (auto &w : words_split) {
        if (w == "REGIONNAME") {
            // start of a new polygon
            // add the last polygon to the list if it's not empty
            if (!curr_polygon.is_empty()) {
                polygons.push_back(curr_polygon);
            }
            curr_polygon = Polygon();
        } else if (std::regex_match(w, coord_regex_ns)) {
            curr_lateral = w;
        } else if (std::regex_match(w, coord_regex_we)) {
            const Coordinate coords(curr_lateral, w);
            curr_polygon.add_coordinate(coords);
        } else if (colors.is_valid(w)) {
            curr_polygon.set_color(colors.to_raylib(w));
        } else {
        }
    }

    return polygons;
}
