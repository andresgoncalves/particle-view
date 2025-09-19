#ifndef VECTOR_PARTICLE_MATCHER_H
#define VECTOR_PARTICLE_MATCHER_H

#include <functional>
#include <memory>

#include "BinaryParticleMatcher.h"

/** Compare a vector property */
class AbstractVectorBinaryParticleMatcher : public BinaryParticleMatcher<float>
{
public:
  AbstractVectorBinaryParticleMatcher(
      std::string propertyName,
      std::string symbol,
      float referenceValue,
      VectorComponent vectorComponent = VectorComponent::Magnitude, )
      : AbstractBinaryParticleMatcher{propertyName,
                                      symbol,
                                      referenceValue},
        vectorComponent{vectorComponent},
  {
  }

  VectorComponent getVectorComponent() const
  {
    return vectorComponent;
  }

private:
  Comparator compare;
  VectorComponent vectorComponent;
};

/** Compare a vector property */
template <typename Comparator>
class VectorBinaryParticleMatcher : public AbstractVectorBinaryParticleMatcher
{
public:
  bool match(const Particle &particle) const override
  {
    auto currentValue = getValue(particle);
    return currentValue.has_value() && compare(currentValue.value(), referenceValue);
  }

  VectorBinaryParticleMatcher(
      std::string propertyName,
      std::string symbol,
      float referenceValue,
      VectorComponent vectorComponent = VectorComponent::Magnitude,
      Comparator compare = {})
      : AbstractVectorBinaryParticleMatcher{propertyName,
                                            symbol,
                                            referenceValue},
        vectorComponent{vectorComponent},
        compare{compare}
  {
  }

private:
  Comparator compare;
  VectorComponent vectorComponent;

  std::optional<float> getValue(const Particle &particle) const
  {
    auto it = particle.properties.find(propertyName);
    if (it != particle.properties.end())
    {
      auto property =
          it->second.getProperty<PropertyType::Vector>();

      if (property != nullptr)
        return property->getComponent(vectorComponent);
    }
    return std::nullopt;
  }
};

/** Create a vector particule rule */
class VectorParticleMatcherFactory
{
public:
  VectorParticleMatcherFactory(
      std::string propertyName,
      VectorComponent vectorComponent = VectorComponent::Magnitude) : propertyName{propertyName}, vectorComponent{vectorComponent}
  {
  }

  constexpr std::unique_ptr<AbstractVectorParticleMatcher> equal(float value) const
  {
    return std::make_unique<VectorBinaryParticleMatcher<std::equal_to<float>>>(propertyName, "=", value, vectorComponent);
  }

  constexpr std::unique_ptr<AbstractVectorParticleMatcher> notEqual(float value) const
  {
    return std::make_unique<VectorBinaryParticleMatcher<std::not_equal_to<float>>>(propertyName, "≠", value, vectorComponent);
  }

  constexpr std::unique_ptr<AbstractVectorParticleMatcher> less(float value) const
  {
    return std::make_unique<VectorBinaryParticleMatcher<std::less<float>>>(propertyName, "<", value, vectorComponent);
  }

  constexpr std::unique_ptr<AbstractVectorParticleMatcher> greater(float value) const
  {
    return std::make_unique<VectorBinaryParticleMatcher<std::greater<float>>>(propertyName, ">", value, vectorComponent);
  }

  constexpr std::unique_ptr<AbstractVectorParticleMatcher> lessOrEqual(float value) const
  {
    return std::make_unique<VectorBinaryParticleMatcher<std::less_equal<float>>>(propertyName, "≤", value, vectorComponent);
  }

  constexpr std::unique_ptr<AbstractVectorParticleMatcher> greaterOrEqual(float value) const
  {
    return std::make_unique<VectorBinaryParticleMatcher<std::greater_equal<float>>>(propertyName, "≥", value, vectorComponent);
  }

private:
  std::string propertyName;
  VectorComponent vectorComponent;
};

#endif