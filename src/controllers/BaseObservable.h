#ifndef BASE_OBSERVABLE_H
#define BASE_OBSERVABLE_H

#include <map>
#include <functional>

/** Base observable template */
template <typename T>
class BaseObservable
{
public:
  /** Create an observable */
  BaseObservable() {};

  /** Subscribe to the observable */
  void subscribe(void *const key, const std::function<void(T)> callback)
  {
    callbacks.insert(std::make_pair(key, callback));
  }

  /** Unsubscribe from the observable */
  void unsubscribe(void *const key)
  {
    callbacks.erase(key);
  }

  /** Notify all subscribers */
  void notify(T value)
  {
    for (auto [key, callback] : callbacks)
      callback(value);
  }

private:
  std::multimap<void *, std::function<void(T value)>> callbacks;
};

/** Void observable */
template <>
class BaseObservable<void>
{
public:
  /** Create an observable */
  BaseObservable() {};

  /** Subscribe to the observable */
  void subscribe(void *const key, const std::function<void()> callback)
  {
    callbacks.insert(std::make_pair(key, callback));
  }

  /** Unsubscribe from the observable */
  void unsubscribe(void *const key)
  {
    callbacks.erase(key);
  }

  /** Notify all subscribers */
  void notify()
  {
    for (auto [key, callback] : callbacks)
      callback();
  }

private:
  std::multimap<void *, std::function<void()>> callbacks;
};

#endif
