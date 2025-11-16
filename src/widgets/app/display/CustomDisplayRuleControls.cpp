#include "CustomDisplayRuleControls.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>

#include "CustomDisplayRuleList.h"
#include "CustomDisplayRuleDialog.h"

CustomDisplayRuleControls::CustomDisplayRuleControls(AppContext &appContext, QWidget *parent) : Section{"Reglas", parent}
{
  auto containerList = new CustomDisplayRuleList{appContext, this};

  auto addButton = new QPushButton{"Agregar", this};
  auto addCallback = [=, &appContext, this]()
  {
    // Check that particles have defined properties
    if (appContext.animationController.getStory().metadata.particleProperties.empty())
    {
      QMessageBox{QMessageBox::Icon::NoIcon, "Error", "No hay propiedades para mostrar"}.exec();
      return;
    }

    auto dialog = new CustomDisplayRuleDialog{appContext, this};
    if (dialog->exec() == QDialog::Accepted)
    {
      auto newCustomRule = std::make_shared<DisplayRule>(dialog->getDisplayRule());
      appContext.displayController.addCustomRule(newCustomRule);
    }
    dialog->deleteLater();
  };
  connect(addButton, &QPushButton::clicked, this, addCallback);

  auto clearButton = new QPushButton{"Limpiar", this};
  connect(clearButton, &QPushButton::clicked, this,
          [&appContext]()
          { appContext.displayController.clearCustomRules(); });

  auto buttonLayout = new QHBoxLayout{};
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(clearButton);

  auto layout = new QVBoxLayout{content};
  layout->addWidget(containerList);
  layout->addLayout(buttonLayout);
  layout->setAlignment(buttonLayout, Qt::AlignRight);
  layout->setContentsMargins({});
}
