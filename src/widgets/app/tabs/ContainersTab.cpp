#include "ContainersTab.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/app/containers/ContainerControls.h>

ContainersTab::ContainersTab(AppContext &appContext, QWidget *parent) : appContext{appContext}, QScrollArea{parent}
{
  auto containerControls = new ContainerControls{appContext, this};

  auto widget = new QWidget{this};
  setWidget(widget);
  setWidgetResizable(true);

  auto layout = new QVBoxLayout{widget};
  layout->setAlignment(Qt::AlignTop);
  layout->addWidget(containerControls);
  layout->setContentsMargins(0, 8, 0, 8);
}