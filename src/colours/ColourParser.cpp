#include "./ColourParser.hpp"
#include "../Utils.hpp"
#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

ColourParser::ColourParser(
    std::string input, std::unordered_map<std::string, uint64_t> &map_to_fill)
    : input(input), map_to_fill(map_to_fill) {}

void ColourParser::parse() {
    Utils::StringSplit spliter(input, '\n');
    std::vector<std::string> lines = spliter.collect();
    // filter comments from lines;
    std::erase_if(lines,
                  [](const std::string line) { return line.starts_with(';'); });

    for (auto s : lines) {
        Utils::StringSplit spliter(s, ' ');
        spliter.next(); // #define
        std::string key{spliter.next()};
        uint64_t colour = std::stoull(spliter.next());
        this->map_to_fill.insert(std::make_pair(key, colour));
    }
}
