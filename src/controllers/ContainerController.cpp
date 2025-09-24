#include "ContainerController.h"

ContainerController::ContainerController()
{
}

ContainerController::Containers &ContainerController::getContainers()
{
  return containers;
}

ContainerController::Containers::iterator ContainerController::addContainer(Containers::value_type container)
{
  containers.push_back(container);
  containersObservable.notify(containers);
  return std::prev(containers.end());
}

void ContainerController::replaceContainer(Containers::iterator it, Containers::value_type container)
{
  *it = container;
  containersObservable.notify(containers);
}

void ContainerController::removeContainer(Containers::iterator it)
{
  containers.erase(it);
  containersObservable.notify(containers);
}

void ContainerController::clearContainers()
{
  containers.clear();
  containersObservable.notify(containers);
}
