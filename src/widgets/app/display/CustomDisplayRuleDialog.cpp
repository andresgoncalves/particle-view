#include "CustomDisplayRuleDialog.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

#include <widgets/shared/dialogs/ColorPicker.h>

CustomDisplayRuleDialog::CustomDisplayRuleDialog(AppContext &appContext, QWidget *parent) : CustomDisplayRuleDialog{false, appContext, parent} {}

CustomDisplayRuleDialog::CustomDisplayRuleDialog(const DisplayRule &displayRule, AppContext &appContext, QWidget *parent) : CustomDisplayRuleDialog{true, appContext, parent}
{
  originalDisplayRule = displayRule;
  // nameControl->setValue(displayRule.name);
  // centerControl->setValue(displayRule.center);
  // sizeControl->setValue(displayRule.size);
  // rotationControl->setValue(displayRule.rotation.toEulerAngles());
  // auto shapeIndex = shapeComboBox->findData(static_cast<int>(displayRule.shape));
  // if (shapeIndex >= 0)
  //   shapeComboBox->setCurrentIndex(shapeIndex);
}

CustomDisplayRuleDialog::CustomDisplayRuleDialog(bool edit, AppContext &appContext, QWidget *parent) : QDialog{parent}
{
  setWindowTitle(edit ? "Editar regla" : "Agregar regla");

  particleMatcherControl = new ParticleMatcherControl{appContext.animationController.getStory().metadata.particleProperties, this};

  colorButton = new ColorButton{this};
  connect(colorButton, &QPushButton::clicked,
          [=, this]()
          {
            auto color = ColorPicker::getColor(this);
            if (color.has_value())
            {
              selectedColor = color.value();
              colorButton->setSolidColor(selectedColor);
            }
          });
  auto colorControl = new Control{"Color", colorButton, QBoxLayout::LeftToRight, this};

  auto controlLayout = new QVBoxLayout{};
  controlLayout->addWidget(particleMatcherControl);
  controlLayout->addWidget(colorControl);
  controlLayout->setAlignment(colorControl, Qt::AlignHCenter);
  controlLayout->setContentsMargins(8, 8, 8, 8);

  auto acceptButton = new QPushButton{"Aceptar", this};
  connect(acceptButton, &QPushButton::clicked, this, &QDialog::accept);

  auto cancelButton = new QPushButton{"Cancelar", this};
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

  auto buttonLayout = new QHBoxLayout{};
  buttonLayout->addWidget(acceptButton);
  buttonLayout->addWidget(cancelButton);
  buttonLayout->setContentsMargins(8, 4, 8, 4);

  auto layout = new QVBoxLayout{this};
  layout->addLayout(controlLayout);
  layout->addLayout(buttonLayout);
  layout->setAlignment(buttonLayout, Qt::AlignRight);
  layout->setContentsMargins(0, 4, 0, 4);

  setMinimumWidth(320);
}

DisplayRule CustomDisplayRuleDialog::getDisplayRule() const
{
  auto displayRule = originalDisplayRule.value_or(DisplayRule{});
  displayRule.setMatcher(particleMatcherControl->getMatcher());
  displayRule.setColorStrategy(std::make_shared<SolidColorStrategy>(selectedColor));
  displayRule.setVisible(true);
  return displayRule;
}
