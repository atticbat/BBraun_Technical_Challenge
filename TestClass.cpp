#include "TestClass.hpp"
#include <fstream>
// headers included here were supposed to be <> to indicate that they are in the
// global include directories and not local
#include <exception>
#include <iostream>
#include <mutex>

TestClass::TestClass()
    : _callback_function(NULL), _local_variable(0) {
} // it's important that the _callback_function is initialised to NULL, so that
  // I can compare it to NULL when I check for whether there is already a
  // callback function stored
TestClass::TestClass(const TestClass &copy) {
  *this = copy;
} // the copy constructor simply calls the copy assignment constructor
TestClass &TestClass::operator=(const TestClass &copy) {
  if (this != &copy) {
    setCallbackFunction(copy.getCallbackFunction());
    setLocalVariable(copy.getLocalVariable());
  }
  return *this;
}
TestClass::~TestClass() {}
double TestClass::callCallbackFunction(double first, double second) {
  if (!_callback_function)
    throw MissingFunctionException();
  return _callback_function(first, second);
}
// value being passed here from main is a negative number, so I've changed the
// parameter to suit negative inputs
void TestClass::checkInputValidity(int first) {
  if (first < 0) {
    throw std::invalid_argument("Invalid argument passed");
  }
  if (first > 100) {
    throw std::out_of_range("Number out of range");
  }
}
void TestClass::writeToFile(std::string filename, double value_to_write) {
  // there won't be any data races with one thread
  std::ofstream file(filename,
                     std::ios::app); // writeToFile now appends, the behaviour
                                     // is more practical as a log file
  if (!file.is_open()) // in case the permissions to an already existing
                       // testfile.txt are disallowing editing
    throw std::runtime_error("Unable to open file");
  file << value_to_write << std::endl;
  file.close();
  if (file.is_open())
    throw std::runtime_error("Unable to close file");
}
void TestClass::setCallbackFunction(
    std::function<double(double, double)> callback) {
  _callback_function = callback;
}
std::function<double(double, double)> TestClass::getCallbackFunction() const {
  return _callback_function;
}
void TestClass::setLocalVariable(int local_var) { _local_variable = local_var; }
int TestClass::getLocalVariable() const { return _local_variable; }
const std::string TestClass::toString() const { return "Test class"; }
const char *TestClass::MissingFunctionException::what() const throw() {
  return ("Exception: function missing");
}
