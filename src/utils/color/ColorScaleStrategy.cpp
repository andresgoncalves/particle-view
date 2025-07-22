#include "ColorScaleStrategy.h"

#include <cmath>

ColorScaleStrategy::ColorScaleStrategy(
    std::string property,
    Particle::PropertyType propertyType,
    std::pair<float, QColor> start,
    std::pair<float, QColor> end) : property{property}, propertyType{propertyType},
                                    start{start}, end{end} {}

QColor ColorScaleStrategy::getColor(const Particle &particle) const
{
  auto defaultValue = start.first;

  auto value = getValue(particle, property, propertyType).value_or(start.first);

  auto normalizedValue = std::clamp((value - start.first) / (end.first - start.first), 0.0f, 1.0f);

  auto color = QColor::fromRgbF(
      start.second.redF() + normalizedValue * (end.second.redF() - start.second.redF()),
      start.second.greenF() + normalizedValue * (end.second.greenF() - start.second.greenF()),
      start.second.blueF() + normalizedValue * (end.second.blueF() - start.second.blueF()));

  return color;
}

std::string ColorScaleStrategy::getProperty() const
{
  return property;
}

Particle::PropertyType ColorScaleStrategy::getPropertyType() const
{
  return propertyType;
}

std::pair<float, QColor> ColorScaleStrategy::getStart() const
{
  return start;
}

std::pair<float, QColor> ColorScaleStrategy::getEnd() const
{
  return end;
}

std::optional<float> ColorScaleStrategy::getValue(const Particle &particle, std::string property, Particle::PropertyType propertyType) const
{
  if (propertyType == Particle::PropertyType::Scalar)
  {
    auto it = particle.scalarProperties.find(property);
    return it != particle.scalarProperties.end() ? std::make_optional(it->second) : std::nullopt;
  }
  else
  {
    auto it = particle.vectorProperties.find(property);
    return it != particle.vectorProperties.end() ? std::make_optional(it->second.length()) : std::nullopt;
  }
}
