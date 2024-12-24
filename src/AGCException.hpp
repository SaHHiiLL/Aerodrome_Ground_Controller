#pragma once

#include <exception>
#include <string>
class AGCException : public std::exception {
    std::string inner;

public:
    AGCException(std::string inner) : inner(inner) {}
    const char *what() const throw() { return inner.c_str(); }
};
