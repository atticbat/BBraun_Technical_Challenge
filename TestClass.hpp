#ifndef TESTCLASS_HPP
#define TESTCLASS_HPP

#include "CallbackFunction.hpp"
#include <functional>
#include <map>
#include <string>

enum validTypes { INVALID, INT, FLOAT, DOUBLE };
union validFunction {
  validFunction() {}
  validFunction(CallbackFunction<int> funct) : _int(funct) {}
  validFunction(CallbackFunction<float> funct) : _float(funct) {}
  validFunction(CallbackFunction<double> funct) : _double(funct) {}
  validFunction(const validFunction &copy) { *this = copy; }
  validFunction &operator=(const validFunction &copy) {
    if (this != &copy) {
      _int = copy._int;
      _float = copy._float;
      _double = copy._double;
    }
    return *this;
  }
  CallbackFunction<int> _int;
  CallbackFunction<float> _float;
  CallbackFunction<double> _double;
};

class passedFunction {

public:
  passedFunction() : _type(INVALID){};
  passedFunction(validTypes type, validFunction funct) {
    _funct = funct;
    _type = type;
  }
  passedFunction(const passedFunction &copy) {
    _funct = copy.getFunct();
    _type = copy.getType();
  }
  validFunction getFunct() const { return _funct; }
  validTypes getType() const { return _type; }

private:
  validFunction _funct;
  validTypes _type;
};

class TestClass {

public:
  TestClass();
  TestClass(const TestClass &copy);
  TestClass &operator=(const TestClass &copy);
  virtual ~TestClass();
  void addCallbackFunction(std::string key, passedFunction funct);
  void removeCallbackFunction(std::string key);
  std::map<std::string, passedFunction> getCallbackFunctions() const;
  int utiliseCallbackFunction(std::string key, int first, int second);
  float utiliseCallbackFunction(std::string key, float first, float second);
  double utiliseCallbackFunction(std::string key, double first, double second);
  void writeToFile(std::string filename, double value_to_write);
  virtual std::string to_string();

private:
  std::map<std::string, passedFunction> _callback_functions;
  struct MissingFunctionException;
};

struct TestClass::MissingFunctionException : public std::exception {
public:
  const char *what() const throw();
};

#endif