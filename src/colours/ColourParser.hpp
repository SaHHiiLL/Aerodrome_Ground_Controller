#pragma once

#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

// Lazy Colour file Parser
class ColourParser {

public:
    enum TokenType {
        Eof = 0,
        Comment,
        Define,
        Identifier,
        Value,
        InValid = -1
    };

    struct Token {
        char *literal;
        TokenType type;
    };

    struct Lexer {
        std::vector<char> input;
        size_t position;
        size_t read_position;
        char curr_char;
    };
    Token next_token();
    size_t position() { return this->lexer.position; }
    bool is_eof() { return this->lexer.curr_char == 0; }

    ColourParser(std::string input) {
        this->lexer.input = std::vector<char>(input.begin(), input.end());
        this->lexer.position = 0;
        this->lexer.read_position = 0;
        this->lexer.curr_char = this->lexer.input[0];
    }

private:
    Lexer lexer;

    std::string input;

    void read_char();
    void skip_whitespaces();
    void skip_curr_line();
    bool is_letter();
    bool is_digit();
    uint64_t read_number();
    std::string read_identifer();
};
