#include <fstream>
#include "test_class.h"
//headers included here were supposed to be <> to indicate that they are in the global include directories and not local
#include <mutex>
#include <exception>
#include <iostream>

TestClass::TestClass(){
    //this is going infinite btw
    //so here there is a shared_ptr, but it calls on the constructor of TestClass infinitely
    //not sure yet what the purpose of the shared pointer was
    // secondClass = std::shared_ptr<TestClass> (this);
    // secondClass= std::shared_ptr<TestClass>(new TestClass());
}

TestClass::TestClass(const TestClass &copy) {
    *this = copy;
}

TestClass   &TestClass::operator = (const TestClass &copy) {
    if (this != &copy) {
        secondClass = std::shared_ptr<TestClass>(copy.secondClass);
    }
    return *this;
}

TestClass::~TestClass(){

}

double TestClass::CallCallbackFunction(double first, double second){
    return callback_function(first,second);
}

void TestClass::doSomethingElse(unsigned int first)
{
    if(first<0){
        throw InvalidArgumentException();
    }
    if(first > 100){
        throw OutOfRangeException();
    }
}

double TestClass::calculateSum(double first, double second){
    sum=first+second;
    return sum;
}

void TestClass::writeToFile(std::string filename, double value_to_write){
    static std::mutex file_writer_mutex;

    //a mutex must be unlocked after use
    std::lock_guard<std::mutex> file_writer_lock(file_writer_mutex);

    std::ofstream file(filename);

    if(!file.is_open())
        throw RuntimeErrorException();

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

const char  *TestClass::InvalidArgumentException::what() const throw() {
    return ("Exception: Invalid argument passed");
}

const char  *TestClass::OutOfRangeException::what() const throw() {
    return ("Exception: Index out of range");
}

const char  *TestClass::RuntimeErrorException::what() const throw() {
    return ("Exception: Run time error");
}