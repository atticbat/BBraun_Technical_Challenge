#ifndef TESTCLASS_HPP
#define TESTCLASS_HPP

#include <functional>
#include <memory>

class TestClass {

public:
  TestClass();
  TestClass(const TestClass &copy);
  TestClass &operator=(const TestClass &copy);
  // in polymorphic classes the destructor has to be virtual, so to destroy the
  // parent and child upon delete
  virtual ~TestClass();
  double callCallbackFunction(double first, double second);
  void checkInputValidity(int first);
  void writeToFile(std::string filename, double value_to_write);
  void setCallbackFunction(std::function<double(double, double)> callback);
  std::function<double(double, double)> getCallbackFunction() const;
  void setLocalVariable(int local_var);
  int getLocalVariable() const;
  virtual std::string to_string();

private:
  std::function<double(double, double)> _callback_function;
  int _local_variable;
  struct MissingFunctionException;
};

struct TestClass::MissingFunctionException : public std::exception {
public:
  const char *what() const throw();
};

#endif