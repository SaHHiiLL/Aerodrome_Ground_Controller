#include "./ColourParser.hpp"
#include "../Utils.hpp"
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

ColourParser::ColourParser(
    std::string input, std::unordered_map<std::string, uint64_t> &map_to_fill)
    : input(input), map_to_fill(map_to_fill) {}

void ColourParser::parse() {

    // split by newlines
    std::vector<std::string> lines =
        this->input | std::ranges::views::split('\n') |
        std::ranges::to<std::vector<std::string>>();

    // remove empty lines and comments
    lines.erase(std::remove_if(lines.begin(), lines.end(),
                               [](const std::string line) {
                                   return line.empty() || line.starts_with(';');
                               }),
                lines.end());

    std::string words = std::accumulate(
        lines.begin(), lines.end(), std::string(),
        [](std::string l, std::string const &r) { return l += " " + r; });

    std::vector<std::string> words_split = Utils::split_whitespace(words);

    for (size_t i = 0; i < words_split.size(); i += 3) {
        if (words_split[i] == "#define") {
            this->map_to_fill.insert(
                {words_split[i + 1], std::stoull(words_split[i + 2])});
        } else {
            std::cout << "Invalid entry for colour parsing at index: " << i
                      << std::endl;
            // invalid
        }
    }
}
