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
    } else if (curr_char == ';') {
        this->skip_curr_line();
        current.type = Comment;
    } else if (is_letter()) {
        current.literal = (char *)this->read_identifer().c_str();
        current.type = Identifier;
    } else if (is_digit()) {
        current.literal = (char *)this->read_identifer().c_str();
        current.type = Value;
    } else if (is_eof()) {
        current.type = Eof;
    } else {
        std::string msg =
            std::format("Invalid input: {},", this->lexer.position);
        std::cout << curr_char << std::endl;
        throw AGCException(msg);
    }

    this->read_char();
    return current;
}
