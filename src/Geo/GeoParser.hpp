#pragma once

#include "../Coordinate.hpp"
#include "../colours/ColourManager.hpp"
#include "GeoMarkings.hpp"
#include "Parser.hpp"
#include <cstdint>
#include <string>
#include <vector>

class GeoParser {
private:
    enum TokenType : std::uint8_t {
        COMMENT = 0,
        SINGLE_COORDS,
        IDENT,
        COLOR_KEY,
    };
    LEXER_IMPL(TokenType)

    std::string input;
    Lexer lexer;
    ColourManager &color_manager;
    Coordinate &center_ref;

public:
    Lexer::Token *next_token();
    GeoParser(const std::string input, ColourManager &color_manager,
              Coordinate &center_ref);
    [[nodiscard]] std::vector<GeoMarkings> parse_all();

    [[nodiscard]] GeoMarkings::Header parse_header();
};
