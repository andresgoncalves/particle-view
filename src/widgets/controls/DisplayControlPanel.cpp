#include "DisplayControlPanel.h"

#include <QtWidgets/QVBoxLayout>

#include "display/DisplayControls.h"
#include "display/DisplayRuleControls.h"

DisplayControlPanel::DisplayControlPanel(AppContext &appContext, QWidget *parent) : appContext{appContext}, QScrollArea{parent}
{
  auto displayControls = new DisplayControls{appContext, this};
  auto displayRuleControls = new DisplayRuleControls{appContext, this};

  auto widget = new QWidget{this};
  setWidget(widget);
  setWidgetResizable(true);

  auto layout = new QVBoxLayout{widget};
  layout->setAlignment(Qt::AlignTop);
  layout->addWidget(displayControls);
  layout->addWidget(displayRuleControls);
  layout->setContentsMargins(0, 8, 0, 8);
}