#ifndef DERIVEDTESTCLASS_HPP
#define DERIVEDTESTCLASS_HPP

#include "TestClass.hpp"

// derived class has been separated from its parent class
class DerivedTestClass : public TestClass {
  // public added to make constructor accessible
public:
  // constructors in canonical form
  DerivedTestClass();
  ~DerivedTestClass();
  DerivedTestClass(const DerivedTestClass &copy);
  DerivedTestClass &operator=(const DerivedTestClass &copy);
  const std::string toString() const;
};

#endif