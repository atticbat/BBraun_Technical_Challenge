#include <iostream>
#include "PointerFactory.hpp"
#include "DerivedTestClass.hpp"
#include <memory>
//<string> needed to define a string type
#include <string>

//malpractice to have global variables like this

double  calculateDivision(double first, double second){
  return first/second;
}

double  calculateSum(double first, double second) {
  return first+second;
}

//in order to use a child class in this context the parameter must become a base class pointer
void describe(TestClass *t){
	std::cout<< t->to_string() << std::endl;
}

int test() {
  try
  {
    PointerFactory  factory;
    std::string filename = "testfile.txt";
    std::unique_ptr<TestClass> testClass = factory.generateFirstClass(baseClass); //makes sense to just use a unique pointer instead of a regular pointer
    std::shared_ptr<TestClass> secondClass = factory.generateSecondClass(childClass); //class returning instance of shared pointer is questionable
    secondClass->setCallbackFunction(calculateSum);
    std::cout << secondClass->callCallbackFunction(21.0, 21.0) << std::endl;
    int result = 0; //result was not initialised, so it was just equal to whatever data was allocated before
    testClass->writeToFile(filename,result); 
    testClass->setCallbackFunction(calculateDivision);
    result = testClass->callCallbackFunction(2.0,1.0);
    testClass->writeToFile(filename,result);
    testClass->setCallbackFunction(calculateSum);
    result = testClass->callCallbackFunction(3.0,1.0);
    testClass->writeToFile(filename, result);
    // DerivedTestClass derivedClass;
    TestClass  *derivedClass = factory.generateThirdClass(childClass); //DerivedTestClass will attempt to be used in describe, which should take a TestClass pointer to facilitate polymorphism
    try {
      describe(derivedClass);
    } catch(const std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
    delete derivedClass;
    try {
      testClass->checkInputValidity(-1);
    } catch ( std::invalid_argument ex){
      std::cout  << ex.what() << std::endl;
    } catch (...){
      std::cout << "error occured" << std::endl;
    }
  auto thirdClass = factory.generateThirdClass(childClass);
  thirdClass->setLocalVariable(5);
  delete thirdClass;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}

int main() //char **argv is atypical I think, so I changed it to something more common
{
  int ret = test();
  // system("leaks technical_challenge");
  return ret;
}

