#include "DisplayRuleRow.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>

#include "DisplayRuleDialog.h"

DisplayRuleRow::DisplayRuleRow(DisplayController::DisplayRules::iterator displayRule, AppContext &appContext, QWidget *parent) : displayRule{displayRule}, QWidget{parent}
{

  auto checkBox = new QCheckBox{this};
  checkBox->setChecked((*displayRule)->isEnabled());
  connect(checkBox, &QCheckBox::checkStateChanged, [=](Qt::CheckState checkState)
          { (*displayRule)->setEnabled(checkState != Qt::Unchecked); });

  auto label = new QLabel{(*displayRule)->getText().c_str(), this};

  auto editButton = new QPushButton{"⋮", this};
  auto editCallback = [=, &appContext, this]
  {
    if (auto binaryDisplayRule = dynamic_cast<AbstractBinaryDisplayRule *>((*displayRule).get()))
    {
      auto displayRuleDialog = new DisplayRuleDialog{*binaryDisplayRule, appContext, this};
      switch (displayRuleDialog->exec())
      {
      case DisplayRuleDialog::DialogResult::Accept:
        appContext.displayController.replaceDisplayRule(displayRule, displayRuleDialog->getDisplayRule());
        checkBox->setChecked((*displayRule)->isEnabled());
        label->setText((*displayRule)->getText().c_str());
        break;
      case DisplayRuleDialog::DialogResult::Delete:
        // displayRule = displayRuleDialog->getDisplayRule();
        // displayRuleGrid->addDisplayRule(displayRule);
        break;
      }
      displayRuleDialog->deleteLater();
    }
  };
  connect(editButton, &QPushButton::clicked, editCallback);

  auto layout = new QGridLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(checkBox, 0, 0);
  layout->addWidget(label, 0, 1);
  layout->addWidget(editButton, 0, 2);
  layout->setContentsMargins({});

  layout->setColumnStretch(0, 0);
  layout->setColumnStretch(1, 1);
  layout->setColumnStretch(2, 0);
  layout->setHorizontalSpacing(16);
}

DisplayRuleRow::~DisplayRuleRow()
{
  (*displayRule)->enabledObservable.unsubscribe(this);
}