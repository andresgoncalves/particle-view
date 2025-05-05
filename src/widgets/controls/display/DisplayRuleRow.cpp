#include "DisplayRuleRow.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>

DisplayRuleRow::DisplayRuleRow(std::shared_ptr<DisplayRule> displayRule, QWidget *parent) : displayRule{displayRule}, QWidget{parent}
{
  auto checkBox = new QCheckBox{this};
  checkBox->setChecked(displayRule->isEnabled());
  connect(checkBox, &QCheckBox::checkStateChanged, [=](Qt::CheckState checkState)
          { displayRule->setEnabled(checkState != Qt::Unchecked); });

  auto label = new QLabel{displayRule->getText().c_str(), this};

  auto editButton = new QPushButton{"⋮", this};
  connect(editButton, &QPushButton::clicked, [=]
          {
            // if(dialog.exec()) {
            // displayRule = dialog.getDisplayRule();
            // checkBox->setChecked(displayRule->isEnabled());
            // label->setText(displayRule->getText().c_str())
            // }
          });

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

  auto enabledCallback = [=](bool enabled)
  {
    checkBox->setChecked(enabled);
  };
  displayRule->enabledObservable.subscribe(this, enabledCallback);
}

DisplayRuleRow::~DisplayRuleRow()
{
  displayRule->enabledObservable.unsubscribe(this);
}