#ifndef COLOR_SCALE_STRATEGY_H
#define COLOR_SCALE_STRATEGY_H

#include "ColorStrategy.h"

#include <string>
#include <optional>
#include <utility>

/** Color scale strategy implementation */
class ColorScaleStrategy : public ColorStrategy
{
public:
  /** Create a color scale strategy */
  ColorScaleStrategy(
      std::string property,
      Particle::PropertyType propertyType,
      std::pair<float, QColor> start,
      std::pair<float, QColor> end);

  /** Get color for particle */
  QColor getColor(const Particle &particle) const override;

  /** Get property */
  std::string getProperty() const;
  /** Get property type */
  Particle::PropertyType getPropertyType() const;
  /** Get start value and color */
  std::pair<float, QColor> getStart() const;
  /** Get end value and color */
  std::pair<float, QColor> getEnd() const;

private:
  /** Extract property value from particle */
  std::optional<float> getValue(const Particle &particle, std::string property, Particle::PropertyType type) const;

  /** Property */
  std::string property;
  /** Property type */
  Particle::PropertyType propertyType;
  /** Start value and color */
  std::pair<float, QColor> start;
  /** End value and color */
  std::pair<float, QColor> end;
};

#endif