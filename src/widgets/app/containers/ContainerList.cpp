#include "ContainerList.h"

#include <QtWidgets/QVBoxLayout>

ContainerList::ContainerList(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  itemLayout = new QVBoxLayout{this};
  itemLayout->setAlignment(Qt::AlignTop);
  itemLayout->setSpacing(0);
  itemLayout->setContentsMargins({});

  build(appContext.containerController.getContainers());

  appContext.containerController.containersObservable.subscribe(
      this,
      [this](ContainerController::Containers &containers)
      {
        clear();
        build(containers);
      });
}

void ContainerList::build(ContainerController::Containers &containers)
{
  for (auto it = containers.begin(); it != containers.end(); it++)
  {
    auto row = new ContainerRow{it, appContext, this};
    rows.push_back(row);
    itemLayout->addWidget(row);
  }
}

void ContainerList::clear()
{
  for (auto row : rows)
  {
    itemLayout->removeWidget(row);
    row->deleteLater();
  }
  rows.clear();
}
