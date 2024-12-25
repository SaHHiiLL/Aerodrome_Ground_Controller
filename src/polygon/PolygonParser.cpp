#include "./PolygonParser.hpp"
#include "../AGCException.hpp"
#include <format>

PolygonParser::Token PolygonParser::next_token() {
    this->skip_whitespaces();
    Token current;
    char curr_char = this->lexer.curr_char;

    if (curr_char == ';') {
        this->skip_curr_line();
        current.type = Comment;

    } else if (is_letter()) {
        std::string ident = this->read_identifer();
        if (ident == "REGIONNAME") {
            current.type = RegionName;
            current.literal = ident;
            this->last_token_type = RegionName;

        } else if (this->last_token_type == RegionName) {
            current.type = RegionNameValue;
            current.literal = ident;
            this->last_token_type = RegionNameValue;

        } else if (this->last_token_type == RegionNameValue) {
            current.type = ColourKey;
            current.literal = ident;
            this->last_token_type = ColourKey;

        } else if (this->last_token_type == ColourKey) {
            current.type = SingleCoordinate;
            current.literal = ident;
            this->last_token_type = SingleCoordinate;

        } else {
            std::string msg =
                std::format("Invalid input: {},", this->lexer.position);
            throw AGCException(msg);
        }
    } else {
        std::string msg =
            std::format("Invalid input: {},", this->lexer.position);
        throw AGCException(msg);
    }
    this->read_char();
    return current;
}
