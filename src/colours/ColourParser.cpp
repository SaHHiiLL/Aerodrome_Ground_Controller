#include "./ColourParser.hpp"
#include <stdexcept>

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
    while (this->lexer.curr_char == ' ' || this->lexer.curr_char == '\n') {
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
    while (this->is_letter()) {
        res.push_back(this->lexer.curr_char);
        this->read_char();
    }
    return res;
}

ColourParser::Token ColourParser::next_token() {
    this->skip_whitespaces();
    Token current;

    switch (this->lexer.curr_char) {
    case '#': {
        this->read_char();
        // the #defind literal
        this->read_identifer();
        std::string key = this->read_identifer();
        std::uint64_t val = this->read_number();
        this->colours.at(key) = val;
        current.type = Comment;
    }
    case ';': { // Comments
        this->skip_curr_line();
        current.type = Comment;
    }
    default: {
        std::string err_msg("Invalid char: %c, at position: %d",
                            this->lexer.curr_char, this->lexer.position);
        throw std::invalid_argument(err_msg);
    }
    };

    this->read_char();
    return current;
}
