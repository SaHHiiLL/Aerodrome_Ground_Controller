#pragma once

#include <cctype>
#include <cstdint>
#include <string>
#include <unordered_map>

// Lazy Colour file Parser
class ColourParser {
private:
    std::string input;
    std::unordered_map<std::string, uint64_t> &map_to_fill;

public:
    ColourParser(std::string input,
                 std::unordered_map<std::string, uint64_t> &map_to_fill);
    void parse();
};
