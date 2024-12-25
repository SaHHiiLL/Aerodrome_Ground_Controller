#include "./ColourParser.hpp"
#include "../AGCException.hpp"
#include <cctype>
#include <format>
#include <iostream>
#include <ostream>
#include <string>

ColourParser::Token ColourParser::next_token() {
    this->skip_whitespaces();
    Token current;
    char curr_char = this->lexer.curr_char;

    if (curr_char == '#') {
        // the #defind literal
        this->read_char();
        this->read_identifer();
        current.type = Define;
        current.literal = this->read_identifer();
    } else if (curr_char == ';') {
        this->skip_curr_line();
        current.type = Comment;
    } else if (is_letter()) {
        current.type = Identifier;
        current.literal = this->read_identifer();
    } else if (is_digit()) {
        current.type = Value;
        current.literal = this->read_identifer();
    } else if (is_eof()) {
        current.type = Eof;
        current.literal = "";
    } else {
        std::string msg =
            std::format("Invalid Position {}", this->lexer.position);
        throw AGCException(msg);
    }

    this->read_char();
    return current;
}
