#pragma once
#include "../colours/ColourManager.hpp"
#include "AirportLabel.hpp"
#include "Parser.hpp"
#include <cstdint>
#include <iterator>
#include <string>
#include <vector>

class LabelParser {
    enum class TokenType : std::uint8_t {
        LABEL = 0,
        SINGLE_COORDINATE,
        QUOTATION,
        COMMENT,
        COLOR_KEY
    };

public:
    LabelParser(std::string input, ColourManager &colors,
                Coordinate &center_ref);
    LEXER_IMPL(TokenType)
    std::string input;
    Lexer lexer;
    Lexer::Token *next_token();
    [[nodiscard]] std::vector<AirportLabel> parse_all();

private:
    ColourManager &colors;
    Coordinate &center_ref;
};
