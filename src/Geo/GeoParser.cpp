#include "./GeoParser.hpp"
#include "GeoMarkings.hpp"
#include <cassert>
#include <regex>
#include <spdlog/spdlog.h>

// TODO: parse "Geo.txt" file

GeoParser::GeoParser(const std::string input, ColourManager &color_manager,
                     Coordinate &center_ref)
    : color_manager(color_manager), center_ref(center_ref), input(input) {}

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
        switch (tok->type) {
        case COMMENT:
            break;
        case IDENT:
            if (airport_name.empty()) {
                airport_name = tok->literal;
            } else if (airport_icao_code.empty()) {
                airport_icao_code = tok->literal;
            } else {
                area_name = tok->literal;
            }
            break;
        case SINGLE_COORDS: {
            if (calibration_point == 4) {
                spdlog::debug("Max calibration points reached");
                break;
            }
            calibration_point++;
        } break;
        case COLOR_KEY:
            break;
        }
        delete tok;
    }
    return GeoMarkings::Header(airport_name, airport_icao_code, area_name);
}

[[nodiscard]] std::vector<GeoMarkings> GeoParser::parse_all() {
    //
    // EGCC Manchester      <optional text>       S53.21.00.000 W02.16.00.000
    // S53.21.00.000 W02.16.00.000
    //
    // <SINGLE_COORDS><SINGLE_COORDS><SINGLE_COORDS><SINGLE_COORDS><COLOR_KEY>
    // N051.28.33.761 W000.26.07.857 N051.28.33.215 W000.26.08.614 smrLLTaxiway
    // N051.28.33.215 W000.26.08.614 N051.28.33.054 W000.26.08.854 smrLLTaxiway
    // N051.28.33.054 W000.26.08.854 N051.28.32.869 W000.26.09.050 smrLLTaxiway
    // N051.28.32.869 W000.26.09.050 N051.28.32.716 W000.26.09.170 smrLLTaxiway
    // N051.28.32.716 W000.26.09.170 N051.28.32.538 W000.26.09.258 smrLLTaxiway
    // N051.28.32.538 W000.26.09.258 N051.28.32.381 W000.26.09.303 smrLLTaxiway
    //

    // parse this file
    GeoMarkings::Header header = this->parse_header();

    // body
    std::vector<std::string> coords;

    std::vector<GeoMarkings> out;
    GeoMarkings current(this->center_ref);

    for (const GeoParser::Lexer::Token *tok = this->next_token();
         tok != nullptr; tok = this->next_token()) {
        switch (tok->type) {
        case COMMENT:
            break;
        case IDENT: {
            // begins a new GeoMarkings -- so parse header
            out.push_back(current);
            current = GeoMarkings(this->center_ref);
            GeoMarkings::Header header = this->parse_header();
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
                line.start = Coordinate(coords.at(0), coords.at(0));
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
    return out;
}
