#ifndef PARTICLE_H
#define PARTICLE_H

#include <QtGui/QVector3D>

#include "Property.h"

struct Particle
{
  inline static const std::string RADIUS_PROPERTY = "Radio";
  inline static const std::string POSITION_PROPERTY = "Posición";

  float getRadius() const
  {
    auto it = properties.find(RADIUS_PROPERTY);
    if (it != properties.end())
    {
      auto property = it->second.getValue<PropertyType::Scalar>();
      if (property != nullptr)
        return property->value;
    }
    return 0.0f;
  }

  QVector3D getPosition() const
  {
    auto it = properties.find(POSITION_PROPERTY);
    if (it != properties.end())
    {
      auto property = it->second.getValue<PropertyType::Vector>();
      if (property != nullptr)
        return property->value;
    }
    return {};
  }

  std::optional<Property> getProperty(std::string propertyName) const
  {
    auto it = properties.find(propertyName);
    if (it != properties.end())
    {
      auto property = it->second.getValue<PropertyType::Vector>();
      if (property != nullptr)
        return *property;
    }
    return std::nullopt;
  }

  void setRadius(float radius)
  {
    properties.emplace(RADIUS_PROPERTY, ScalarProperty{radius});
  }

  void setPosition(QVector3D position)
  {
    properties.emplace(POSITION_PROPERTY, VectorProperty{position});
  }
  void setProperty(std::string propertyName, Property property)
  {
    properties.emplace(propertyName, property);
  }

  PropertyMap properties;
};

#endif