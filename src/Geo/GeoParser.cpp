#include "./GeoParser.hpp"
#include "GeoMarkings.hpp"
#include <cassert>
#include <regex>
#include <spdlog/spdlog.h>

// TODO: parse "Geo.txt" file

GeoParser::GeoParser(const std::string &input, ColourManager &color_manager,
                     Coordinate &center_ref)
    : input(input), lexer(input), color_manager(color_manager), center_ref(center_ref) {
    this->lexer = Lexer(input);
}

const std::regex COORD_REGEX(R"([N|S|W|E]\d{3}.\d{2}.\d{2}.\d{3})");
GeoParser::Lexer::Token *GeoParser::next_token() {
    GeoParser::Lexer::Token *tok = nullptr;
    this->lexer.skip_whitespace();

    if (this->lexer.is_eof()) {
        return nullptr;
    }

    switch (this->lexer.curr_char) {
    case ';': {
        tok = new GeoParser::Lexer::Token();
        this->lexer.skip_line();
        tok->type = TokenType::COMMENT;
        break;
    }
    default: {
        if (this->lexer.is_letter()) {
            std::string ident = this->lexer.read_to_space();
            if (std::regex_match(ident, COORD_REGEX)) {
                tok = new GeoParser::Lexer::Token();
                tok->literal = ident;
                tok->type = TokenType::SINGLE_COORDS;
            } else if (this->color_manager.is_valid(ident)) {
                tok = new GeoParser::Lexer::Token();
                tok->type = TokenType::COLOR_KEY;
                tok->literal = ident;
            } else {
                tok = new GeoParser::Lexer::Token();
                tok->type = TokenType::IDENT;
                tok->literal = ident;
            }
            break;
        }
    }
    }
    this->lexer.read_next();
    return tok;
}

GeoMarkings::Header GeoParser::parse_header() {
    std::string airport_name;
    std::string airport_icao_code;
    std::optional<std::string> area_name;
    int calibration_point = 0;

    // Header
    for (const GeoParser::Lexer::Token *tok = this->next_token();
         tok != nullptr; tok = this->next_token()) {
        bool exit = false;
        switch (tok->type) {
        case COMMENT:
            break;
        case IDENT:
            if (airport_icao_code.empty()) {
                airport_icao_code = tok->literal;
            } else if (airport_name.empty()) {
                airport_name = tok->literal;
            } else {
                area_name = tok->literal;
            }
            break;
        case SINGLE_COORDS: {
            if (calibration_point == 3) {
                spdlog::debug("Max calibration points reached");
                exit = true;
            }
            calibration_point++;
        } break;
        case COLOR_KEY:
            break;
        }

        delete tok;

        if (exit) {
            break;
        }
    }
    return GeoMarkings::Header(airport_name, airport_icao_code, area_name);
}

[[nodiscard]] std::vector<GeoMarkings> GeoParser::parse_all() {

    GeoMarkings::Header header = this->parse_header();

    // body
    std::vector<std::string> coords;

    std::vector<GeoMarkings> out;
    GeoMarkings current(this->center_ref);
    current.set_header(header);

    for (const GeoParser::Lexer::Token *tok = this->next_token();
         tok != nullptr; tok = this->next_token()) {
        switch (tok->type) {
        case COMMENT:
            break;
        case IDENT: {
            // begins a new GeoMarkings -- so parse header
            out.push_back(current);
            current = GeoMarkings(this->center_ref);
            header = this->parse_header();
            current.set_header(header);
            break;
        }
        case SINGLE_COORDS: {
            coords.push_back(tok->literal);
            break;
        }
        case COLOR_KEY:
            if (coords.size() == 4) {
                GeoMarkings::Line line;
                line.color = this->color_manager.to_raylib(tok->literal);
                line.start = Coordinate(coords.at(0), coords.at(1));
                line.end = Coordinate(coords.at(2), coords.at(3));
                current.add_line(line);
                coords.clear();
            } else {
                spdlog::error("Invalid number of coords {}", coords.size());
            }
            // marks the end of one line
            break;
        }
        delete tok;
    }
    out.push_back(std::move(current));
    return out;
}
