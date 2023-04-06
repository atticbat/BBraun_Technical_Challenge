#ifndef CALLBACKFUNCTION_HPP
#define CALLBACKFUNCTION_HPP
#include <functional>

template <typename T> class CallbackFunction {
public:
  CallbackFunction<T>();
  CallbackFunction<T>(T (*callback)(T, T));
  CallbackFunction<T>(const CallbackFunction<T> &copy);
  CallbackFunction<T> &operator=(const CallbackFunction<T> &copy);
  typedef T (*ptr)(T, T);
  T callCallbackFunction(T first, T second);
  ptr getCallbackFunction() const { return _callback_function; };

private:
  T (*_callback_function)(T, T);
};

#include "CallbackFunction.tpp"

#endif