#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <algorithm>
#include <map>
#include <functional>

template <typename T>
class Observable
{
public:
  Observable(T initialValue);

  void subscribe(const std::function<void(T)> cb);
  void unsubscribe(const std::function<void(T)> cb);
  void set(T value);
  T get() const;

  Observable<T> &operator=(T value);

private:
  T value;

  std::vector<std::function<void(T value)>> callbacks;
};

template <typename T>
Observable<T>::Observable(T initialValue) : value{initialValue} {}

template <typename T>
void Observable<T>::subscribe(const std::function<void(T)> cb)
{
  callbacks.push_back(cb);
}

template <typename T>
void Observable<T>::unsubscribe(const std::function<void(T)> cb)
{
  // std::erase(callbacks, cb);
}

template <typename T>
void Observable<T>::set(T value)
{
  this->value = value;
  for (auto cb : callbacks)
  {
    cb(value);
  }
}

template <typename T>
T Observable<T>::get() const
{
  return value;
}

template <typename T>
Observable<T> &Observable<T>::operator=(T value)
{
  set(value);
  return *this;
}

#endif