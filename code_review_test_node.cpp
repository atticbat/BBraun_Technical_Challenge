#include <iostream>
#include "test_class.h"
#include <memory>
//<string> needed to define a string type
#include <string>

std::string filename="testfile.txt";

double callback(double first, float second){
  return first/second;
}

//in order to use a child class in this context the parameter must become a base class pointer
void describe(TestClass *t){
	std::cout<< t->to_string() << std::endl;
}

int main(int argc, char **argv)
{
  //argc and argv likely useless, for now just voided
  (void) argc;
  (void) argv;
  try
  {
    //segv on first line
    std::unique_ptr<TestClass> testClass;
    testClass = std::make_unique<TestClass>();
    std::shared_ptr<TestClass> secondClass = testClass->GetSecondClass();
    int result = 0;

    testClass->writeToFile(filename,result);

    //callback function not set
    testClass->setCallbackFunction(callback);
    result = testClass->CallCallbackFunction(2.0,1.0);

    testClass->writeToFile(filename,result);
  std::cout << "works" << std::endl;

    testClass->setCallbackFunction(callback);

    result = testClass->CallCallbackFunction(3.0,1.0);

    testClass->writeToFile(filename, result);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  //DerivedTestClass will attempt to be used in describe, which should take a TestClass pointer to facilitate polymorphism
  // DerivedTestClass derivedClass;
  TestClass *derivedClass = new DerivedTestClass();
  
  // const auto thirdClass = testClass->GetThirdClass();

  //can't set a value in a constant variable
  // thirdClass->SetLocalVariable(5);

  //result was not initialised, meaning that its value could be anything left over from previous memory allocations

  
  try
  {
    describe(derivedClass);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  delete derivedClass;
//  try {
//    testClass->doSomethingElse(-1);
//  } catch ( std::invalid_argument ex){
//    std::cout  << ex.what();
//  } catch (...){
//    std::cout << "error occured";
//  }

  return 0;
}

