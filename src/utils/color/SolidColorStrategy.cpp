#include "SolidColorStrategy.h"

SolidColorStrategy::SolidColorStrategy(QColor color) : solidColor{color} {}

QColor SolidColorStrategy::getColor(const Particle &) const
{
  return solidColor;
}

QColor SolidColorStrategy::getSolidColor() const
{
  return solidColor;
}
