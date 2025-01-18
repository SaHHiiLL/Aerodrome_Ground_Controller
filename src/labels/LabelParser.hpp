#pragma once
#include "../colours/Colours.hpp"
#include "AirportLabel.hpp"
#include "Parser.hpp"
#include <cstdint>
#include <iterator>
#include <string>
#include <vector>

class LabelParser {
    enum TokenType {
        Label = 0,
        SingleCoordinate,
        Quotation,
        Comment,
        ColorKey
    };

public:
    LabelParser(std::string input, Colours &colors, Coordinate &center_ref)
        : input(input), colors(colors), center_ref(center_ref) {
        lexer = Lexer(input);
    };
    LEXER_IMPL(TokenType)
    std::string input;
    Lexer lexer;
    Lexer::Token *next_token();
    std::vector<AirportLabel> parse_all();

private:
    Colours &colors;
    Coordinate &center_ref;
};
