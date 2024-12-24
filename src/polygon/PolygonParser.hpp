#pragma once
#include "../Parser.hpp"

class PolygonParser {
public:
    enum TokenType {
        Eof = 0,
        RegionName,
        RegionNameValue,
        ColourKey,
        SingleCoordinate,
        Comment,
        Invalid = -1,
    };

private:
    TokenType last_token_type;

    LEXER_IMPL(PolygonParser)
};
