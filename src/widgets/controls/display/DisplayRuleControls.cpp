#include "DisplayRuleControls.h"

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

  auto layout = new QVBoxLayout{content};
  layout->addWidget(displayRuleGrid);
  layout->addWidget(addRuleButton);
  layout->setAlignment(addRuleButton, Qt::AlignLeft);
  layout->setContentsMargins({});
}
