#ifndef BINARY_PARTICLE_MATCHER_H
#define BINARY_PARTICLE_MATCHER_H

#include "ParticleMatcher.h"

/** Compare a property with a reference value */
template <typename T>
class BinaryParticleMatcher : public ParticleMatcher
{
public:
  std::string getText() const override
  {
    auto stream = std::stringstream{};
    stream << propertyName << " " << symbol << " " << referenceValue;
    return stream.str();
  }

  BinaryParticleMatcher(
      std::string propertyName,
      std::string symbol,
      T referenceValue)
      : propertyName{propertyName},
        symbol{symbol},
        referenceValue{referenceValue}
  {
  }

protected:
  std::string propertyName;
  std::string symbol;
  T referenceValue;
};

#endif