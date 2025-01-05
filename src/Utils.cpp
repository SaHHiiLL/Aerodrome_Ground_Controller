
// Function that returns the next substring
#include "./Utils.hpp"
#include <regex>
#include <vector>

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
