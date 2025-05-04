#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "BaseObservable.h"

template <typename T>
class Observable : public BaseObservable<T>
{
public:
  Observable(T &reference);

  void notify();
  T get() const;

private:
  T &reference;
};

template <typename T>
Observable<T>::Observable(T &reference) : reference{reference} {}

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