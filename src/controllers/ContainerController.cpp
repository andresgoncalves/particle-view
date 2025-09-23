#include "ContainerController.h"

ContainerController::ContainerController()
{
}

const ContainerController::Containers &ContainerController::getContainers() const
{
  return containers;
}

ContainerController::Containers::iterator ContainerController::addContainer(std::shared_ptr<Container> container)
{
  containers.push_back(container);
  containersObservable.notify(containers);
  return std::prev(containers.end());
}

void ContainerController::replaceContainer(Containers::iterator it, std::shared_ptr<Container> container)
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
