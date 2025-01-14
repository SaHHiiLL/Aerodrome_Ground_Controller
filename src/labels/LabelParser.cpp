#include "./LabelParser.hpp"
#include "raylib.h"
#include <regex>

LabelParser::Lexer::Token *LabelParser::next_token() {
    LabelParser::Lexer::Token *tok = nullptr;
    this->lexer.skip_whitespace();
    if (this->lexer.is_eof())
        return nullptr;

    switch (this->lexer.curr_char) {
    case '"':
        this->lexer.read_next();
        if (this->lexer.is_letter() || this->lexer.is_number()) {
            std::string label = this->lexer.read_until('\"');
            tok->type = TokenType::Label;
            tok->literal = label;
            // Read leading "
            this->lexer.read_next();
        } else {
            TraceLog(LOG_WARNING, "Invalid char `%s` at positon %s",
                     this->lexer.curr_char, this->lexer.position);
        }
        this->lexer.read_next();
    case ';':
        tok->type = TokenType::Comment;
        break;
    default:
        if (this->lexer.is_letter()) {
            std::string ident = this->lexer.read_to_space();
            const std::regex coord_regex(R"([N|S|W|E]\d{3}.\d{2}.\d{2}.\d{3})");
            if (std::regex_match(ident, coord_regex)) {
                tok->literal = ident;
                tok->type = TokenType::SingleCoordinate;
            } else if (this->colors.is_valid(ident)) {
                tok->type = TokenType::ColorKey;
                tok->literal = ident;
            } else {
                // Invalid
                TraceLog(LOG_WARNING, "Token of literal %s is invalid",
                         ident.data());
            }
        }
    }

    this->lexer.read_next();
    return tok;
}
