#include "ColourManager.hpp"
#include "../ResourceManager.hpp"
#include "./ColourParser.hpp"
#include <string>

ColourManager::ColourManager(std::filesystem::path path) {
    std::string res = ResourceManager::read_file_abs(path);
    ColourParser parser = ColourParser(res, this->colours);
    parser.parse();
}
bool ColourManager::is_valid(const std::string &key) const {
    return this->colours.contains(key);
}
