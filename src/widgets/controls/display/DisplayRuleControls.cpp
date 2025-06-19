#include "DisplayRuleControls.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include "DisplayRuleGrid.h"
#include "DisplayRuleDialog.h"

DisplayRuleControls::DisplayRuleControls(AppContext &appContext, QWidget *parent) : ControlSection{"Reglas", parent}
{
  auto displayRuleGrid = new DisplayRuleGrid{appContext, this};

  auto addRuleButton = new QPushButton{"Agregar regla", this};
  auto addRuleCallback = [&, displayRuleGrid]()
  {
    auto displayRuleDialog = new DisplayRuleDialog{appContext, this};
    if (displayRuleDialog->exec() == QDialog::Accepted)
    {
      auto it = appContext.displayController.addDisplayRule(displayRuleDialog->getDisplayRule());
      displayRuleGrid->addRow(it);
    }
    displayRuleDialog->deleteLater();
  };
  connect(addRuleButton, &QPushButton::clicked, this, addRuleCallback);

  auto clearRulesButton = new QPushButton{"Limpiar reglas", this};
  auto clearRulesCallback = [&, displayRuleGrid]()
  {
    displayRuleGrid->clear();
    appContext.displayController.clearDisplayRules();
  };
  connect(clearRulesButton, &QPushButton::clicked, this, clearRulesCallback);

  auto buttonLayout = new QHBoxLayout{};
  buttonLayout->addWidget(addRuleButton);
  buttonLayout->addWidget(clearRulesButton);

  auto layout = new QVBoxLayout{content};
  layout->addWidget(displayRuleGrid);
  layout->addLayout(buttonLayout);
  layout->setAlignment(buttonLayout, Qt::AlignLeft);
  layout->setContentsMargins({});
}
