#ifndef DERIVEDTESTCLASS_HPP
# define DERIVEDTESTCLASS_HPP

# include "TestClass.hpp"

class DerivedTestClass : public TestClass{
//public added to make constructor accessible
public:
	DerivedTestClass();
	~DerivedTestClass();
    DerivedTestClass(const DerivedTestClass &copy);
    DerivedTestClass    &operator = (const DerivedTestClass &copy);
	std::string toString();
};


#endif