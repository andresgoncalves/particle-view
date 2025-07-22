#ifndef COLOR_STRATEGY_H
#define COLOR_STRATEGY_H

#include <QtGui/QColor>

#include <models/Particle.h>

/** Interface template for coloring a particle */
class ColorStrategy
{
public:
  virtual ~ColorStrategy() = default;

  /** Get color for particle */
  virtual QColor getColor(const Particle &particle) const = 0;
};

#endif