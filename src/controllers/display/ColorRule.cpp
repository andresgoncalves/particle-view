#include <cmath>

#include "ColorRule.h"

FixedColorRule::FixedColorRule(QColor color) : fixedColor{color} {}

QColor FixedColorRule::getColor(const Particle &) const
{
  return fixedColor;
}

QColor FixedColorRule::getFixedColor() const
{
  return fixedColor;
}

GradientColorRule::GradientColorRule(
    std::string property, Particle::PropertyType type,
    float startValue, float endValue,
    QColor startColor, QColor endColor) : property{property}, type{type},
                                          startValue{startValue}, endValue{endValue},
                                          startColor{startColor}, endColor{endColor} {}

QColor GradientColorRule::getColor(const Particle &particle) const
{
  auto defaultValue = startValue;

  auto value = getValue(particle, property, type).value_or(defaultValue);

  auto normalizedValue = std::clamp((value - startValue) / (endValue - startValue), 0.0f, 1.0f);

  auto color = QColor::fromRgbF(
      startColor.redF() + normalizedValue * (endColor.redF() - startColor.redF()),
      startColor.greenF() + normalizedValue * (endColor.greenF() - startColor.greenF()),
      startColor.blueF() + normalizedValue * (endColor.blueF() - startColor.blueF()));

  return color;
}

std::string GradientColorRule::getProperty() const
{
  return property;
}

Particle::PropertyType GradientColorRule::getType() const
{
  return type;
}

float GradientColorRule::getStartValue() const
{
  return startValue;
}

float GradientColorRule::getEndValue() const
{
  return endValue;
}

QColor GradientColorRule::getStartColor() const
{
  return startColor;
}

QColor GradientColorRule::getEndColor() const
{
  return endColor;
}

std::optional<float> GradientColorRule::getValue(const Particle &particle, std::string property, Particle::PropertyType type) const
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
