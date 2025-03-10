#include "./ColourParser.hpp"
#include "../Utils.hpp"
#include "raylib.h"
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

ColourParser::ColourParser(
    std::string input, std::unordered_map<std::string, uint64_t> &map_to_fill)
    : input(std::move(input)), map_to_fill(map_to_fill) {}

void ColourParser::parse() {

    // split by newlines
    std::vector<std::string> lines =
        this->input | std::ranges::views::split('\n') |
        std::ranges::to<std::vector<std::string>>();

    // remove empty lines and comments
    std::erase_if(lines,
                  [](const std::string &line) {
                      return line.empty() || line.starts_with(';');
                  });

    std::string words = std::accumulate(
        lines.begin(), lines.end(), std::string(),
        [](std::string l, std::string const &r) { return l += " " + r; });

    std::vector<std::string> words_split = Utils::split_whitespace(words);

    for (size_t i = 0; i < words_split.size(); i += 3) {
        if (words_split[i] == "#define") {
            uint32_t color_bgr = std::stoull(words_split[i + 2]);
            this->map_to_fill.insert(
                {words_split[i + 1],
                 __builtin_bswap32(color_bgr | 0xff000000)});
        } else {
            std::cout << "Invalid entry for colour parsing at index: " << i
                      << std::endl;
            // invalid
        }
    }

    TraceLog(LOG_INFO, "Color Parsed found %d unique colors ",
             this->map_to_fill.size());
}
