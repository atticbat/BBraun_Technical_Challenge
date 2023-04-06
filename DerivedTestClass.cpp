#include "DerivedTestClass.hpp"
#include <string>

DerivedTestClass::DerivedTestClass() : TestClass() {}
const std::string DerivedTestClass::toString() const {
  return "Derived Test Class";
}
DerivedTestClass::~DerivedTestClass() {}
DerivedTestClass::DerivedTestClass(const DerivedTestClass &copy) {
  *this = copy;
}
DerivedTestClass &DerivedTestClass::operator=(const DerivedTestClass &copy) {
  if (this != &copy) {
    setCallbackFunction(copy.getCallbackFunction());
    setLocalVariable(copy.getLocalVariable());
  }
  return *this;
}