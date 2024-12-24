#pragma once

#include "../Parser.hpp"
#include <cctype>

// Lazy Colour file Parser
class ColourParser {

public:
    enum TokenType {
        Eof = 0,
        Comment,
        Define,
        Identifier,
        Value,
        InValid = -1
    };

    LEXER_IMPL(ColourParser)
};
