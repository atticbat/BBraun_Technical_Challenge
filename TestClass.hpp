#ifndef TESTCLASS_HPP
#define TESTCLASS_HPP

#include <functional>
#include <memory>

class TestClass {

public:
  TestClass();
  // constructors are in canonical form, this provides a constructor for Class
  // a(b) and a = b
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
  // getters and setters are the only way I will interface with my private local
  // variable
  void setLocalVariable(int local_var);
  int getLocalVariable() const;
  virtual const std::string
  toString() const; // to_string changed to camelCase, moreover, the return
                    // value of this funciton does not have to be editable, so I
                    // can make it const. The benefit of this is that now I can
                    // call this funciton with a constant instance of TestClass

private: // these variables should not be directly interfaced with by the
         // programmer, I have getters and setters for this
  // the naming convention for private variables, conventionally, should be
  // snake_case, with an underscore at the beginning
  std::function<double(double, double)> _callback_function;
  int _local_variable;
  struct MissingFunctionException; // custom exception for missing function
};

struct TestClass::MissingFunctionException : public std::exception {
public:
  const char *what() const throw();
};

#endif