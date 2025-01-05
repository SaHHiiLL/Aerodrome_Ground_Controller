#pragma once
#include <string>
#include <vector>

namespace Utils {

std::vector<std::string> split_whitespace(const std::string &str);

class StringTrim {
public:
    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(),
                std::ranges::find_if(s.begin(), s.end(), [](unsigned char ch) {
                    return !std::isspace(ch);
                }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::ranges::find_if(
                    s.rbegin(), s.rend(),
                    [](unsigned char ch) { return !std::isspace(ch); })
                    .base(),
                s.end());
    }

    // trim from both ends
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }
};

} // namespace Utils
