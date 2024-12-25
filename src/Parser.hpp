#pragma once
#include <cstdint>
#include <string>
#include <vector>

#define LEXER_IMPL(X)                                                          \
public:                                                                        \
    struct Token {                                                             \
        std::string literal;                                                   \
        TokenType type;                                                        \
    };                                                                         \
    struct Lexer {                                                             \
        std::vector<char> input;                                               \
        size_t position;                                                       \
        size_t read_position;                                                  \
        char curr_char;                                                        \
    };                                                                         \
    Token next_token();                                                        \
    size_t position() { return this->lexer.position; }                         \
    X(std::string input) {                                                     \
        this->lexer.input = std::vector<char>(input.begin(), input.end());     \
        this->lexer.position = 0;                                              \
        this->lexer.read_position = 0;                                         \
        this->lexer.curr_char = this->lexer.input[0];                          \
    }                                                                          \
                                                                               \
    Lexer lexer;                                                               \
    bool is_eof() { return this->lexer.curr_char == 0; }                       \
    void read_char() {                                                         \
        if (this->lexer.read_position >= this->lexer.input.size()) {           \
            this->lexer.curr_char = 0;                                         \
        } else {                                                               \
            this->lexer.curr_char =                                            \
                this->lexer.input[this->lexer.read_position];                  \
            this->lexer.position = this->lexer.read_position;                  \
            this->lexer.read_position++;                                       \
        }                                                                      \
    }                                                                          \
    void skip_whitespaces() {                                                  \
        while (std::isspace(this->lexer.curr_char)) {                          \
            this->read_char();                                                 \
        }                                                                      \
    }                                                                          \
    void skip_curr_line() {                                                    \
        while (this->lexer.curr_char != '\n')                                  \
            this->read_char();                                                 \
        this->read_char();                                                     \
    }                                                                          \
    bool is_letter() { return std::isalpha(this->lexer.curr_char); }           \
    bool is_digit() { return std::isdigit(this->lexer.curr_char); }            \
    uint64_t read_number() {                                                   \
        std::string res;                                                       \
        while (this->is_letter()) {                                            \
            res.push_back(this->lexer.curr_char);                              \
            this->read_char();                                                 \
        }                                                                      \
        return atoi(res.c_str());                                              \
    }                                                                          \
    std::string read_identifer() {                                             \
        std::string res;                                                       \
        while (this->is_letter() || this->is_digit()) {                        \
            res.push_back(this->lexer.curr_char);                              \
            this->read_char();                                                 \
        }                                                                      \
        return res;                                                            \
    }

/*
 * Declare a `TokenType` enum and just implement `next_token` method for the
class you whish to tokenise class Parser { enum TokenType { HELLO };
    LEXER_IMPL(Parser)
public:
    Parser(Lexer lexer, std::string input)
        : lexer(std::move(lexer)), input(std::move(input)) {}
};
*/
