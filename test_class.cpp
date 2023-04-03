#include <fstream>
#include "test_class.h"
//headers included here were supposed to be <> to indicate that they are in the global include directories and not local
#include <mutex>
#include <exception>
#include <iostream>

TestClass::TestClass(){
    secondClass= std::shared_ptr<TestClass>(new TestClass());
}

TestClass::~TestClass(){

}

double TestClass::CallCallbackFunction(double first, double second){
    return callback_function(first,second);
}

void TestClass::doSomethingElse(unsigned int first)
{
    if(first<0){
        throw std::invalid_argument("value incorrect");
    }
    if(first > 100){
        throw std::out_of_range("value incorrect");
    }
}

double TestClass::calculateSum(double first, double second){
    sum=first+second;
    return sum;
}

void TestClass::writeToFile(std::string filename, double value_to_write){
    static std::mutex file_writer_mutex;

    std::lock_guard<std::mutex> file_writer_lock(file_writer_mutex);

    std::ofstream file(filename);

    if(!file.is_open())
        throw std::runtime_error("file cannot be opened");

    file << value_to_write << std::endl;

}

void TestClass::setCallbackFunction(std::function<double(double,float)> callback){
 callback_function = callback;
}

const TestClass * TestClass::GetThirdClass(){
    third_class = new TestClass();
    return third_class;
}

std::string TestClass::to_string(){
	return "Test class " ;
}

DerivedTestClass::DerivedTestClass(){
    
}

std::string DerivedTestClass::to_string(){
	return "Derived Test Class";
}