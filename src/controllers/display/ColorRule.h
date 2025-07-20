#ifndef COLOR_RULE_H
#define COLOR_RULE_H

#include <optional>
#include <string>

#include <QtGui/QColor>

#include "../Observable.h"
#include "../../models/Particle.h"

class ColorRule
{
public:
  virtual ~ColorRule() = default;

  virtual QColor getColor(const Particle &particle) const = 0;
};

class FixedColorRule : public ColorRule
{
public:
  FixedColorRule(QColor color);

  QColor getColor(const Particle &particle) const override;

  QColor getFixedColor() const;

protected:
  QColor fixedColor;
};

class GradientColorRule : public ColorRule
{
public:
  GradientColorRule(
      std::string property, Particle::PropertyType type,
      float startValue, float endValue,
      QColor startColor, QColor endColor);

  QColor getColor(const Particle &particle) const override;

  std::string getProperty() const;
  Particle::PropertyType getType() const;
  float getStartValue() const;
  float getEndValue() const;
  QColor getStartColor() const;
  QColor getEndColor() const;

private:
  std::optional<float> getValue(const Particle &particle, std::string property, Particle::PropertyType type) const;

  std::string property;
  Particle::PropertyType type;
  float startValue;
  float endValue;
  QColor startColor;
  QColor endColor;
};

#endif