#include "DisplayRuleDialog.h"

#include <QtWidgets/QtWidgets>

#include "../NumericControl.h"

DisplayRuleDialog::DisplayRuleDialog(AppContext &appContext, QWidget *parent) : QDialog{parent}
{
  setWindowTitle("Agregar regla");

  propertyComboBox = new QComboBox{this};

  auto story = appContext.animationController.getStory();
  for (auto property : story.scalarProperties)
    propertyComboBox->addItem(property.c_str(), Particle::PropertyType::Scalar);
  for (auto property : story.vectorProperties)
    propertyComboBox->addItem(property.c_str(), Particle::PropertyType::Vector);

  ruleComboBox = new QComboBox{this};
  ruleComboBox->addItem("=", DisplayRuleItem::Equal);
  ruleComboBox->addItem("≠", DisplayRuleItem::NotEqual);
  ruleComboBox->addItem("<", DisplayRuleItem::Less);
  ruleComboBox->addItem(">", DisplayRuleItem::Greater);
  ruleComboBox->addItem("≤", DisplayRuleItem::LessEqual);
  ruleComboBox->addItem("≥", DisplayRuleItem::GreaterEqual);

  valueControl = new NumericControl{this};

  auto inputLayout = new QHBoxLayout{};
  inputLayout->setAlignment(Qt::AlignHCenter);
  inputLayout->addWidget(propertyComboBox);
  inputLayout->addWidget(ruleComboBox);
  inputLayout->addWidget(valueControl);

  auto addButton = new QPushButton{"Agregar", this};
  connect(addButton, &QPushButton::clicked, this, [=, this]
          { this->accept(); });
  auto cancelButton = new QPushButton{"Cancelar", this};
  connect(cancelButton, &QPushButton::clicked, this, [=, this]
          { this->reject(); });

  auto buttonsLayout = new QHBoxLayout{};
  buttonsLayout->setAlignment(Qt::AlignRight);
  buttonsLayout->addWidget(cancelButton);
  buttonsLayout->addWidget(addButton);

  auto layout = new QVBoxLayout{this};
  layout->addLayout(inputLayout);
  layout->addLayout(buttonsLayout);

  setMinimumWidth(320);
}

std::shared_ptr<DisplayRule> DisplayRuleDialog::getDisplayRule() const
{
  auto value = valueControl->getValue<float>();
  auto property = propertyComboBox->currentText().toStdString();
  auto propertyType = static_cast<Particle::PropertyType>(propertyComboBox->currentData().toInt());
  auto displayRule = static_cast<DisplayRuleItem>(ruleComboBox->currentData().toInt());

  switch (displayRule)
  {
  case Equal:
    return std::make_shared<DisplayRuleEqual>(property, propertyType, value);
  case NotEqual:
    return std::make_shared<DisplayRuleNotEqual>(property, propertyType, value);
  case Less:
    return std::make_shared<DisplayRuleLess>(property, propertyType, value);
  case Greater:
    return std::make_shared<DisplayRuleGreater>(property, propertyType, value);
  case LessEqual:
    return std::make_shared<DisplayRuleLessEqual>(property, propertyType, value);
  case GreaterEqual:
    return std::make_shared<DisplayRuleGreaterEqual>(property, propertyType, value);
  }
}
