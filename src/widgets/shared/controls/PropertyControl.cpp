#include "PropertyControl.h"

#include <algorithm>

PropertyControl::PropertyControl(const PropertyTypeMap &properties, QWidget *parent) : PropertyControl{nullptr, properties, parent} {}

PropertyControl::PropertyControl(const char *title, const PropertyTypeMap &properties, QWidget *parent) : PropertyControl{title, QBoxLayout::Direction::Down, properties, parent} {}

PropertyControl::PropertyControl(const char *title, QBoxLayout::Direction direction, const PropertyTypeMap &properties, QWidget *parent) : Control{title, new QComboBox{}, direction, parent}
{
  for (auto &[propertyName, propertyType] : properties)
  {
    switch (propertyType)
    {
    case PropertyType::Scalar:
      // Add items
      values.push_back({propertyName.c_str(), {}});
      // Add values
      widget->addItem(propertyName.c_str());

      break;

    case PropertyType::Vector:
      // Add items
      widget->addItem((propertyName + " (Magnitud)").c_str());
      widget->addItem((propertyName + " (Componente X)").c_str());
      widget->addItem((propertyName + " (Componente Y)").c_str());
      widget->addItem((propertyName + " (Componente Z)").c_str());
      // Add values
      values.push_back({propertyName.c_str(), VectorComponent::Magnitude});
      values.push_back({propertyName.c_str(), VectorComponent::X});
      values.push_back({propertyName.c_str(), VectorComponent::Y});
      values.push_back({propertyName.c_str(), VectorComponent::Z});

      break;
    case PropertyType::String:
      break;
    }
  }
}

QComboBox *PropertyControl::getComboBox() const
{
  return widget;
}

void PropertyControl::setValue(PropertyControlValue value)
{
  auto iterator = std::find(values.begin(), values.end(), value);
  auto index = iterator != values.end() ? std::distance(values.begin(), iterator) : 0;
  widget->setCurrentIndex(index);
}

PropertyControl::PropertyControlValue PropertyControl::getValue() const
{
  return values[widget->currentIndex()];
}

void PropertyControl::onChange(std::function<void(PropertyControlValue)> callback) const
{
  connect(widget, &QComboBox::currentIndexChanged, this, [&, callback]
          { callback(getValue()); });
};