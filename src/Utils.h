#include <optional>
#include <string>
#include <vector>


namespace Utils {
    class StringSplit {
    public:
        // Constructor that takes a string reference and delimiter
        StringSplit(const std::string& str, char delimiter)
            : data(str), delimiter(delimiter), start(str.c_str()), end(start) { }

        // Function that returns the next substring
        char* next();

        std::vector<std::string> collect();

    private:
        const std::string& data;  // Original string
        char delimiter;          // Delimiter for splitting
        const char* start;       // Pointer to the start of the current substring
        const char* end;         // Pointer to the end of the current substring
        
        int start_i{};
        int end_i{};
    };

}
