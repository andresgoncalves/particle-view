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
      std::string propertyName,
      std::pair<float, QColor> start,
      std::pair<float, QColor> end,
      VectorComponent vectorComponent = VectorComponent::Magnitude);

  /** Get color for particle */
  QColor getColor(const Particle &particle) const override;

  /** Get property */
  std::string getProperty() const;
  /** Get vector component */
  VectorComponent getVectorComponent() const;
  /** Get start value and color */
  std::pair<float, QColor> getStart() const;
  /** Get end value and color */
  std::pair<float, QColor> getEnd() const;

private:
  /** Extract property value from particle */
  std::optional<float> getValue(const Particle &particle) const;

  /** Property */
  std::string propertyName;
  /** Vector component */
  VectorComponent vectorComponent;
  /** Start value and color */
  std::pair<float, QColor> start;
  /** End value and color */
  std::pair<float, QColor> end;
};

#endif