#include "./ColourParser.hpp"
#include "../AGCException.hpp"
#include <cctype>
#include <format>
#include <iostream>
#include <ostream>
#include <string>

void ColourParser::read_char() {
    if (this->lexer.read_position >= this->lexer.input.size()) {
        this->lexer.curr_char = 0;
    } else {
        this->lexer.curr_char = this->lexer.input[this->lexer.read_position];
        this->lexer.position = this->lexer.read_position;
        this->lexer.read_position++;
    }
}

void ColourParser::skip_whitespaces() {
    while (std::isspace(this->lexer.curr_char)) {
        this->read_char();
    }
}

void ColourParser::skip_curr_line() {
    while (this->lexer.curr_char != '\n')
        this->read_char();
    this->read_char();
}

bool ColourParser::is_letter() { return std::isalpha(this->lexer.curr_char); }
bool ColourParser::is_digit() { return std::isdigit(this->lexer.curr_char); }

uint64_t ColourParser::read_number() {
    std::string res;
    while (this->is_letter()) {
        res.push_back(this->lexer.curr_char);
        this->read_char();
    }
    return atoi(res.c_str());
}

std::string ColourParser::read_identifer() {
    std::string res;
    while (this->is_letter() || this->is_digit()) {
        res.push_back(this->lexer.curr_char);
        this->read_char();
    }
    return res;
}

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
