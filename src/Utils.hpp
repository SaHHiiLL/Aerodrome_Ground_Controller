#pragma once
#include <string>
#include <vector>

namespace Utils {

std::vector<std::string> split_whitespace(const std::string &str);

class StringTrim {
public:
    // trim from start (in place)
    static void ltrim(std::string &s);

    // trim from end (in place)
    static void rtrim(std::string &s);

    // trim from both ends
    static void trim(std::string &s);
};

} // namespace Utils
