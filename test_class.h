#ifndef TEST_CLASS_H
# define TEST_CLASS_H
//protected the header file against any other potential header files named test_class.h, relevant only in bigger projects
# include <functional>
//memory is not a local header file, it is stored in the global include directories
# include <memory>
// *yet to see if any of these headers are actually required

class TestClass {

public:
    TestClass();
    //in polymorphic classes the destructor has to be virtual, so to destroy the parent and child upon delete
    virtual ~TestClass();

    double CallCallbackFunction(double first, double second);
    void doSomethingElse(unsigned int first);
    double calculateSum(double first, double second);
    void writeToFile(std::string filename, double value_to_write);
    std::shared_ptr<TestClass> GetSecondClass(){return secondClass;}
    const TestClass * GetThirdClass();
    void setCallbackFunction(std::function<double(double, float)> callback);
    void SetLocalVariable(int local_var){local_variable=local_var;}
	virtual std::string to_string();

    std::function<double(double,float)> callback_function;
    double sum;
    int local_variable;
    std::shared_ptr<TestClass> secondClass;
    TestClass * third_class;
};

class DerivedTestClass : public TestClass{
//public added to make constructor accessible
public:
	DerivedTestClass();
	virtual std::string to_string();
};
#endif