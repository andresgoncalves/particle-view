#ifndef DISPLAY_RULE_H
#define DISPLAY_RULE_H

#include <functional>

#include "../../models/Particle.h"

class DisplayRule
{
public:
  using Predicate = std::function<bool(const Particle &)>;

  struct Scalar
  {
    Scalar() = delete;

    static Predicate equal(std::string property, float value);
    static Predicate less(std::string property, float value);
    static Predicate greater(std::string property, float value);
    static Predicate equalOrLess(std::string property, float value);
    static Predicate equalOrGreater(std::string property, float value);
    static Predicate between(std::string property, float min, float max);
  };

  struct Vector
  {
    Vector() = delete;

    static Predicate equal(std::string property, float value);
    static Predicate less(std::string property, float value);
    static Predicate greater(std::string property, float value);
    static Predicate equalOrLess(std::string property, float value);
    static Predicate equalOrGreater(std::string property, float value);
    static Predicate between(std::string property, float min, float max);
  };

  DisplayRule(Predicate predicate);

  bool test(const Particle &particle) const;

private:
  Predicate predicate;
};

#endif