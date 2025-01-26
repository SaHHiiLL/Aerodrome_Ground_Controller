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
};
