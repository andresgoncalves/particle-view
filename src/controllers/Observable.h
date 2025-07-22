#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "BaseObservable.h"

/** Observable template */
template <typename T>
class Observable : public BaseObservable<T>
{
public:
  /** Create an observable for an object */
  Observable(T &reference) : reference{reference} {}

  /** Subscribe to the observable */
  void subscribe(void *const key, const std::function<void(T)> callback, bool init = false);

  /** Notify all subscribers */
  void notify();

  /** Get current value */
  T get() const;

private:
  /** Reference to observed object */
  T &reference;
};

template <typename T>
void Observable<T>::subscribe(void *const key, const std::function<void(T)> callback, bool init)
{
  BaseObservable<T>::subscribe(key, callback);
  if (init)
    callback(get());
}

template <typename T>
void Observable<T>::notify()
{
  BaseObservable<T>::notify(get());
}

template <typename T>
T Observable<T>::get() const
{
  return reference;
}

#endif