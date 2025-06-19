#include "DisplayColorRuleDialog.h"

#include <QtWidgets/QtWidgets>

#include "../NumericControl.h"

DisplayColorRuleDialog::DisplayColorRuleDialog(AppContext &appContext, QWidget *parent)
    : DisplayColorRuleDialog{false, appContext, parent} {}

DisplayColorRuleDialog::DisplayColorRuleDialog(std::shared_ptr<ColorRule> colorRule, AppContext &appContext, QWidget *parent) : DisplayColorRuleDialog{true, appContext, parent}
{
  if (auto gradientColorRule = dynamic_cast<GradientColorRule *>(colorRule.get()))
  {
    propertyComboBox->setCurrentText(gradientColorRule->getProperty().c_str());
    startValueControl->setValue(gradientColorRule->getStartValue());
    endValueControl->setValue(gradientColorRule->getEndValue());
    startColorTextField->setText(gradientColorRule->getStartColor().name());
    endColorTextField->setText(gradientColorRule->getEndColor().name());
  }
}

DisplayColorRuleDialog::DisplayColorRuleDialog(bool edit, AppContext &appContext, QWidget *parent) : QDialog{parent}
{
  setWindowTitle(edit ? "Editar regla" : "Agregar regla");

  propertyComboBox = new QComboBox{this};

  auto story = appContext.animationController.getStory();
  for (auto property : story.scalarProperties)
    propertyComboBox->addItem(property.c_str(), Particle::PropertyType::Scalar);
  for (auto property : story.vectorProperties)
    propertyComboBox->addItem(property.c_str(), Particle::PropertyType::Vector);

  startValueControl = new NumericControl{this};
  endValueControl = new NumericControl{this};

  auto colorButtonCallback = [=, this](QLineEdit *colorTextField)
  {
    auto color = QColor{colorTextField->text()};
    auto colorDialog = new QColorDialog{color, this};
    colorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    if (colorDialog->exec() == QDialog::Accepted)
    {
      colorTextField->setText(colorDialog->currentColor().name());
    }
    colorDialog->deleteLater();
  };

  startColorTextField = new QLineEdit{this};
  auto startColorLabel = new QLabel{"Inicio", this};
  auto startColorButton = new QPushButton{"Seleccionar", this};
  connect(startColorButton, &QPushButton::clicked, this, [=]
          { colorButtonCallback(startColorTextField); });

  auto startColorLayout = new QHBoxLayout{};
  startColorLayout->setAlignment(Qt::AlignVCenter);
  startColorLayout->addWidget(startColorLabel);
  startColorLayout->addWidget(startColorTextField);
  startColorLayout->addWidget(startColorButton);

  endColorTextField = new QLineEdit{this};
  auto endColorLabel = new QLabel{"Fin", this};
  auto endColorButton = new QPushButton{"Seleccionar", this};
  connect(endColorButton, &QPushButton::clicked, this, [=]
          { colorButtonCallback(endColorTextField); });

  auto endColorLayout = new QHBoxLayout{};
  endColorLayout->setAlignment(Qt::AlignVCenter);
  endColorLayout->addWidget(endColorLabel);
  endColorLayout->addWidget(endColorTextField);
  endColorLayout->addWidget(endColorButton);

  auto buttonsLayout = new QHBoxLayout{};
  buttonsLayout->setAlignment(Qt::AlignRight);

  auto addButton = new QPushButton{"Guardar", this};
  connect(addButton, &QPushButton::clicked, this, [=, this]
          { this->done(QDialog::Accepted); });
  buttonsLayout->addWidget(addButton);

  auto cancelButton = new QPushButton{"Cancelar", this};
  connect(cancelButton, &QPushButton::clicked, this, [=, this]
          { this->done(QDialog::Rejected); });
  buttonsLayout->addWidget(cancelButton);

  auto layout = new QVBoxLayout{this};
  layout->addLayout(startColorLayout);
  layout->addLayout(endColorLayout);
  layout->addLayout(buttonsLayout);

  setMinimumWidth(320);
}

std::shared_ptr<ColorRule> DisplayColorRuleDialog::getColorRule() const
{
  auto property = propertyComboBox->currentText().toStdString();
  auto propertyType = static_cast<Particle::PropertyType>(propertyComboBox->currentData().toInt());
  auto startValue = startValueControl->getValue<float>();
  auto endValue = endValueControl->getValue<float>();
  auto startColor = QColor{startColorTextField->text()};
  auto endColor = QColor{endColorTextField->text()};

  auto colorRule = std::make_shared<GradientColorRule>(property, propertyType, startValue, endValue, startColor, endColor);

  return colorRule;
}
