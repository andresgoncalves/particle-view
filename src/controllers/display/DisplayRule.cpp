
#include "DisplayRule.h"

DisplayRule::DisplayRule(DisplayRule::Predicate predicate) : predicate{predicate} {}

bool DisplayRule::test(const Particle &particle) const
{
  return predicate(particle);
}

DisplayRule::Predicate DisplayRule::Scalar::equal(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.scalarProperties.find(property);
    return it != particle.scalarProperties.end() && it->second == value;
  };
}

DisplayRule::Predicate DisplayRule::Scalar::less(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.scalarProperties.find(property);
    return it != particle.scalarProperties.end() && it->second < value;
  };
}

DisplayRule::Predicate DisplayRule::Scalar::greater(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.scalarProperties.find(property);
    return it != particle.scalarProperties.end() && it->second > value;
  };
}

DisplayRule::Predicate DisplayRule::Scalar::equalOrLess(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.scalarProperties.find(property);
    return it != particle.scalarProperties.end() && it->second <= value;
  };
}

DisplayRule::Predicate DisplayRule::Scalar::equalOrGreater(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.scalarProperties.find(property);
    return it != particle.scalarProperties.end() && it->second >= value;
  };
}

DisplayRule::Predicate DisplayRule::Scalar::between(std::string property, float min, float max)
{
  return [=](const Particle &particle)
  {
    auto it = particle.scalarProperties.find(property);
    return it != particle.scalarProperties.end() && it->second >= min && it->second <= max;
  };
}

DisplayRule::Predicate DisplayRule::Vector::equal(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.vectorProperties.find(property);
    return it != particle.vectorProperties.end() && it->second.length() == value;
  };
}

DisplayRule::Predicate DisplayRule::Vector::less(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.vectorProperties.find(property);
    return it != particle.vectorProperties.end() && it->second.length() < value;
  };
}

DisplayRule::Predicate DisplayRule::Vector::greater(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.vectorProperties.find(property);
    return it != particle.vectorProperties.end() && it->second.length() > value;
  };
}

DisplayRule::Predicate DisplayRule::Vector::equalOrLess(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.vectorProperties.find(property);
    return it != particle.vectorProperties.end() && it->second.length() <= value;
  };
}

DisplayRule::Predicate DisplayRule::Vector::equalOrGreater(std::string property, float value)
{
  return [=](const Particle &particle)
  {
    auto it = particle.vectorProperties.find(property);
    return it != particle.vectorProperties.end() && it->second.length() >= value;
  };
}

DisplayRule::Predicate DisplayRule::Vector::between(std::string property, float min, float max)
{
  return [=](const Particle &particle)
  {
    auto it = particle.vectorProperties.find(property);
    return it != particle.vectorProperties.end() && it->second.length() >= min && it->second.length() <= max;
  };
}
