#include "ParticleMatcherControl.h"

#include <algorithm>

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <controllers/matchers/ScalarParticleMatcher.h>
#include <controllers/matchers/VectorParticleMatcher.h>
#include <controllers/matchers/StringParticleMatcher.h>

ParticleMatcherControl::ParticleMatcherControl(const PropertyTypeMap &properties, QWidget *parent) : QWidget{parent}
{
  // Value controls
  scalarMatcherValueControl = new ScalarMatcherValueControl{this};
  vectorMatcherValueControl = new VectorMatcherValueControl{this};
  stringMatcherValueControl = new StringMatcherValueControl{this};

  // Stacked widget
  stackedValueControls = new QStackedWidget{this};
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
  auto propertyChangeCallback = [=, this](int index)
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
  };
  connect(propertyComboBox, &QComboBox::currentIndexChanged, this, propertyChangeCallback);

  // Use default index if available
  if (propertyValues.size() > 0)
    propertyChangeCallback(0);

  auto layout = new QHBoxLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(propertyComboBox);
  layout->addWidget(stackedValueControls);
  layout->setContentsMargins({});
}

void ParticleMatcherControl::setMatcher(const ParticleMatcher *matcher)
{
  int index = 0;
  if (auto scalarMatcher = dynamic_cast<const AbstractScalarBinaryParticleMatcher *>(matcher))
  {
    scalarMatcherValueControl->setMatcher(scalarMatcher);
    stackedValueControls->setCurrentWidget(scalarMatcherValueControl);

    auto iterator = std::find(propertyValues.begin(), propertyValues.end(), std::make_tuple(scalarMatcher->getPropertyName(), PropertyType::Scalar, VectorComponent{}));
    index = iterator != propertyValues.end() ? std::distance(propertyValues.begin(), iterator) : 0;
  }
  else if (auto vectorMatcher = dynamic_cast<const AbstractVectorBinaryParticleMatcher *>(matcher))
  {
    vectorMatcherValueControl->setMatcher(vectorMatcher);
    stackedValueControls->setCurrentWidget(vectorMatcherValueControl);

    auto iterator = std::find(propertyValues.begin(), propertyValues.end(), std::make_tuple(vectorMatcher->getPropertyName(), PropertyType::Vector, vectorMatcher->getVectorComponent()));
    index = iterator != propertyValues.end() ? std::distance(propertyValues.begin(), iterator) : 0;
  }
  else if (auto stringMatcher = dynamic_cast<const AbstractStringBinaryParticleMatcher *>(matcher))
  {
    stringMatcherValueControl->setMatcher(stringMatcher);
    stackedValueControls->setCurrentWidget(stringMatcherValueControl);

    auto iterator = std::find(propertyValues.begin(), propertyValues.end(), std::make_tuple(stringMatcher->getPropertyName(), PropertyType::String, VectorComponent{}));
    index = iterator != propertyValues.end() ? std::distance(propertyValues.begin(), iterator) : 0;
  }
  propertyComboBox->setCurrentIndex(index);
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
