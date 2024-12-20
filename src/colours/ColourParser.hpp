#pragma once

#include <cctype>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
class ColourParser {

public:
    enum TokenType { Comment = 0, Eof, Define, Identifier, Value };

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
    ColourParser(std::string input) {
        this->lexer.input = std::vector<char>(input.begin(), input.end());
        this->lexer.position = 0;
        this->lexer.read_position = 0;
        this->lexer.curr_char = this->lexer.input[0];
    }

private:
    Lexer lexer;
    std::unordered_map<std::string, std::uint64_t> colours;

    std::string input;

    void read_char();
    void skip_whitespaces();
    void skip_curr_line();
    bool is_letter();
    bool is_digit();
    uint64_t read_number();
    std::string read_identifer();
};
