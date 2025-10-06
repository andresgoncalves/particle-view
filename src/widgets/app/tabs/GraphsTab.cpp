#include "GraphsTab.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/app/graphs/GraphControls.h>

GraphsTab::GraphsTab(AppContext &appContext, QWidget *parent) : appContext{appContext}, QScrollArea{parent}
{
  auto graphControls = new GraphControls{appContext, this};

  auto widget = new QWidget{this};
  setWidget(widget);
  setWidgetResizable(true);

  auto layout = new QVBoxLayout{widget};
  layout->setAlignment(Qt::AlignTop);
  layout->addWidget(graphControls);
  layout->setContentsMargins(0, 8, 0, 8);
}