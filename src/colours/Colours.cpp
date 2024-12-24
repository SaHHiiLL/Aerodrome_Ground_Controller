#include "Colours.hpp"
#include "../AGCException.hpp"
#include "../ResourceManager.hpp"
#include "./ColourParser.hpp"
#include <string>

Colours::Colours(std::filesystem::path path) {
    ResourceManager &rm = ResourceManager::Instance();
    std::string res = rm.read_file_abs(path);
    ColourParser parser = ColourParser(res);
    std::string last_ident{};

    for (ColourParser::Token toke = parser.next_token(); toke.type > 0;
         toke = parser.next_token()) {

        if (toke.type == ColourParser::TokenType::Identifier) {
            last_ident = toke.literal;
        }

        if (toke.type == ColourParser::TokenType::Value) {
            if (!last_ident.empty()) {
                std::string msg = std::format(
                    "Invalid identifer for colour parsing at line: {}",
                    parser.position());
                throw AGCException(msg);
            } else {
                this->colours[last_ident] =
                    std::stoul(std::string(toke.literal));
            }
        }
        last_ident.clear();
    }
}
