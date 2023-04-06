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
  std::ofstream file(filename, std::ios::app);
  if (!file.is_open())
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
  return it->second.getFunct(INT)._int.callCallbackFunction(first, second);
}
float TestClass::utiliseCallbackFunction(std::string key, float first,
                                         float second) {
  auto it = _callback_functions.find(key);
  if (it == _callback_functions.end())
    throw MissingFunctionException();
  return it->second.getFunct(FLOAT)._float.callCallbackFunction(first, second);
}
double TestClass::utiliseCallbackFunction(std::string key, double first,
                                          double second) {
  auto it = _callback_functions.find(key);
  if (it == _callback_functions.end())
    throw MissingFunctionException();
  return it->second.getFunct(DOUBLE)._double.callCallbackFunction(first,
                                                                  second);
}
std::string TestClass::to_string() { return "Test class"; }
