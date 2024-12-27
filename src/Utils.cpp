
// Function that returns the next substring
#include "./Utils.hpp"
#include <regex>
#include <vector>

char *Utils::StringSplit::next() {
    if (*end == '\0') {
        return nullptr;
    }

    start = end; // Start of the next substring

    while (*end != delimiter && *end != '\0') {
        ++end;
    }

    // Mark the current substring
    const char *substring = start;

    // Temporarily modify the end character to create a C-style string without
    // allocating
    if (*end != '\0') {
        *const_cast<char *>(end) = '\0'; // Temporarily terminate the string
        ++end; // Move to the next character after the delimiter
    }
    return const_cast<char *>(substring);
}

std::vector<std::string> Utils::StringSplit::collect() {
    std::vector<std::string> res;
    auto ne = this->next();
    while (ne != nullptr) {
        res.push_back(ne);
        ne = this->next();
    }
    return res;
}

std::vector<std::string> Utils::split_whitespace(const std::string &str) {
    // Regular expression to match one or more whitespace characters
    std::regex ws_re("\\s+");
    // Split the string using regex
    std::sregex_token_iterator it(str.begin(), str.end(), ws_re, -1);
    std::sregex_token_iterator reg_end;

    std::vector<std::string> result(it, reg_end); // Convert iterator to vector

    // Remove empty strings if any (in case of leading/trailing spaces)
    result.erase(std::remove(result.begin(), result.end(), ""), result.end());

    return result;
}
