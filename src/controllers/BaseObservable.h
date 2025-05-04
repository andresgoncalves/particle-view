#ifndef BASE_OBSERVABLE_H
#define BASE_OBSERVABLE_H

#include <map>
#include <functional>

template <typename T>
class BaseObservable
{
public:
  BaseObservable() {};

  void subscribe(void *const key, const std::function<void(T)> callback)
  {
    callbacks.insert(std::make_pair(key, callback));
  }

  void unsubscribe(void *const key)
  {
    callbacks.erase(key);
  }

  void notify(T value)
  {
    for (auto [key, callback] : callbacks)
      callback(value);
  }

private:
  std::multimap<void *, std::function<void(T value)>> callbacks;
};

template <>
class BaseObservable<void>
{
public:
  BaseObservable() {};

  void subscribe(void *const key, const std::function<void()> callback)
  {
    callbacks.insert(std::make_pair(key, callback));
  }

  void unsubscribe(void *const key)
  {
    callbacks.erase(key);
  }

  void notify()
  {
    for (auto [key, callback] : callbacks)
      callback();
  }

private:
  std::multimap<void *, std::function<void()>> callbacks;
};

#endif