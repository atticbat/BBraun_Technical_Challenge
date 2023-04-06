#include "DerivedTestClass.hpp"
#include <string>

template <typename T> DerivedTestClass<T>::DerivedTestClass() : TestClass() {}
template <typename T> std::string DerivedTestClass<T>::toString() {
  return "Derived Test Class";
}
template <typename T> DerivedTestClass<T>::~DerivedTestClass() {}