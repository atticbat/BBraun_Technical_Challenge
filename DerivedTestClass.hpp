#ifndef DERIVEDTESTCLASS_HPP
#define DERIVEDTESTCLASS_HPP

#include "TestClass.hpp"

template <typename T> class DerivedTestClass : public TestClass<T> {
  // public added to make constructor accessible
public:
  DerivedTestClass();
  ~DerivedTestClass();
  DerivedTestClass(const DerivedTestClass &copy);
  DerivedTestClass &operator=(const DerivedTestClass &copy);
  std::string toString();
};

#include "DerivedTestClass.tpp"

#endif