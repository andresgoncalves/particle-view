#ifndef DISPLAY_RULE_H
#define DISPLAY_RULE_H

#include <functional>
#include <optional>
#include <sstream>

#include "../Observable.h"
#include "../../models/Particle.h"

class DisplayRule
{
public:
  ~DisplayRule() = default;

  virtual bool test(const Particle &particle) const = 0;
  virtual std::string getText() const = 0;

  void setEnabled(bool enabled);

  bool isEnabled() const;

  Observable<bool> enabledObservable = enabled;

protected:
  virtual std::optional<float> getValue(const Particle &particle, std::string property, Particle::PropertyType type) const;

  bool enabled = true;
};

template <typename Comparator>
class BinaryDisplayRule : public DisplayRule
{
public:
  bool test(const Particle &particle) const override
  {
    auto currentValue = getValue(particle, property, type);
    return currentValue.has_value() && compare(currentValue.value(), compareValue);
  }

  std::string getText() const override
  {
    auto stream = std::stringstream{};
    stream << property << " " << symbol << " " << compareValue;
    return stream.str();
  }

  std::string getProperty() const
  {
    return property;
  }

  Particle::PropertyType getType() const
  {
    return type;
  }

  float geCompareValue() const
  {
    return compareValue;
  }

  std::string getSymbol() const
  {
    return symbol;
  }

protected:
  BinaryDisplayRule(std::string property, Particle::PropertyType type, float compareValue, std::string symbol, Comparator compare = {})
      : property{property}, type{type}, compareValue{compareValue}, symbol{symbol}, compare{compare}
  {
  }

private:
  std::string property;
  Particle::PropertyType type;
  float compareValue;

  std::string symbol;
  Comparator compare;
};

struct DisplayRuleEqual : public BinaryDisplayRule<std::equal_to<float>>
{
  DisplayRuleEqual(std::string property, Particle::PropertyType type, float compareValue) : BinaryDisplayRule{property, type, compareValue, "="} {}
};
struct DisplayRuleNotEqual : public BinaryDisplayRule<std::not_equal_to<float>>
{
  DisplayRuleNotEqual(std::string property, Particle::PropertyType type, float compareValue) : BinaryDisplayRule{property, type, compareValue, "≠"} {}
};
struct DisplayRuleLess : public BinaryDisplayRule<std::less<float>>
{
  DisplayRuleLess(std::string property, Particle::PropertyType type, float compareValue) : BinaryDisplayRule{property, type, compareValue, "<"} {}
};
struct DisplayRuleGreater : public BinaryDisplayRule<std::greater<float>>
{
  DisplayRuleGreater(std::string property, Particle::PropertyType type, float compareValue) : BinaryDisplayRule{property, type, compareValue, ">"} {}
};
struct DisplayRuleLessEqual : public BinaryDisplayRule<std::less_equal<float>>
{
  DisplayRuleLessEqual(std::string property, Particle::PropertyType type, float compareValue) : BinaryDisplayRule{property, type, compareValue, "≤"} {}
};
struct DisplayRuleGreaterEqual : public BinaryDisplayRule<std::greater_equal<float>>
{
  DisplayRuleGreaterEqual(std::string property, Particle::PropertyType type, float compareValue) : BinaryDisplayRule{property, type, compareValue, "≥"} {}
};

#endif