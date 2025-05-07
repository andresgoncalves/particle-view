#include "DisplayRuleRow.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>

DisplayRuleRow::DisplayRuleRow(std::shared_ptr<DisplayRule> displayRule, AppContext &appContext, QWidget *parent) : displayRule{displayRule}, QWidget{parent}
{
  checkBox = new QCheckBox{this};
  checkBox->setChecked(displayRule->isEnabled());
  connect(checkBox, &QCheckBox::checkStateChanged, [this](Qt::CheckState checkState)
          { this->displayRule->setEnabled(checkState != Qt::Unchecked); });

  label = new QLabel{displayRule->getText().c_str(), this};

  editButton = new QPushButton{"⋮", this};

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
  displayRule->enabledObservable.unsubscribe(this);
}

void DisplayRuleRow::setDisplayRule(std::shared_ptr<DisplayRule> displayRule)
{
  this->displayRule = displayRule;
  checkBox->setChecked(displayRule->isEnabled());
  label->setText(displayRule->getText().c_str());
}

void DisplayRuleRow::onEdit(std::function<void()> editCallback) const
{
  connect(editButton, &QPushButton::clicked, editCallback);
};