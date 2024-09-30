#include <optional>
#include <string>


namespace Utils {
    class StringSplit {
    public:
        // Constructor that takes a string reference and delimiter
        StringSplit(const std::string& str, char delimiter)
            : data(str), delimiter(delimiter), start(str.c_str()), end(start) { }

        // Function that returns the next substring
        const std::optional<char*> next() {
            if (*end == '\0') {
                return std::nullopt;  // Return nullptr when all substrings are processed
            }

            start = end;  // Start of the next substring

            while (*end != delimiter && *end != '\0') {
                ++end;
            }

            // Mark the current substring
            const char* substring = start;

            // Temporarily modify the end character to create a C-style string without allocating
            if (*end != '\0') {
                *const_cast<char*>(end) = '\0';  // Temporarily terminate the string
                ++end;                           // Move to the next character after the delimiter
            }

            return const_cast<char*>(substring);
        }

    private:
        const std::string& data;  // Original string
        char delimiter;          // Delimiter for splitting
        const char* start;       // Pointer to the start of the current substring
        const char* end;         // Pointer to the end of the current substring
        
        int start_i;
        int end_i;
    };

}
