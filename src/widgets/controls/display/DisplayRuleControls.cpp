#include "DisplayRuleControls.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QCheckBox>

#include "DisplayRuleGrid.h"

DisplayRuleControls::DisplayRuleControls(AppContext &appContext, QWidget *parent) : ControlSection{"Reglas", parent}
{
  auto displayRuleGrid = new DisplayRuleGrid{appContext, this};

  auto layout = new QVBoxLayout{content};
  layout->addWidget(displayRuleGrid);
  layout->setContentsMargins({});
}
