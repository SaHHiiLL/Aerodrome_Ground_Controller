#include "./LabelParser.hpp"
#include "raylib.h"
#include <regex>
#include <stdexcept>

LabelParser::Lexer::Token *LabelParser::next_token() {
    LabelParser::Lexer::Token *tok = nullptr;
    this->lexer.skip_whitespace();
    if (this->lexer.is_eof())
        return nullptr;

    switch (this->lexer.curr_char) {
    case '"':
        tok = new LabelParser::Lexer::Token();
        {
            this->lexer.read_next();
            std::string label = this->lexer.read_until('\"');
            if (this->lexer.curr_char != '"') {
                // we reached EOF, invalid file
                throw std::invalid_argument(
                    "Expected quotation, got EOF :skull:");
            }
            tok->type = TokenType::Label;
            tok->literal = label;
            // Read leading "
            this->lexer.read_next();
        }
        break;
    case ';':
        tok = new LabelParser::Lexer::Token();
        lexer.skip_line();
        tok->type = TokenType::Comment;
        break;
    default:
        if (this->lexer.is_letter()) {
            std::string ident = this->lexer.read_to_space();
            const std::regex coord_regex(R"([N|S|W|E]\d{3}.\d{2}.\d{2}.\d{3})");
            if (std::regex_match(ident, coord_regex)) {

                tok = new LabelParser::Lexer::Token();
                tok->literal = ident;
                tok->type = TokenType::SingleCoordinate;
            } else if (this->colors.is_valid(ident)) {
                tok = new LabelParser::Lexer::Token();
                tok->type = TokenType::ColorKey;
                tok->literal = ident;
            } else {
                // Invalid
                TraceLog(LOG_WARNING, "Token of literal %s is invalid",
                         ident.data());
            }
        }
        break;
    }

    this->lexer.read_next();
    return tok;
}

std::vector<AirportLabel> LabelParser::parse_all() {
    std::vector<AirportLabel> labels;

    std::string current_label;
    std::string current_ns_coords;
    std::string current_we_coords;

    for (const LabelParser::Lexer::Token *tok = this->next_token();
         tok != nullptr; tok = this->next_token()) {
        switch (tok->type) {
        case TokenType::Comment: {
            // Ignore comments
            break;
        }
        case TokenType::Label: {
            current_label = tok->literal;
            break;
        }
        case TokenType::Quotation: {
            break;
        }
        case TokenType::SingleCoordinate: {
            if (current_ns_coords.empty()) {
                current_ns_coords = tok->literal;
            } else {
                current_we_coords = tok->literal;
            }
            break;
        }
        case TokenType::ColorKey: {
            std::string current_color = tok->literal;
            // Every option should be filled
            // NOTE: color is currently ignore - I am just lazy
            if (!current_label.empty() && !current_ns_coords.empty() &&
                !current_we_coords.empty() && !current_color.empty()) {

                if (this->colors.is_valid(current_color)) {
                    Coordinate coords =
                        Coordinate(current_ns_coords, current_we_coords);
                    auto color = this->colors.to_raylib(current_color);
                    AirportLabel l(current_label, coords, this->center_ref,
                                   color);
                    labels.push_back(l);

                    current_label.clear();
                    current_ns_coords.clear();
                    current_we_coords.clear();
                    current_color.clear();
                }
            } else {
                TraceLog(LOG_WARNING, "Invalid file");
            }
            break;
        }
        }

        delete tok;
    }

    return labels;
}
