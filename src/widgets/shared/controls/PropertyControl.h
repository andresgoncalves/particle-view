#ifndef PROPERTY_CONTROL_H
#define PROPERTY_CONTROL_H

#include <vector>

#include <QtWidgets/QComboBox>

#include <models/Property.h>

#include "Control.h"

/** Color control with title and a color picker */
class PropertyControl : public Control<QComboBox>
{
public:
  using PropertyControlValue = std::pair<std::string, VectorComponent>;

  /** Creates a vertical control without title */
  PropertyControl(const PropertyTypeMap &properties, QWidget *parent = nullptr);
  /** Creates a vertical control with title */
  PropertyControl(const char *title, const PropertyTypeMap &properties, QWidget *parent = nullptr);
  /** Creates a control with title and given direction */
  PropertyControl(const char *title, QBoxLayout::Direction direction, const PropertyTypeMap &properties, QWidget *parent = nullptr);

  /** Get line edit */
  QComboBox *getComboBox() const;

  /** Set control value */
  void setValue(PropertyControlValue value);

  /** Get control value */
  PropertyControlValue getValue() const;

  /** Add change listener */
  void onChange(std::function<void(PropertyControlValue)> callback) const;

private:
  /** Property combo box values */
  std::vector<PropertyControlValue> values;
};

#endif