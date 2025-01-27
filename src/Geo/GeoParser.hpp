#pragma once

#include "Parser.hpp"
#include <cstdint>
#include <string>
#include <vector>

class GeoParser {
    enum TokenType {
        COMMENT,
        SINGLE_COORDS,
        IDENT,
    };
    LEXER_IMPL(TokenType)

    std::string input;
    Lexer lexer;
    Lexer::Token *next_token();
    // [[nodiscard]] std::vector<AirportLabel> parse_all();
};
