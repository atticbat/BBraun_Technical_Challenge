#include <fstream>
#include "TestClass.hpp"
//headers included here were supposed to be <> to indicate that they are in the global include directories and not local
#include <mutex>
#include <exception>
#include <iostream>

TestClass::TestClass() : _callback_function(NULL), _local_variable(0) {}
TestClass::TestClass(const TestClass &copy) { *this = copy; }
TestClass   &TestClass::operator = (const TestClass &copy) {
    if (this != &copy) {
        setCallbackFunction(copy.getCallbackFunction());
        setLocalVariable(copy.getLocalVariable());
    }
    return *this;
}
TestClass::~TestClass() {}
double TestClass::callCallbackFunction(double first, double second) {
    if (!_callback_function)
        throw MissingFunctionException();
    checkInputValidity(first);
    return _callback_function(first,second);
}
//value being passed here from main is a negative number, so I've changed the parameter to suit negative inputs
void TestClass::checkInputValidity(int first)
{
    if(first < 0){
        throw std::invalid_argument("Invalid argument passed");
    }
    if(first > 100){
        throw std::out_of_range("Number out of range");
    }
}
void TestClass::writeToFile(std::string filename, double value_to_write){
    //there is no need to lock the mutex, since we are not using multiple threads in this program
    //there won't be any data races with one thread
    std::ofstream file(filename, std::ios::app); //writeToFile now appends
    if(!file.is_open()) //in case the permissions to an already existing testfile.txt are disallowing editing
        throw std::runtime_error("Unable to open file");
    file << value_to_write << std::endl;
    file.close();
    if(file.is_open())
        throw std::runtime_error("Unable to close file");
}
void TestClass::setCallbackFunction(std::function<double(double,double)> callback) { _callback_function = callback; }
std::function<double(double,double)> TestClass::getCallbackFunction() const { return _callback_function; }
void TestClass::setLocalVariable(int local_var) { _local_variable=local_var; }
int TestClass::getLocalVariable() const { return _local_variable; }
std::string TestClass::to_string() { return "Test class"; }
const char  *TestClass::MissingFunctionException::what() const throw() { return ("Exception: Function missing"); }
