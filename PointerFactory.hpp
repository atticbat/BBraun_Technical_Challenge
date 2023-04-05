#ifndef ATESTCLASS_HPP
#define ATESTCLASS_HPP

#include <memory>

class TestClass;

enum ClassType { baseClass, childClass };

class PointerFactory {
public:
  PointerFactory();
  ~PointerFactory();
  std::unique_ptr<TestClass> generateFirstClass(ClassType type);
  std::shared_ptr<TestClass> generateSecondClass(ClassType type);
  TestClass *generateThirdClass(ClassType type);
};

#endif