#include "DerivedTestClass.hpp"
#include <string>

DerivedTestClass::DerivedTestClass() : TestClass() {}
std::string DerivedTestClass::toString() { return "Derived Test Class"; }
DerivedTestClass::~DerivedTestClass() {}