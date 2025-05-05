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

bool DisplayRule::isEnabled() const
{
  return enabled;
}
