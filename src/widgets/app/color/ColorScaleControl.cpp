#include "ColorScaleControl.h"

#include <algorithm>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/dialogs/ColorPicker.h>
#include <utils/color/ColorScaleStrategy.h>

ColorScaleControl::ColorScaleControl(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  // Property control
  propertyComboBox = new QComboBox{this};
  // Add properties
  for (auto [propertyName, propertyType] : appContext.animationController.getStory().particleProperties)
  {
    switch (propertyType)
    {
    case PropertyType::Scalar:
      // Add items
      propertyValues.push_back({propertyName.c_str(), {}});
      // Add values
      propertyComboBox->addItem(propertyName.c_str());

      break;

    case PropertyType::Vector:
      // Add items
      propertyComboBox->addItem((propertyName + " (Magnitud)").c_str());
      propertyComboBox->addItem((propertyName + " (Componente X)").c_str());
      propertyComboBox->addItem((propertyName + " (Componente Y)").c_str());
      propertyComboBox->addItem((propertyName + " (Componente Z)").c_str());
      // Add values
      propertyValues.push_back({propertyName.c_str(), VectorComponent::Magnitude});
      propertyValues.push_back({propertyName.c_str(), VectorComponent::X});
      propertyValues.push_back({propertyName.c_str(), VectorComponent::Y});
      propertyValues.push_back({propertyName.c_str(), VectorComponent::Z});

      break;
    case PropertyType::String:
      break;
    }
  }
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

void ColorScaleControl::setColorStrategy(ColorScaleStrategy *colorStrategy)
{
  // Set property controls
  auto search = [colorStrategy](std::pair<std::string, VectorComponent> item)
  {
    return item.first == colorStrategy->getProperty() &&
           item.second == colorStrategy->getVectorComponent();
  };
  auto iterator = std::find_if(propertyValues.begin(), propertyValues.end(), search);
  auto index = iterator != propertyValues.end() ? std::distance(propertyValues.begin(), iterator) : 0;
  propertyComboBox->setCurrentIndex(index);

  // Set start controls
  startColor = colorStrategy->getStart().second;
  startValueControl->setValue(colorStrategy->getStart().first);
  startColorControl->getColorButton()->setSolidColor(startColor);

  // Set end controls
  endColor = colorStrategy->getEnd().second;
  endValueControl->setValue(colorStrategy->getEnd().first);
  endColorControl->getColorButton()->setSolidColor(endColor);
}

std::shared_ptr<ColorScaleStrategy> ColorScaleControl::getColorStrategy() const
{
  auto [propertyName, vectorComponent] = propertyValues[propertyComboBox->currentIndex()];
  return std::make_shared<ColorScaleStrategy>(
      propertyName,
      std::make_pair(startValueControl->getValue<float>(), startColor),
      std::make_pair(endValueControl->getValue<float>(), endColor),
      vectorComponent);
}
