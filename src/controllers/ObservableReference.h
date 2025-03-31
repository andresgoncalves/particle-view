#ifndef OBSERVABLE_REFERENCE_H
#define OBSERVABLE_REFERENCE_H

#include <map>
#include <functional>

template <typename T>
class ObservableReference
{
public:
  ObservableReference(T &reference);

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
ObservableReference<T>::ObservableReference(T &reference) : reference{reference} {}

template <typename T>
void ObservableReference<T>::subscribe(void *key, const std::function<void(T)> callback)
{
  callbacks.insert(std::make_pair(key, callback));
}

template <typename T>
void ObservableReference<T>::unsubscribe(void *key)
{
  callbacks.erase(key);
}

template <typename T>
void ObservableReference<T>::notify()
{
  notify(get());
}

template <typename T>
void ObservableReference<T>::notify(T value)
{
  for (auto [key, callback] : callbacks)
  {
    callback(value);
  }
}

template <typename T>
T ObservableReference<T>::get() const
{
  return reference;
}

#endif