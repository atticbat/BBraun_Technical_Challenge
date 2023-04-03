#include <functional>
#include "memory"

class TestClass {

public:
    TestClass();
    ~TestClass();

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
	DerivedTestClass();
	virtual std::string to_string();
}
