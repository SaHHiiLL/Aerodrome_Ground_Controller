#pragma once
#include "../colours/Colours.hpp"
#include "Parser.hpp"
#include <cstdint>
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
    LabelParser();
    LEXER_IMPL(TokenType)
    Lexer lexer;
    Lexer::Token *next_token();
    Colours &colors;

    LabelParser(Colours &colors) : colors(colors) {};
};
