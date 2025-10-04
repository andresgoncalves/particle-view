#include "ParticleMatcherControl.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QStackedWidget>

ParticleMatcherControl::ParticleMatcherControl(const PropertyTypeMap &properties, QWidget *parent) : QWidget{parent}
{
  // Value controls
  scalarMatcherValueControl = new ScalarMatcherValueControl{this};
  vectorMatcherValueControl = new VectorMatcherValueControl{this};
  stringMatcherValueControl = new StringMatcherValueControl{this};

  // Stacked widget
  auto stackedValueControls = new QStackedWidget{this};
  stackedValueControls->addWidget(scalarMatcherValueControl);
  stackedValueControls->addWidget(vectorMatcherValueControl);
  stackedValueControls->addWidget(stringMatcherValueControl);

  // Property control
  propertyComboBox = new QComboBox{this};
  // Add properties
  for (auto [propertyName, propertyType] : properties)
  {
    switch (propertyType)
    {
    case PropertyType::Scalar:
    case PropertyType::String:
      // Add items
      propertyComboBox->addItem(propertyName.c_str());
      // Add values
      propertyValues.push_back({propertyName.c_str(), propertyType, {}});
      break;

    case PropertyType::Vector:
      // Add items
      propertyComboBox->addItem((propertyName + " (Magnitud)").c_str());
      propertyComboBox->addItem((propertyName + " (Componente X)").c_str());
      propertyComboBox->addItem((propertyName + " (Componente Y)").c_str());
      propertyComboBox->addItem((propertyName + " (Componente Z)").c_str());
      // Add values
      propertyValues.push_back({propertyName.c_str(), propertyType, VectorComponent::Magnitude});
      propertyValues.push_back({propertyName.c_str(), propertyType, VectorComponent::X});
      propertyValues.push_back({propertyName.c_str(), propertyType, VectorComponent::Y});
      propertyValues.push_back({propertyName.c_str(), propertyType, VectorComponent::Z});
      break;
    }
  }
  // Change value controls with property type
  connect(propertyComboBox, &QComboBox::currentIndexChanged, this,
          [=, this](int index)
          {
            auto [propertyName, propertyType, vectorComponent] = propertyValues[index];
            switch (propertyType)
            {
            case PropertyType::Scalar:
              stackedValueControls->setCurrentWidget(scalarMatcherValueControl);
              break;
            case PropertyType::Vector:
              stackedValueControls->setCurrentWidget(vectorMatcherValueControl);
              break;
            case PropertyType::String:
              stackedValueControls->setCurrentWidget(stringMatcherValueControl);
              break;
            }
          });

  auto layout = new QHBoxLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(propertyComboBox);
  layout->addWidget(stackedValueControls);
  layout->setContentsMargins({});
}

std::unique_ptr<ParticleMatcher> ParticleMatcherControl::getMatcher() const
{
  auto [propertyName, propertyType, vectorComponent] = propertyValues[propertyComboBox->currentIndex()];
  switch (propertyType)
  {
  case PropertyType::Scalar:
    return scalarMatcherValueControl->getMatcher(propertyName);
  case PropertyType::Vector:
    return vectorMatcherValueControl->getMatcher(propertyName, vectorComponent);
  case PropertyType::String:
    return stringMatcherValueControl->getMatcher(propertyName);
  }
}
