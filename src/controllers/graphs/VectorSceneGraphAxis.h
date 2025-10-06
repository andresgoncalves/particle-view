#ifndef VECTOR_SCENE_GRAPH_AXIS_H
#define VECTOR_SCENE_GRAPH_AXIS_H

#include "GraphAxis.h"

/** Graph a vector property */
class VectorSceneGraphAxis : public GraphAxis<float>
{
public:
  VectorSceneGraphAxis(std::string propertyName, VectorComponent vectorComponent = VectorComponent::Magnitude)
      : GraphAxis{}, propertyName{propertyName}, vectorComponent{vectorComponent}
  {
  }

  /** Get scene value with current axis */
  std::optional<float> getValue(const Scene &scene) const override
  {
    auto property = scene.getProperty(propertyName);
    if (!property.has_value() || property.value().getType() != PropertyType::Vector)
      return std::nullopt;
    return property.value().getValue<PropertyType::Vector>()->getComponent(vectorComponent);
  }

  /** Get axis text */
  std::string getText() const override
  {
    switch (vectorComponent)
    {
    case VectorComponent::Magnitude:
      return this->propertyName + " (Magnitud)";
    case VectorComponent::X:
      return this->propertyName + " (Componente X)";
    case VectorComponent::Y:
      return this->propertyName + " (Componente Y)";
    case VectorComponent::Z:
      return this->propertyName + " (Componente Z)";
    }
  }

  /** Get property name */
  std::string getPropertyName() const
  {
    return propertyName;
  }

  /** Get vector component */
  VectorComponent getVectorComponent() const
  {
    return vectorComponent;
  }

private:
  std::string propertyName;
  VectorComponent vectorComponent;
};

#endif