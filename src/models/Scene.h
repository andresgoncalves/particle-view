#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>

#include <QtGui/QVector3D>

#include "Particle.h"

struct Scene
{
  inline static const std::string PARTICLE_COUNT_PROPERTY = "N° de Partículas";
  inline static const std::string TIME_PROPERTY = "Tiempo";

  int frame;
  std::vector<Particle> particles;
  PropertyMap properties;

  int getParticleCount() const
  {
    auto it = properties.find(PARTICLE_COUNT_PROPERTY);
    if (it != properties.end())
    {
      auto property = it->second.getValue<PropertyType::Scalar>();
      if (property != nullptr)
        return property->value;
    }
    return 0;
  }

  double getTime() const
  {
    auto it = properties.find(TIME_PROPERTY);
    if (it != properties.end())
    {
      auto property = it->second.getValue<PropertyType::Scalar>();
      if (property != nullptr)
        return property->value;
    }
    return 0.0;
  }

  std::optional<Property> getProperty(std::string propertyName) const
  {
    auto it = properties.find(propertyName);
    if (it != properties.end())
      return it->second;
    return std::nullopt;
  }

  void setTime(float time)
  {
    properties.emplace(TIME_PROPERTY, ScalarProperty{time});
  }
  void setTime(double time)
  {
    setTime(static_cast<float>(time));
  }

  struct Metadata
  {
    QVector3D start;
    QVector3D end;
    std::map<std::string, float> maxValues;
    PropertyTypeMap particleProperties;
  } metadata;
};

#endif