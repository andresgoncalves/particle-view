#include "DisplayRuleDialog.h"

#include <QtWidgets/QtWidgets>

#include "../NumericControl.h"

DisplayRuleDialog::DisplayRuleDialog(AppContext &appContext, QWidget *parent)
    : DisplayRuleDialog{false, appContext, parent} {}

DisplayRuleDialog::DisplayRuleDialog(AbstractBinaryDisplayRule &displayRule, AppContext &appContext, QWidget *parent) : DisplayRuleDialog{true, appContext, parent}
{
  propertyComboBox->setCurrentText(displayRule.getProperty().c_str());
  ruleComboBox->setCurrentText(displayRule.getSymbol().c_str());
  valueControl->setValue(displayRule.getCompareValue());
}

DisplayRuleDialog::DisplayRuleDialog(bool edit, AppContext &appContext, QWidget *parent) : QDialog{parent}
{
  setWindowTitle(edit ? "Editar regla" : "Agregar regla");

  propertyComboBox = new QComboBox{this};

  auto story = appContext.animationController.getStory();
  for (auto property : story.scalarProperties)
    propertyComboBox->addItem(property.c_str(), Particle::PropertyType::Scalar);
  for (auto property : story.vectorProperties)
    propertyComboBox->addItem(property.c_str(), Particle::PropertyType::Vector);

  ruleComboBox = new QComboBox{this};
  ruleComboBox->addItem("=", DisplayRuleType::Equal);
  ruleComboBox->addItem("≠", DisplayRuleType::NotEqual);
  ruleComboBox->addItem("<", DisplayRuleType::Less);
  ruleComboBox->addItem(">", DisplayRuleType::Greater);
  ruleComboBox->addItem("≤", DisplayRuleType::LessEqual);
  ruleComboBox->addItem("≥", DisplayRuleType::GreaterEqual);

  valueControl = new NumericControl{this};

  auto inputLayout = new QHBoxLayout{};
  inputLayout->setAlignment(Qt::AlignHCenter);
  inputLayout->addWidget(propertyComboBox);
  inputLayout->addWidget(ruleComboBox);
  inputLayout->addWidget(valueControl);

  auto buttonsLayout = new QHBoxLayout{};
  buttonsLayout->setAlignment(Qt::AlignRight);

  auto addButton = new QPushButton{"Guardar", this};
  connect(addButton, &QPushButton::clicked, this, [=, this]
          { this->done(DialogResult::Accept); });
  buttonsLayout->addWidget(addButton);

  if (edit)
  {
    auto deleteButton = new QPushButton{"Borrar", this};
    connect(deleteButton, &QPushButton::clicked, this, [=, this]
            { this->done(DialogResult::Delete); });
    buttonsLayout->addWidget(deleteButton);
  }

  auto cancelButton = new QPushButton{"Cancelar", this};
  connect(cancelButton, &QPushButton::clicked, this, [=, this]
          { this->done(DialogResult::Cancel); });
  buttonsLayout->addWidget(cancelButton);

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
  auto displayRule = static_cast<DisplayRuleType>(ruleComboBox->currentData().toInt());

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
