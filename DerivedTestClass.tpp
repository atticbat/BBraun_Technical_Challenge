#ifndef DERIVEDTESTCLASS_TPP
#define DERIVEDTESTCLASS_TPP

#include <string>

template <typename T>
DerivedTestClass<T>::DerivedTestClass() : TestClass<T>() {}
template <typename T> std::string DerivedTestClass<T>::toString() {
  return "Derived Test Class";
}
template <typename T> DerivedTestClass<T>::~DerivedTestClass() {}

#endif