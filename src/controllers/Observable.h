#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <map>
#include <functional>

template <typename T>
class Observable
{
public:
  Observable(T &reference);

  void subscribe(void *const key, const std::function<void(T)> callback);
  void unsubscribe(void *const key);
  void notify();
  void notify(T value);
  T get() const;

private:
  T &reference;

  std::multimap<void *, std::function<void(T value)>> callbacks;
};

template <typename T>
Observable<T>::Observable(T &reference) : reference{reference} {}

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
void Observable<T>::notify()
{
  notify(get());
}

template <typename T>
void Observable<T>::notify(T value)
{
  for (auto [key, callback] : callbacks)
  {
    callback(value);
  }
}

template <typename T>
T Observable<T>::get() const
{
  return reference;
}

#endif