#include "GradientColorControl.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/dialogs/ColorPicker.h>
#include <utils/color/GradientColorStrategy.h>

GradientColorControl::GradientColorControl(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  // Property control
  propertyComboBox = new QComboBox{this};
  // Add scalar properties
  for (auto property : appContext.animationController.getStory().scalarProperties)
    propertyComboBox->addItem(property.c_str(), Particle::PropertyType::Scalar);
  // Add vector properties
  for (auto property : appContext.animationController.getStory().vectorProperties)
    propertyComboBox->addItem(property.c_str(), Particle::PropertyType::Vector);
  auto propertyControl = new Control<QComboBox>{"Propiedad", propertyComboBox, this};

  // Start value control
  startValueControl = new NumericControl{"Valor", QBoxLayout::Direction::LeftToRight, this};

  // Start color control
  startColorControl = new ColorControl{"Color", false, this};
  connect(startColorControl->getColorButton(), &ColorButton::clicked, this,
          [this]
          {
            auto pickedColor = ColorPicker::getColor(startColor, this);
            if (pickedColor.has_value())
            {
              startColor = pickedColor.value();
              startColorControl->getColorButton()->setSolidColor(startColor);
            }
          });

  // End value control
  endValueControl = new NumericControl{"Valor", QBoxLayout::Direction::LeftToRight, this};

  // End color control
  endColorControl = new ColorControl{"Color", false, this};
  connect(endColorControl->getColorButton(), &ColorButton::clicked, this,
          [this]
          {
            auto pickedColor = ColorPicker::getColor(endColor, this);
            if (pickedColor.has_value())
            {
              endColor = pickedColor.value();
              endColorControl->getColorButton()->setSolidColor(endColor);
            }
          });

  // Start section
  auto startSection = new Section{"Mínimo de escala", this};
  auto startLayout = new QVBoxLayout{startSection->getContent()};
  startLayout->addWidget(startValueControl);
  startLayout->addWidget(startColorControl);
  startLayout->setContentsMargins({});
  // End section
  auto endSection = new Section{"Máximo de escala", this};
  auto endLayout = new QVBoxLayout{endSection->getContent()};
  endLayout->addWidget(endValueControl);
  endLayout->addWidget(endColorControl);
  endLayout->setContentsMargins({});

  // Build layout
  auto layout = new QVBoxLayout{this};
  layout->addWidget(propertyControl);
  layout->addWidget(startSection);
  layout->addWidget(endSection);
  layout->setAlignment(Qt::AlignTop);
  layout->setContentsMargins({});
}

void GradientColorControl::setColorStrategy(GradientColorStrategy *colorStrategy)
{
  // Set property controls
  propertyComboBox->setCurrentText(colorStrategy->getProperty().c_str());

  // Set start controls
  startColor = colorStrategy->getStart().second;
  startValueControl->setValue(colorStrategy->getStart().first);
  startColorControl->getColorButton()->setSolidColor(startColor);

  // Set end controls
  endColor = colorStrategy->getEnd().second;
  endValueControl->setValue(colorStrategy->getEnd().first);
  endColorControl->getColorButton()->setSolidColor(endColor);
}

std::shared_ptr<GradientColorStrategy> GradientColorControl::getColorStrategy() const
{
  return std::make_shared<GradientColorStrategy>(
      propertyComboBox->currentText().toStdString(),
      (Particle::PropertyType)propertyComboBox->currentData().toInt(),
      std::make_pair(startValueControl->getValue<float>(), startColor),
      std::make_pair(endValueControl->getValue<float>(), endColor));
}
