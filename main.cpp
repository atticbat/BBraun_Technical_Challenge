#include "DerivedTestClass.hpp"
#include "PointerFactory.hpp"
#include <exception>
#include <iostream>
//<memory> taken from TestClass.hpp
//<string> needed to define a string type
#include <string>

// malpractice to have global variables like this

double calculateDivision(double first, double second) {
  return first / second;
} // rename to reflect its actual function

double calculateSum(double first, double second) {
  return first + second;
} // calculateSum not used here but it was brought here over keeping it as a
  // function in TestClass, otherwise what's the point of passing callback
  // functions? (used to be called do_something_else)

// in order to use a child class in this context the parameter must become a
// base class pointer
void describe(TestClass *t) { std::cout << t->toString() << std::endl; }

int test() {
  PointerFactory
      factory; // normally factory classes double up as abstract classes to
               // multiple inheriting classes but here that's unnecessary
  // the reason why I did't keep the pointer generations in the TestClass is
  // because you would need an instance of TestClass to create an instance of
  // TestClass, which doesn't make sense
  std::unique_ptr<TestClass> testClass = factory.generateFirstClass(
      baseClass); // going with the theme of the original main, first pointer is
                  // a unique pointer, second is a shared pointer and third is a
                  // regular pointer

  std::shared_ptr<TestClass> secondClass = factory.generateSecondClass(
      baseClass); // shared pointer was not utilised in the example, so I kept
                  // it as is

  TestClass *derivedClass = factory.generateThirdClass(
      childClass); // this derivedClass instance had to be altered to accomodate
                   // for polymorphism

  auto thirdClass = factory.generateThirdClass(
      baseClass); // a constant pointer will be unable to set the local
                  // variable, so the const has to go

  thirdClass->setLocalVariable(
      5); // naming convention is camelCase for function names, the function is
          // changed for the sake of consistency

  int result = 0; // result was uninitialised at first, meaning that whatever
                  // data was leftover in the memory from a former allocation
                  // would be the value of the integer

  std::string filename =
      "testfile.txt"; // variables such as these should not be set as globals,
                      // because they're only required in this scope

  try {
    testClass->writeToFile(
        filename, result); // this file may already exist and the user may have
                           // tampered with the permissions on this file, in
                           // this scenario the file open fails and I throw an
                           // exception, it is important to protect against this
  } catch (std::exception &ex) {
    std::cerr << ex.what()
              << std::endl; // exception output printed to standard error
  }

  try {
    result = testClass->callCallbackFunction(
        2.0, 1.0); // point of failure will be a missing callback function, for
                   // this a try catch is necessary
    std::cout
        << "result of 2.0 / 1.0: " << result
        << std::endl; // result is being printed to show the outcome (there
                      // won't be any here since callCallbackFunction will fail)
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }

  try {
    testClass->writeToFile(filename, result);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }

  testClass->setCallbackFunction(
      calculateDivision); // callback function renamed to reflect its purpose

  try {
    result = testClass->callCallbackFunction(
        3.0, 1.0); // now with a callback function we'll have the proper
                   // functionality
    std::cout << "result of 3.0 / 1.0: " << result << std::endl;
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }

  try {
    testClass->writeToFile(filename, result);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }

  describe(derivedClass);

  try {
    testClass->checkInputValidity(
        -1); // checkInputValidity used to only accept unsigned integers, but if
             // you pass a negative number into this then the data will overflow
             // and the number would become UINT_MAX, to get the correct throw
             // error I changed the parameter to take integers
  } catch (std::invalid_argument ex) {
    std::cout << ex.what();
  } catch (...) {
    std::cout << "error occured";
  }

  return 0;
}

int main() // argv and argc were not being used so I removed them
{
  int ret = test();
  // system("leaks technical_challenge");
  return ret;
}
