#include "DisplayController.h"

#include <utils/color/SolidColorStrategy.h>

DisplayController::DisplayController() : displayParticles{true, std::make_unique<SolidColorStrategy>(QColor{255, 255, 255})} {}

void DisplayController::toggleParticles()
{
  displayParticles.first = !displayParticles.first;
  displayParticlesObservable.notify();
}

void DisplayController::setDisplayParticles(bool value)
{
  displayParticles.first = value;
  displayParticlesObservable.notify();
}

void DisplayController::setDisplayParticles(std::shared_ptr<ColorStrategy> colorStrategy)
{
  displayParticles.second = colorStrategy;
  displayParticlesObservable.notify();
}

void DisplayController::toggleVector(std::string property)
{
  setDisplayVector(property, !getDisplayVector(property).first);
}

void DisplayController::setDisplayVector(std::string property, bool value)
{
  if (displayVectors.contains(property))
    displayVectors[property].first = value;
  else
    displayVectors[property] = {value, std::make_shared<SolidColorStrategy>(QColor{0, 0, 0})};

  displayVectorsObservable.notify();
}

void DisplayController::setDisplayVector(std::string property, std::shared_ptr<ColorStrategy> colorStrategy)
{
  if (displayVectors.contains(property))
    displayVectors[property].second = colorStrategy;
  else
    displayVectors[property] = {true, colorStrategy};

  displayVectorsObservable.notify();
}

DisplayController::DisplayProperty DisplayController::getDisplayParticles() const
{
  return displayParticles;
}

DisplayController::DisplayProperty DisplayController::getDisplayVector(std::string property) const
{
  auto displayVector = displayVectors.find(property);
  if (displayVector != displayVectors.end())
    return displayVector->second;
  return {false, std::make_shared<SolidColorStrategy>(QColor{0, 0, 0})};
}

std::map<std::string, DisplayController::DisplayProperty> DisplayController::getDisplayVectors() const
{
  return displayVectors;
}

DisplayController::DisplayRules DisplayController::getDisplayRules() const
{
  return displayRules;
}

DisplayController::DisplayRules &DisplayController::getDisplayRules()
{
  return displayRules;
}

void DisplayController::setBackgroundColor(QColor color)
{
  this->backgroundColor = color;
}

QColor DisplayController::getBackgroundColor() const
{
  return backgroundColor;
}

DisplayController::DisplayRules::iterator DisplayController::addDisplayRule(std::shared_ptr<DisplayRule> displayRule)
{
  displayRules.push_back(displayRule);
  displayRule->enabledObservable.subscribe(this, [&](bool enabled)
                                           { displayRulesObservable.notify(); });
  displayRulesObservable.notify();
  return std::prev(displayRules.end());
}

void DisplayController::replaceDisplayRule(DisplayRules::iterator it, std::shared_ptr<DisplayRule> displayRule)
{
  *it = displayRule;
  displayRule->enabledObservable.subscribe(this, [&](bool enabled)
                                           { displayRulesObservable.notify(); });
  displayRulesObservable.notify();
}

void DisplayController::removeDisplayRule(DisplayRules::iterator it)
{
  displayRules.erase(it);
  displayRulesObservable.notify();
}

void DisplayController::clearDisplayRules()
{
  displayRules.clear();
  displayRulesObservable.notify();
}
