#ifndef BASE_OBSERVABLE_H
#define BASE_OBSERVABLE_H

#include <map>
#include <functional>

template <typename T>
class BaseObservable
{
public:
  BaseObservable();

  void subscribe(void *const key, const std::function<void(T)> callback);
  void unsubscribe(void *const key);
  void notify(T value);

private:
  std::multimap<void *, std::function<void(T value)>> callbacks;
};

template <typename T>
BaseObservable<T>::BaseObservable() {}

template <typename T>
void BaseObservable<T>::subscribe(void *key, const std::function<void(T)> callback)
{
  callbacks.insert(std::make_pair(key, callback));
}

template <typename T>
void BaseObservable<T>::unsubscribe(void *key)
{
  callbacks.erase(key);
}

template <typename T>
void BaseObservable<T>::notify(T value)
{
  for (auto [key, callback] : callbacks)
    callback(value);
}

#endif