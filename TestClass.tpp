#ifndef TESTCLASS_TPP
#define TESTCLASS_TPP
#include <exception>
#include <fstream>
#include <iostream>
#include <mutex>

template <typename T> TestClass<T>::TestClass() : _callback_function(NULL) {}
template <typename T> TestClass<T>::TestClass(const TestClass &copy) {
  *this = copy;
}
template <typename T>
TestClass<T> &TestClass<T>::operator=(const TestClass &copy) {
  if (this != &copy) {
    setCallbackFunction(copy.getCallbackFunction());
  }
  return *this;
}
template <typename T> TestClass<T>::~TestClass() {}
template <typename T>
double TestClass<T>::callCallbackFunction(T first, T second) {
  if (!_callback_function)
    throw MissingFunctionException();
  checkInputValidity(first);
  return _callback_function(first, second);
}
// value being passed here from main is a negative number, so I've changed the
// parameter to suit negative inputs
template <typename T> void TestClass<T>::checkInputValidity(int first) {
  if (first < 0) {
    throw std::invalid_argument("Invalid argument passed");
  }
  if (first > 100) {
    throw std::out_of_range("Number out of range");
  }
}
template <typename T>
void TestClass<T>::writeToFile(std::string filename, double value_to_write) {
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
template <typename T>
void TestClass<T>::setCallbackFunction(std::function<T(T, T)> callback) {
  _callback_function = callback;
}
template <typename T>
std::function<T(T, T)> TestClass<T>::getCallbackFunction() const {
  return _callback_function;
}
// void TestClass<T>::setLocalVariable(int local_var) { _local_variable =
// local_var; } int TestClass<T>::getLocalVariable() const { return
// _local_variable; }
template <typename T> std::string TestClass<T>::to_string() {
  return "Test class";
}
template <typename T>
const char *TestClass<T>::MissingFunctionException::what() const throw() {
  return ("Exception: Function missing");
}
#endif