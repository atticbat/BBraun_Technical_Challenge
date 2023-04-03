#include <iostream>
#include "test_class.h"
#include <memory>

std::string filename="testfile.txt";

double callback(double first, float second){
  return first/second;
}

void describe(TestClass t){
	std::cout<< t.to_string() << std::endl;
}

int main(int argc, char **argv)
{
  std::unique_ptr<TestClass> testClass = std::make_unique<TestClass>();

  std::shared_ptr<TestClass> secondClass = testClass->GetSecondClass();
  
  DerivedTestClass derivedClass;
  
  const auto thirdClass = testClass->GetThirdClass();

  thirdClass->SetLocalVariable(5);

  int result;

  testClass->writeToFile(filename,result);

  result = testClass->CallCallbackFunction(2.0,1.0);

  testClass->writeToFile(filename,result);

  testClass->setCallbackFunction(callback);

  result = testClass->CallCallbackFunction(3.0,1.0);

  testClass->writeToFile(filename, result);
  
  describe(derivedClass);

  try {
    testClass->doSomethingElse(-1);
  } catch ( std::invalid_argument ex){
    std::cout  << ex.what();
  } catch (...){
    std::cout << "error occured";
  }

  return 0;
}

