#include "CustomDisplayRuleRow.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>

#include <widgets/shared/dialogs/ColorPicker.h>
#include <widgets/shared/buttons/ColorButton.h>

#include "CustomDisplayRuleDialog.h"

CustomDisplayRuleRow::CustomDisplayRuleRow(DisplayController::CustomRules::iterator iterator, AppContext &appContext, QWidget *parent) : QWidget{parent}
{
  auto displayRule = *iterator;

  auto checkBox = new QCheckBox{this};
  checkBox->setChecked(displayRule->isEnabled());
  connect(checkBox, &QCheckBox::checkStateChanged,
          [=, &appContext, this](Qt::CheckState checkState)
          {
            auto newCustomRule = std::make_shared<DisplayRule>(*displayRule);
            newCustomRule->setEnabled(checkState != Qt::Unchecked);
            appContext.displayController.replaceCustomRule(iterator, newCustomRule);
          });

  auto label = new QLabel{displayRule->getMatcher()->getText().c_str()};

  auto colorButton = new ColorButton{this};
  colorButton->setColorStrategy(displayRule->getColorStrategy().get());
  connect(colorButton, &QPushButton::clicked,
          [=, &appContext, this]()
          {
            auto color = ColorPicker::getColor(this);
            if (color.has_value())
            {
              auto newCustomRule = std::make_shared<DisplayRule>(*displayRule);
              newCustomRule->setColorStrategy(std::make_shared<SolidColorStrategy>(color.value()));
              appContext.displayController.replaceCustomRule(iterator, newCustomRule);
            }
          });

  auto actionMenu = new QMenu{this};
  auto editAction = actionMenu->addAction("Editar");
  connect(editAction, &QAction::triggered,
          [=, &appContext, this]()
          {
            auto dialog = new CustomDisplayRuleDialog{*displayRule, appContext, this};
            if (dialog->exec() == QDialog::Accepted)
            {
              auto newCustomRule = std::make_shared<DisplayRule>(dialog->getDisplayRule());
              appContext.displayController.replaceCustomRule(iterator, newCustomRule);
            }
            dialog->deleteLater();
          });
  auto copyAction = actionMenu->addAction("Copiar");
  connect(copyAction, &QAction::triggered,
          [=, &appContext]()
          {
            auto newCustomRule = std::make_shared<DisplayRule>(*displayRule);
            appContext.displayController.addCustomRule(newCustomRule);
          });
  auto deleteAction = actionMenu->addAction("Eliminar");
  connect(deleteAction, &QAction::triggered,
          [=, &appContext]()
          {
            appContext.displayController.removeCustomRule(iterator);
          });

  auto actionsButton = new QPushButton{"⋮", this};
  connect(actionsButton, &QPushButton::clicked,
          [=, this]()
          {
            actionMenu->popup(mapToGlobal(actionsButton->pos() + QPoint{0, actionsButton->height()}));
          });

  auto layout = new QGridLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(checkBox, 0, 0);
  layout->addWidget(label, 0, 1);
  layout->addWidget(colorButton, 0, 2);
  layout->addWidget(actionsButton, 0, 3);
  layout->setContentsMargins({});

  layout->setColumnStretch(0, 0);
  layout->setColumnStretch(1, 1);
  layout->setColumnStretch(2, 0);
  layout->setHorizontalSpacing(16);
}
