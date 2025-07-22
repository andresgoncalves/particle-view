#ifndef SOLID_COLOR_STRATEGY_H
#define SOLID_COLOR_STRATEGY_H

#include "ColorStrategy.h"

/** Solid color strategy implementation */
class SolidColorStrategy : public ColorStrategy
{
public:
  /** Create a solid color strategy */
  SolidColorStrategy(QColor color);

  /** Get color for particle */
  QColor getColor(const Particle &particle) const override;

  /** Get solid color */
  QColor getSolidColor() const;

protected:
  QColor solidColor;
};

#endif