#ifndef PARTICLE_H
#define PARTICLE_H

#include <map>
#include <QtGui/QVector3D>

#include "Property.h"

struct Particle
{
  inline static const std::string RADIUS_PROPERTY = "Radio";
  inline static const std::string POSITION_PROPERTY = "Posición";

  constexpr float getRadius()
  {
    auto it = properties.find(RADIUS_PROPERTY);
    if (it != properties.end())
    {
      auto property = it->second.getProperty<PropertyType::Scalar>();
      if (property != nullptr)
        return property->value;
    }
    return 0.0f;
  }

  constexpr QVector3D getPosition()
  {
    auto it = properties.find(POSITION_PROPERTY);
    if (it != properties.end())
    {
      auto property = it->second.getProperty<PropertyType::Vector>();
      if (property != nullptr)
        return property->value;
    }
    return {};
  }

  std::map<std::string, Property> properties;
};

#endif