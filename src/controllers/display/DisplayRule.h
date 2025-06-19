#ifndef DISPLAY_RULE_H
#define DISPLAY_RULE_H

#include <functional>
#include <optional>
#include <string>

#include <QtGui/QColor>

#include "../Observable.h"
#include "../../models/Particle.h"

class DisplayRule
{
public:
  virtual ~DisplayRule() = default;

  virtual bool test(const Particle &particle) const = 0;
  virtual std::string getText() const = 0;

  void setEnabled(bool enabled);
  void setColor(QColor color);

  bool isEnabled() const;
  QColor getColor() const;

  Observable<bool> enabledObservable = enabled;

protected:
  virtual std::optional<float> getValue(const Particle &particle, std::string property, Particle::PropertyType type) const;

  bool enabled = true;
  QColor color;
};

class AbstractBinaryDisplayRule : public DisplayRule
{
public:
  virtual bool test(const Particle &particle) const override = 0;

  Particle::PropertyType getType() const;
  std::string getText() const override;
  std::string getProperty() const;
  std::string getSymbol() const;

  float getCompareValue() const;

protected:
  AbstractBinaryDisplayRule(std::string property, Particle::PropertyType type, float compareValue, std::string symbol);

  Particle::PropertyType type;
  std::string property;
  std::string symbol;
  float compareValue;
};

template <typename Comparator>
class BinaryDisplayRule : public AbstractBinaryDisplayRule
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

  float getCompareValue() const
  {
    return compareValue;
  }

  std::string getSymbol() const
  {
    return symbol;
  }

protected:
  BinaryDisplayRule(std::string property, Particle::PropertyType type, float compareValue, std::string symbol, Comparator compare = {})
      : AbstractBinaryDisplayRule{property, type, compareValue, symbol}, compare{compare}
  {
  }

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