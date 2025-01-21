#include "ColourManager.hpp"
#include "../ResourceManager.hpp"
#include "./ColourParser.hpp"
#include <string>

ColourManager::ColourManager(std::filesystem::path path) {
    ResourceManager &rm = ResourceManager::Instance();
    std::string res = rm.read_file_abs(path);
    ColourParser parser = ColourParser(res, this->colours);
    parser.parse();
}

ColourManager::~ColourManager() {}
