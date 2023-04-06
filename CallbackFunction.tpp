#ifndef CALLBACKFUNCTION_TPP
#define CALLBACKFUNCTION_TPP

#include <exception>
template <typename T>
CallbackFunction<T>::CallbackFunction() : _callback_function(NULL) {}

template <typename T>
CallbackFunction<T>::CallbackFunction(T (*callback)(T, T))
    : _callback_function(callback) {}

template <typename T>
CallbackFunction<T>::CallbackFunction(const CallbackFunction<T> &copy) {
  *this = copy;
}

template <typename T>
CallbackFunction<T> &
CallbackFunction<T>::operator=(const CallbackFunction<T> &copy) {
  if (this != &copy) {
    _callback_function = copy.getCallbackFunction();
  }
  return *this;
}

template <typename T>
T CallbackFunction<T>::callCallbackFunction(T first, T second) {
  if (!_callback_function)
    throw std::exception();
  return _callback_function(first, second);
}

#endif