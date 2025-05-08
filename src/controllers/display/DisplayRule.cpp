#include "DisplayRule.h"

std::optional<float> DisplayRule::getValue(const Particle &particle, std::string property, Particle::PropertyType type) const
{
  if (type == Particle::PropertyType::Scalar)
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

void DisplayRule::setEnabled(bool enabled)
{
  this->enabled = enabled;
  enabledObservable.notify();
}

void DisplayRule::setColor(QColor color)
{
  this->color = color;
}

bool DisplayRule::isEnabled() const
{
  return enabled;
}

QColor DisplayRule::getColor() const
{
  return color;
}

AbstractBinaryDisplayRule::AbstractBinaryDisplayRule(std::string property, Particle::PropertyType type, float compareValue, std::string symbol)
    : property{property}, type{type}, compareValue{compareValue}, symbol{symbol}
{
}

std::string AbstractBinaryDisplayRule::getText() const
{
  auto stream = std::stringstream{};
  stream << property << " " << symbol << " " << compareValue;
  return stream.str();
}

std::string AbstractBinaryDisplayRule::getProperty() const
{
  return property;
}

Particle::PropertyType AbstractBinaryDisplayRule::getType() const
{
  return type;
}

float AbstractBinaryDisplayRule::getCompareValue() const
{
  return compareValue;
}

std::string AbstractBinaryDisplayRule::getSymbol() const
{
  return symbol;
}
