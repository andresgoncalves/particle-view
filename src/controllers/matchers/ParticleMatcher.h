#ifndef PARTICLE_MATCHER_H
#define PARTICLE_MATCHER_H

#include <optional>
#include <sstream>

#include <models/Particle.h>

class ParticleMatcher
{
public:
  virtual ~ParticleMatcher() = default;

  /** Test a particle with current rule */
  virtual bool match(const Particle &particle) const = 0;

  /** Get rule text */
  virtual std::string getText() const = 0;
};

#endif