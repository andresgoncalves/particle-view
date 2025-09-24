#include "DisplayController.h"

void DisplayController::setParticleRule(DisplayRule rule)
{
  particleRule = rule;
  particleRuleObservable.notify(particleRule);
}

void DisplayController::setVectorRule(std::string property, DisplayRule rule)
{
  vectorRules[property] = rule;
  vectorRulesObservable.notify(vectorRules);
}

DisplayController::CustomRules::iterator DisplayController::addCustomRule(CustomRules::value_type displayRule)
{
  customRules.push_back(displayRule);
  customRulesObservable.notify(customRules);
  return std::prev(customRules.end());
}

void DisplayController::replaceCustomRule(CustomRules::iterator it, CustomRules::value_type displayRule)
{
  *it = displayRule;
  customRulesObservable.notify(customRules);
}

void DisplayController::removeCustomRule(CustomRules::iterator it)
{
  customRules.erase(it);
  customRulesObservable.notify(customRules);
}

void DisplayController::clearCustomRules()
{
  customRules.clear();
  customRulesObservable.notify(customRules);
}

void DisplayController::setBackgroundColor(QColor color)
{
  this->backgroundColor = color;
  backgroundColorObservable.notify();
}

DisplayRule &DisplayController::getParticleRule()
{
  return particleRule;
}

DisplayRule DisplayController::getVectorRule(std::string property)
{
  auto it = vectorRules.find(property);
  if (it != vectorRules.end())
    return it->second;

  auto rule = DisplayRule{};
  rule.setVisible(false);
  return rule;
}

DisplayController::VectorRules &DisplayController::getVectorRules()
{
  return vectorRules;
}

DisplayController::CustomRules &DisplayController::getCustomRules()
{
  return customRules;
}

QColor DisplayController::getBackgroundColor() const
{
  return backgroundColor;
}

DisplayRule DisplayController::getMatchingParticleRule(const Particle &particle)
{
  auto displayRule = getMatchingCustomRule(particle);
  return displayRule.value_or(particleRule);
}

DisplayRule DisplayController::getMatchingVectorRule(const Particle &particle, std::string property)
{
  auto displayRule = getMatchingCustomRule(particle);
  return displayRule.value_or(getVectorRule(property));
}

std::optional<DisplayRule> DisplayController::getMatchingCustomRule(const Particle &particle)
{
  auto result = std::optional<DisplayRule>{};
  for (auto customRule : customRules)
  {
    if (customRule->isEnabled() && customRule->getMatcher()->match(particle))
      result = *customRule;
  }
  return result;
}