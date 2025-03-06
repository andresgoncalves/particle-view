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

  void subscribe(void *const key, const std::function<void(T)> callback);
  void unsubscribe(void *const key);
  void set(T value);
  T get() const;

  Observable<T> &operator=(T value);

private:
  T value;

  std::map<void *, std::function<void(T value)>> callbacks;
};

template <typename T>
Observable<T>::Observable(T initialValue) : value{initialValue} {}

template <typename T>
void Observable<T>::subscribe(void *key, const std::function<void(T)> callback)
{
  callbacks.insert(std::make_pair(key, callback));
}

template <typename T>
void Observable<T>::unsubscribe(void *key)
{
  callbacks.erase(key);
}

template <typename T>
void Observable<T>::set(T value)
{
  this->value = value;
  for (auto [key, callback] : callbacks)
  {
    callback(value);
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