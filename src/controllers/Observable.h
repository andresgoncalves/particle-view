#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "BaseObservable.h"

template <typename T>
class Observable : public BaseObservable<T>
{
public:
  Observable(T &reference) : reference{reference} {}

  void notify()
  {
    BaseObservable<T>::notify(get());
  }

  T get() const
  {
    return reference;
  }

private:
  T &reference;
};

#endif