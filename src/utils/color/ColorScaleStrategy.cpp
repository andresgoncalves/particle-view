#include "ColorScaleStrategy.h"

#include <cmath>

ColorScaleStrategy::ColorScaleStrategy(
    std::string propertyName,
    std::pair<float, QColor> start,
    std::pair<float, QColor> end,
    VectorComponent vectorComponent) : propertyName{propertyName},
                                       start{start}, end{end}, vectorComponent{vectorComponent} {}

QColor ColorScaleStrategy::getColor(const Particle &particle) const
{
  auto defaultValue = start.first;

  auto value = getValue(particle).value_or(start.first);

  auto normalizedValue = std::clamp((value - start.first) / (end.first - start.first), 0.0f, 1.0f);

  auto color = QColor::fromRgbF(
      start.second.redF() + normalizedValue * (end.second.redF() - start.second.redF()),
      start.second.greenF() + normalizedValue * (end.second.greenF() - start.second.greenF()),
      start.second.blueF() + normalizedValue * (end.second.blueF() - start.second.blueF()));

  return color;
}

std::string ColorScaleStrategy::getProperty() const
{
  return propertyName;
}

VectorComponent ColorScaleStrategy::getVectorComponent() const
{
  return vectorComponent;
}

std::pair<float, QColor> ColorScaleStrategy::getStart() const
{
  return start;
}

std::pair<float, QColor> ColorScaleStrategy::getEnd() const
{
  return end;
}

std::optional<float> ColorScaleStrategy::getValue(const Particle &particle) const
{
  auto it = particle.properties.find(propertyName);
  if (it != particle.properties.end())
  {
    switch (it->second.getType())
    {
    case PropertyType::Scalar:
      return it->second.getValue<PropertyType::Scalar>()->value;
    case PropertyType::Vector:
      return it->second.getValue<PropertyType::Vector>()->getComponent(vectorComponent);
    case PropertyType::String:
      break;
    }
  }
  return std::nullopt;
}
