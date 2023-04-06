#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

struct MissingFunctionException : public std::exception {
public:
  const char *what() const throw();
};

#endif