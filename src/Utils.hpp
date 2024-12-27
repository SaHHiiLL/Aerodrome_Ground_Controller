#pragma once
#include <string>
#include <vector>

namespace Utils {

std::vector<std::string> split_whitespace(const std::string &str);
class StringSplit {
public:
    // Constructor that takes a string reference and delimiter
    StringSplit(const std::string &str, char delimiter)
        : data(str), delimiter(delimiter), start(str.c_str()), end(start) {}

    // Function that returns the next substring
    char *next();

    std::vector<std::string> collect();

private:
    const std::string &data; // Original string
    char delimiter;          // Delimiter for splitting
    const char *start;       // Pointer to the start of the current substring
    const char *end;         // Pointer to the end of the current substring

    int start_i{};
    int end_i{};
};

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
