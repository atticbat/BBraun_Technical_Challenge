#include "DerivedTestClass.hpp"
#include <exception>
#include <iostream>
#include <memory>
#include <string>

enum ClassType { baseClass, childClass };

std::unique_ptr<TestClass> generateFirstClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (std::unique_ptr<TestClass>(new TestClass()));
  case childClass:
    return (std::unique_ptr<DerivedTestClass>(new DerivedTestClass()));
  default:
    return NULL;
  }
}
std::shared_ptr<TestClass> generateSecondClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (std::shared_ptr<TestClass>(new TestClass()));
  case childClass:
    return (std::shared_ptr<DerivedTestClass>(new DerivedTestClass()));
  default:
    return NULL;
  }
}
TestClass *generateThirdClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (new TestClass());
  case childClass:
    return (new DerivedTestClass());
  default:
    return NULL;
  }
}

double calculateDivision(double first, double second) { return first / second; }

int calculateSum(int first, int second) { return first + second; }

void describe(TestClass *t) { std::cout << t->to_string() << std::endl; }

int test() {
  std::cout << RED
            << "Test with single pointer, with a callback that exists and one "
               "that doesn't"
            << NOCOLOUR << std::endl;
  try {
    std::unique_ptr<TestClass> firstClass = generateFirstClass(baseClass);
    passedFunction funct(
        DOUBLE, validFunction(CallbackFunction<double>(calculateDivision)));

    firstClass->addCallbackFunction("divide", funct);
    std::cout << firstClass->utiliseCallbackFunction("divide", 82.0, 2.0)
              << std::endl;
    std::cout << firstClass->utiliseCallbackFunction("sum", 21.0, 21.0)
              << std::endl;
  } catch (std::exception ex) {
    std::cerr << ex.what() << std::endl;
  }
  std::cout << RED
            << "Test with faulty parameters passed to callback function "
               "initialisation"
            << NOCOLOUR << std::endl;
  try {
    std::shared_ptr<TestClass> secondClass = generateSecondClass(baseClass);
    passedFunction funct(
        INT, validFunction(CallbackFunction<double>(calculateDivision)));
    secondClass->addCallbackFunction("divide", funct);
    std::cout << secondClass->utiliseCallbackFunction("divide", 0.4, 0.2)
              << std::endl;
  } catch (std::exception ex) {
    std::cerr << ex.what() << std::endl;
  }
  //    int result = 0; // result was not initialised, so it was just equal to
  //                    // whatever data was allocated before
  //    testClass->writeToFile(filename, result);
  //    testClass->setCallbackFunction(calculateDivision);
  //    result = testClass->callCallbackFunction(2.0, 1.0);
  //    testClass->writeToFile(filename, result);
  //    testClass->setCallbackFunction(calculateSum);
  //    result = testClass->callCallbackFunction(3.0, 1.0);
  //    testClass->writeToFile(filename, result);
  //    // DerivedTestClass derivedClass;
  //    TestClass<int> *derivedClass = generateThirdClass<int>(
  //        childClass); // DerivedTestClass will attempt to be used in
  //        describe,
  //                     // which should take a TestClass pointer to
  //                     facilitate
  //                     // polymorphism
  //    try {
  //      describe(derivedClass);
  //    } catch (const std::exception &e) {
  //      std::cerr << e.what() << std::endl;
  //    }
  //    delete derivedClass;
  //    try {
  //      testClass->checkInputValidity(-1);
  //    } catch (std::invalid_argument ex) {
  //      std::cout << ex.what() << std::endl;
  //    } catch (...) {
  //      std::cout << "error occured" << std::endl;
  //    }
  //    auto thirdClass = generateThirdClass<double>(childClass);
  //    delete thirdClass;
  // catch (const std::exception &e) {
  //   std::cerr << e.what() << std::endl;
  // }
  return (0);
}

int main() // char **argv is atypical I think, so I changed it to something more
           // common
{
  int ret = test();
  // system("leaks technical_challenge");
  return ret;
}
