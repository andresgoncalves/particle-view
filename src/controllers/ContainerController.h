#ifndef CONTAINER_CONTROLLER_H
#define CONTAINER_CONTROLLER_H

#include <list>
#include <memory>

#include <models/Container.h>

#include "Observable.h"

class ContainerController
{
public:
  using Containers = std::list<std::shared_ptr<Container>>;

  ContainerController();

  /** Get containers */
  Containers &getContainers();

  /** Add a container */
  Containers::iterator addContainer(Containers::value_type value);
  /** Replace a container */
  void replaceContainer(Containers::iterator it, Containers::value_type value);
  /** Remove a container */
  void removeContainer(Containers::iterator it);
  /** Clear a container */
  void clearContainers();

  /** Containers observable */
  BaseObservable<Containers &> containersObservable;

private:
  Containers containers;
};

#endif