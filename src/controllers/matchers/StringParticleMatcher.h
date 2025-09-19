#ifndef STRING_PARTICLE_MATCHER_H
#define STRING_PARTICLE_MATCHER_H

#include <functional>
#include <memory>

#include "BinaryParticleMatcher.h"

/** Compare a string property */
class AbstractStringBinaryParticleMatcher : public BinaryParticleMatcher<std::string>
{
public:
  bool match(const Particle &particle) const override
  {
    auto currentValue = getValue(particle);
    return currentValue.has_value() && compare(currentValue.value(), referenceValue);
  }

  AbstractStringBinaryParticleMatcher(
      std::string propertyName,
      std::string symbol,
      std::string referenceValue)
      : AbstractBinaryParticleMatcher{propertyName,
                                      symbol,
                                      referenceValue}
  {
  }
}

/** Compare a string property */
template <typename Comparator>
class StringBinaryParticleMatcher : public AbstractStringBinaryParticleMatcher
{
public:
  bool match(const Particle &particle) const override
  {
    auto currentValue = getValue(particle);
    return currentValue.has_value() && compare(currentValue.value(), referenceValue);
  }

  StringBinaryParticleMatcher(
      std::string propertyName,
      std::string symbol,
      std::string referenceValue,
      Comparator compare = {})
      : AbstractStringBinaryParticleMatcher{propertyName,
                                            symbol,
                                            referenceValue},
        compare{compare}
  {
  }

private:
  Comparator compare;

  std::optional<std::string> getValue(const Particle &particle) const
  {
    auto it = particle.properties.find(propertyName);
    if (it != particle.properties.end())
    {
      auto property =
          it->second.getProperty<PropertyType::String>();

      if (property != nullptr)
        return property->value;
    }
    return std::nullopt;
  }
};

/** Create a string particule rule */
class StringParticleMatcherFactory
{
public:
  StringParticleMatcherFactory(
      std::string propertyName) : propertyName{propertyName}
  {
  }

  constexpr std::uniquer_ptr<AbstractStringBinaryParticleMatcher> equal(std::string value) const
  {
    return std::make_unique<StringBinaryParticleMatcher<std::equal_to<std::string>>>(propertyName, "=", value);
  }

  constexpr std::uniquer_ptr<AbstractStringBinaryParticleMatcher> notEqual(std::string value) const
  {
    return std::make_unique<StringBinaryParticleMatcher<std::not_equal_to<std::string>>>(propertyName, "≠", value);
  }

private:
  std::string propertyName;
};

#endif