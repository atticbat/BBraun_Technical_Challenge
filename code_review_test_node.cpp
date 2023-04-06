#include "DerivedTestClass.hpp"
#include <iostream>
#include <memory>
#include <string>

enum ClassType { baseClass, childClass };

template <typename T>
std::unique_ptr<TestClass<T>> generateFirstClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (std::unique_ptr<TestClass<T>>(new TestClass<T>()));
  case childClass:
    return (std::unique_ptr<DerivedTestClass<T>>(new DerivedTestClass<T>()));
  default:
    return NULL;
  }
}
template <typename T>
std::shared_ptr<TestClass<T>> generateSecondClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (std::shared_ptr<TestClass<T>>(new TestClass<T>()));
  case childClass:
    return (std::shared_ptr<DerivedTestClass<T>>(new DerivedTestClass<T>()));
  default:
    return NULL;
  }
}
template <typename T> TestClass<T> *generateThirdClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (new TestClass<T>());
  case childClass:
    return (new DerivedTestClass<T>());
  default:
    return NULL;
  }
}

double calculateDivision(double first, double second) { return first / second; }

double calculateSum(double first, double second) { return first + second; }

// in order to use a child class in this context the parameter must become a
// base class pointer
template <typename T> void describe(TestClass<T> *t) {
  std::cout << t->to_string() << std::endl;
}

int test() {
  try {
    // PointerFactory factory;
    std::string filename = "testfile.txt";
    std::unique_ptr<TestClass<double>> testClass = generateFirstClass<double>(
        baseClass); // makes sense to just use a unique
                    // pointer instead of a regular pointer
    std::shared_ptr<TestClass<float>> secondClass = generateSecondClass<float>(
        childClass); // class returning instance of shared pointer is
                     // questionable
    secondClass->setCallbackFunction(calculateSum);
    std::cout << secondClass->callCallbackFunction(21.0, 21.0) << std::endl;
    int result = 0; // result was not initialised, so it was just equal to
                    // whatever data was allocated before
    testClass->writeToFile(filename, result);
    testClass->setCallbackFunction(calculateDivision);
    result = testClass->callCallbackFunction(2.0, 1.0);
    testClass->writeToFile(filename, result);
    testClass->setCallbackFunction(calculateSum);
    result = testClass->callCallbackFunction(3.0, 1.0);
    testClass->writeToFile(filename, result);
    // DerivedTestClass derivedClass;
    TestClass<int> *derivedClass = generateThirdClass<int>(
        childClass); // DerivedTestClass will attempt to be used in describe,
                     // which should take a TestClass pointer to facilitate
                     // polymorphism
    try {
      describe(derivedClass);
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
    delete derivedClass;
    try {
      testClass->checkInputValidity(-1);
    } catch (std::invalid_argument ex) {
      std::cout << ex.what() << std::endl;
    } catch (...) {
      std::cout << "error occured" << std::endl;
    }
    auto thirdClass = generateThirdClass<double>(childClass);
    delete thirdClass;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}

int main() // char **argv is atypical I think, so I changed it to something more
           // common
{
  int ret = test();
  // system("leaks technical_challenge");
  return ret;
}
