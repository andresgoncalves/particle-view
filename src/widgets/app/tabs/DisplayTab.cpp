#include "DisplayTab.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/app/display/DisplayPropertyControls.h>

DisplayTab::DisplayTab(AppContext &appContext, QWidget *parent) : appContext{appContext}, QScrollArea{parent}
{
  auto displayPropertyControls = new DisplayPropertyControls{appContext, this};

  auto widget = new QWidget{this};
  setWidget(widget);
  setWidgetResizable(true);

  auto layout = new QVBoxLayout{widget};
  layout->setAlignment(Qt::AlignTop);
  layout->addWidget(displayPropertyControls);
  layout->setContentsMargins(0, 8, 0, 8);
}