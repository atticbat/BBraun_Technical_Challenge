#include "PointerFactory.hpp"
#include "DerivedTestClass.hpp"

PointerFactory::PointerFactory() {}

PointerFactory::~PointerFactory() {}

std::unique_ptr<TestClass> PointerFactory::generateFirstClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (std::unique_ptr<TestClass>(new TestClass));
  case childClass:
    return (std::unique_ptr<DerivedTestClass>(new DerivedTestClass));
  default:
    return NULL;
  }
}
std::shared_ptr<TestClass> PointerFactory::generateSecondClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (std::shared_ptr<TestClass>(new TestClass()));
  case childClass:
    return (std::shared_ptr<DerivedTestClass>(new DerivedTestClass()));
  default:
    return NULL;
  }
}
TestClass *PointerFactory::generateThirdClass(ClassType type) {
  switch (type) {
  case baseClass:
    return (new TestClass());
  case childClass:
    return (new DerivedTestClass());
  default:
    return NULL;
  }
}