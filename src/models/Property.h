#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <variant>
#include <map>

#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

template <typename T>
struct BaseProperty
{
  BaseProperty(T value) : value{value} {}

  T value;
};

struct StringProperty : public BaseProperty<std::string>
{
  StringProperty(std::string value) : BaseProperty{value} {}
};

struct ScalarProperty : public BaseProperty<float>
{
  ScalarProperty(float value) : BaseProperty{value} {}
};

enum class VectorComponent
{
  Magnitude,
  X,
  Y,
  Z,
};

struct VectorProperty : public BaseProperty<QVector3D>
{
  VectorProperty(QVector3D value) : BaseProperty{value} {}

  constexpr float getComponent(VectorComponent component) const
  {
    switch (component)
    {
    case VectorComponent::X:
      return value.x();
    case VectorComponent::Y:
      return value.y();
    case VectorComponent::Z:
      return value.z();
    }
    return value.length();
  }
};

enum class PropertyType
{
  Scalar,
  Vector,
  String,
};

class Property : private std::variant<ScalarProperty, VectorProperty, StringProperty>
{
public:
  Property(ScalarProperty property) : std::variant<ScalarProperty, VectorProperty, StringProperty>{property}
  {
  }
  Property(VectorProperty property) : std::variant<ScalarProperty, VectorProperty, StringProperty>{property}
  {
  }
  Property(StringProperty property) : std::variant<ScalarProperty, VectorProperty, StringProperty>{property}
  {
  }

  template <PropertyType I>
  constexpr auto getValue() const noexcept
  {
    return std::get_if<static_cast<std::size_t>(I)>(this);
  }

  constexpr PropertyType getType() const noexcept
  {
    return static_cast<PropertyType>(this->index());
  }
};

#endif