#ifndef ANY_PARTICLE_MATCHER_H
#define ANY_PARTICLE_MATCHER_H

#include "ParticleMatcher.h"

/** Match any particle */
class AnyParticleMatcher : public ParticleMatcher
{
public:
  bool match(const Particle &particle) const override
  {
    return true;
  }

  std::string getText() const override
  {
    return "*";
  }
};

#endif