#ifndef SCALAR_SCENE_GRAPH_AXIS_H
#define SCALAR_SCENE_GRAPH_AXIS_H

#include "GraphAxis.h"

/** Graph a scalar property */
class ScalarSceneGraphAxis : public GraphAxis
{
public:
  ScalarSceneGraphAxis(std::string propertyName)
      : GraphAxis{}, propertyName{propertyName}
  {
  }

  /** Get scene value with current axis */
  std::optional<float> getValue(const Scene &scene) const override
  {
    auto property = scene.getProperty(propertyName);
    if (!property.has_value() || property.value().getType() != PropertyType::Scalar)
      return std::nullopt;
    return property.value().getValue<PropertyType::Scalar>()->value;
  }

  /** Get axis text */
  std::string getText() const override
  {
    return propertyName;
  }

  /** Get property name */
  std::string getPropertyName() const
  {
    return propertyName;
  }

private:
  std::string propertyName;
};

#endif