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
  colorTextField->setText(displayRule.getColor().name());
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

  auto ruleLayout = new QHBoxLayout{};
  ruleLayout->setAlignment(Qt::AlignVCenter);
  ruleLayout->addWidget(propertyComboBox);
  ruleLayout->addWidget(ruleComboBox);
  ruleLayout->addWidget(valueControl);

  colorTextField = new QLineEdit{this};
  auto colorLabel = new QLabel{"Color", this};
  auto colorButton = new QPushButton{"Seleccionar", this};
  auto colorButtonCallback = [=, this]
  {
    auto color = QColor{colorTextField->text()};
    auto colorDialog = new QColorDialog{color, this};
    if (colorDialog->exec() == QDialog::Accepted)
    {
      colorTextField->setText(colorDialog->currentColor().name());
    }
    colorDialog->deleteLater();
  };
  connect(colorButton, &QPushButton::clicked, this, colorButtonCallback);

  auto colorLayout = new QHBoxLayout{};
  colorLayout->setAlignment(Qt::AlignVCenter);
  colorLayout->addWidget(colorLabel);
  colorLayout->addWidget(colorTextField);
  colorLayout->addWidget(colorButton);

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
  layout->addLayout(ruleLayout);
  layout->addLayout(colorLayout);
  layout->addLayout(buttonsLayout);

  setMinimumWidth(320);
}

std::shared_ptr<DisplayRule> DisplayRuleDialog::getDisplayRule() const
{
  auto value = valueControl->getValue<float>();
  auto property = propertyComboBox->currentText().toStdString();
  auto propertyType = static_cast<Particle::PropertyType>(propertyComboBox->currentData().toInt());
  auto ruleType = static_cast<DisplayRuleType>(ruleComboBox->currentData().toInt());

  auto displayRule = std::shared_ptr<DisplayRule>{};
  switch (ruleType)
  {
  case Equal:
    displayRule = std::make_shared<DisplayRuleEqual>(property, propertyType, value);
    break;
  case NotEqual:
    displayRule = std::make_shared<DisplayRuleNotEqual>(property, propertyType, value);
    break;
  case Less:
    displayRule = std::make_shared<DisplayRuleLess>(property, propertyType, value);
    break;
  case Greater:
    displayRule = std::make_shared<DisplayRuleGreater>(property, propertyType, value);
    break;
  case LessEqual:
    displayRule = std::make_shared<DisplayRuleLessEqual>(property, propertyType, value);
    break;
  case GreaterEqual:
    displayRule = std::make_shared<DisplayRuleGreaterEqual>(property, propertyType, value);
    break;
  }

  displayRule->setColor(colorTextField->text());

  return displayRule;
}
