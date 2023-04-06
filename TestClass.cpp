#include "TestClass.hpp"
#include <fstream>
// headers included here were supposed to be <> to indicate that they are in the
// global include directories and not local
#include <exception>
#include <iostream>
#include <mutex>

TestClass::TestClass() {}
TestClass::TestClass(const TestClass &copy) { *this = copy; }
TestClass &TestClass::operator=(const TestClass &copy) {
  if (this != &copy) {
    auto callback = copy.getCallbackFunctions();
    auto it = callback.begin();
    for (; it != callback.end(); it++) {
      addCallbackFunction(it->first, it->second);
    }
  }
  return *this;
}
TestClass::~TestClass() {}
void TestClass::writeToFile(std::string filename, double value_to_write) {
  // there won't be any data races with one thread
  std::ofstream file(filename, std::ios::app); // writeToFile now appends
  if (!file.is_open()) // in case the permissions to an already existing
                       // testfile.txt are disallowing editing
    throw std::runtime_error("Unable to open file");
  file << value_to_write << std::endl;
  file.close();
  if (file.is_open())
    throw std::runtime_error("Unable to close file");
}
void TestClass::addCallbackFunction(std::string key, passedFunction funct) {
  std::pair<std::string, passedFunction> data(key, funct);
  _callback_functions.insert(data);
}
void TestClass::removeCallbackFunction(std::string key) {
  auto it = _callback_functions.find(key);
  if (it == _callback_functions.end())
    throw MissingFunctionException();
  _callback_functions.erase(it);
}
std::map<std::string, passedFunction> TestClass::getCallbackFunctions() const {
  return _callback_functions;
}
int TestClass::utiliseCallbackFunction(std::string key, int first, int second) {
  auto it = _callback_functions.find(key);
  if (it == _callback_functions.end())
    throw MissingFunctionException();
  return it->second.getFunct()._int.callCallbackFunction(first, second);
}
float TestClass::utiliseCallbackFunction(std::string key, float first,
                                         float second) {
  auto it = _callback_functions.find(key);
  if (it == _callback_functions.end())
    throw MissingFunctionException();
  return it->second.getFunct()._float.callCallbackFunction(first, second);
}
double TestClass::utiliseCallbackFunction(std::string key, double first,
                                          double second) {
  auto it = _callback_functions.find(key);
  if (it == _callback_functions.end())
    throw MissingFunctionException();
  return it->second.getFunct()._double.callCallbackFunction(first, second);
}

// void TestClass::setLocalVariable(int local_var) { _local_variable =
// local_var; } int TestClass::getLocalVariable() const { return
// _local_variable; }
std::string TestClass::to_string() { return "Test class"; }
const char *TestClass::MissingFunctionException::what() const throw() {
  return ("Exception: Function missing");
}
