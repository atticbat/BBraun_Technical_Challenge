#ifndef TESTCLASS_HPP
#define TESTCLASS_HPP

#include <functional>

template <typename T> class TestClass {

public:
  TestClass();
  TestClass(const TestClass &copy);
  TestClass &operator=(const TestClass &copy);
  // in polymorphic classes the destructor has to be virtual, so to destroy the
  // parent and child upon delete
  virtual ~TestClass();
  double callCallbackFunction(T first, T second);
  void checkInputValidity(int first); // questionable implementation
  void writeToFile(std::string filename, double value_to_write);
  void setCallbackFunction(std::function<T(T, T)> callback);
  std::function<T(T, T)> getCallbackFunction() const;
  // void setLocalVariable(int local_var);
  // int getLocalVariable() const;
  virtual std::string to_string();

private:
  std::function<T(T, T)> _callback_function;
  // int _local_variable;
  struct MissingFunctionException;
};

template <typename T>
struct TestClass<T>::MissingFunctionException : public std::exception {
public:
  const char *what() const throw();
};

#include "TestClass.tpp"

#endif