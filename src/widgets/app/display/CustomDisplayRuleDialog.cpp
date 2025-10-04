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
  // Matcher control
  particleMatcherControl->setMatcher(displayRule.getMatcher().get());
  // Color control
  selectedColorStrategy = displayRule.getColorStrategy();
  colorButton->setColorStrategy(selectedColorStrategy.get());
  // Visiblity buttons
  if (displayRule.isVisible())
    visibilityTrueButton->setChecked(true);
  else
    visibilityFalseButton->setChecked(true);
}

CustomDisplayRuleDialog::CustomDisplayRuleDialog(bool edit, AppContext &appContext, QWidget *parent) : QDialog{parent}
{
  setWindowTitle(edit ? "Editar regla" : "Agregar regla");

  particleMatcherControl = new ParticleMatcherControl{appContext.animationController.getStory().metadata.particleProperties, this};

  colorButton = new ColorButton{this};
  colorButton->setColorStrategy(selectedColorStrategy.get());
  connect(colorButton, &QPushButton::clicked,
          [=, this]()
          {
            auto color = ColorPicker::getColor(this);
            if (color.has_value())
            {
              selectedColorStrategy = std::make_shared<SolidColorStrategy>(color.value());
              colorButton->setColorStrategy(selectedColorStrategy.get());
            }
          });
  auto colorControl = new Control{"Color", colorButton, QBoxLayout::LeftToRight, this};

  visibilityTrueButton = new QRadioButton{"Mostrar", this};
  visibilityFalseButton = new QRadioButton{"Ocultar", this};
  visibilityTrueButton->setChecked(true);
  connect(visibilityTrueButton, &QRadioButton::toggled,
          [=](bool visible)
          { colorControl->setVisible(visible); });

  auto visibilityLayout = new QHBoxLayout{};
  visibilityLayout->addWidget(visibilityTrueButton);
  visibilityLayout->addWidget(visibilityFalseButton);
  visibilityLayout->setContentsMargins(8, 8, 8, 8);

  auto controlLayout = new QVBoxLayout{};
  controlLayout->addWidget(particleMatcherControl);
  controlLayout->addLayout(visibilityLayout);
  controlLayout->addWidget(colorControl);
  controlLayout->setAlignment(visibilityLayout, Qt::AlignHCenter);
  controlLayout->setAlignment(colorControl, Qt::AlignHCenter);
  controlLayout->addStretch();
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
  displayRule.setColorStrategy(selectedColorStrategy);
  displayRule.setVisible(visibilityTrueButton->isChecked());
  return displayRule;
}
