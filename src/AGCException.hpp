#pragma once

#include <exception>
#include <string>
class AGCException : public std::exception {
    std::string inner;

public:
    AGCException(std::string inner) : inner(inner) {}
    const char *what() const noexcept { return inner.c_str(); }
};
