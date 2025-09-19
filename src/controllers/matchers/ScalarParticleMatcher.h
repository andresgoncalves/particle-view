#ifndef SCALAR_PARTICLE_MATCHER_H
#define SCALAR_PARTICLE_MATCHER_H

#include <functional>
#include <memory>

#include "BinaryParticleMatcher.h"

/** Compare a scalar property */
class AbstractScalarBinaryParticleMatcher : public BinaryParticleMatcher<float>
{
public:
  bool match(const Particle &particle) const override
  {
    auto currentValue = getValue(particle);
    return currentValue.has_value() && compare(currentValue.value(), referenceValue);
  }

  AbstractScalarBinaryParticleMatcher(
      std::string propertyName,
      std::string symbol,
      float referenceValue)
      : AbstractBinaryParticleMatcher{propertyName,
                                      symbol,
                                      referenceValue}
  {
  }
}

/** Compare a scalar property */
template <typename Comparator>
class ScalarBinaryParticleMatcher : public AbstractScalarBinaryParticleMatcher
{
public:
  bool match(const Particle &particle) const override
  {
    auto currentValue = getValue(particle);
    return currentValue.has_value() && compare(currentValue.value(), referenceValue);
  }

  ScalarBinaryParticleMatcher(
      std::string propertyName,
      std::string symbol,
      float referenceValue,
      Comparator compare = {})
      : AbstractScalarBinaryParticleMatcher{propertyName,
                                            symbol,
                                            referenceValue},
        compare{compare}
  {
  }

private:
  Comparator compare;

  std::optional<float> getValue(const Particle &particle) const
  {
    auto it = particle.properties.find(propertyName);
    if (it != particle.properties.end())
    {
      auto property =
          it->second.getValue<PropertyType::Scalar>();

      if (property != nullptr)
        return property->value;
    }
    return std::nullopt;
  }
};

/** Create a scalar particule rule */
class ScalarParticleMatcherFactory
{
public:
  ScalarParticleMatcherFactory(
      std::string propertyName) : propertyName{propertyName}
  {
  }

  constexpr std::unique_ptr<AbstractScalarBinaryParticleMatcher> equal(float value) const
  {
    return std::make_unique<ScalarBinaryParticleMatcher<std::equal_to<float>>>(propertyName, "=", value);
  }

  constexpr std::unique_ptr<AbstractScalarBinaryParticleMatcher> notEqual(float value) const
  {
    return std::make_unique<ScalarBinaryParticleMatcher<std::not_equal_to<float>>>(propertyName, "≠", value);
  }

  constexpr std::unique_ptr<AbstractScalarBinaryParticleMatcher> less(float value) const
  {
    return std::make_unique<ScalarBinaryParticleMatcher<std::less<float>>>(propertyName, "<", value);
  }

  constexpr std::unique_ptr<AbstractScalarBinaryParticleMatcher> greater(float value) const
  {
    return std::make_unique<ScalarBinaryParticleMatcher<std::greater<float>>>(propertyName, ">", value);
  }

  constexpr std::unique_ptr<AbstractScalarBinaryParticleMatcher> lessOrEqual(float value) const
  {
    return std::make_unique<ScalarBinaryParticleMatcher<std::less_equal<float>>>(propertyName, "≤", value);
  }

  constexpr std::unique_ptr<AbstractScalarBinaryParticleMatcher> greaterOrEqual(float value) const
  {
    return std::make_unique<ScalarBinaryParticleMatcher<std::greater_equal<float>>>(propertyName, "≥", value);
  }

private:
  std::string propertyName;
};

#endif