#include "Exceptions.hpp"

const char *MissingFunctionException::what() const throw() {
  return ("Exception: Function missing");
}