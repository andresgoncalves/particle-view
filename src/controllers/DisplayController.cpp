#include "DisplayController.h"

DisplayController::DisplayController() {}

void DisplayController::toggleParticles()
{
  displayParticles = !displayParticles;
  displayParticlesObservable.notify();
}

void DisplayController::setDisplayParticles(bool value)
{
  displayParticles = value;
  displayParticlesObservable.notify();
}

void DisplayController::toggleVector(std::string property)
{
  setDisplayVector(property, !getDisplayVector(property));
}

void DisplayController::setDisplayVector(std::string property, bool value)
{
  if (value)
    displayedVectors.insert(property);
  else
    displayedVectors.erase(property);

  displayedVectorsObservable.notify();
}

bool DisplayController::getDisplayParticles() const
{
  return displayParticles;
}

bool DisplayController::getDisplayVector(std::string property) const
{
  return displayedVectors.contains(property);
}

std::set<std::string> DisplayController::getDisplayedVectors() const
{
  return displayedVectors;
}

DisplayController::DisplayRules DisplayController::getDisplayRules() const
{
  return displayRules;
}

DisplayController::DisplayRules::iterator DisplayController::addDisplayRule(std::shared_ptr<DisplayRule> displayRule)
{
  displayRules.push_back(displayRule);
  displayRule->enabledObservable.subscribe(this, [&](bool enabled)
                                           { displayRulesObservable.notify(); });
  displayRulesObservable.notify();
  return std::prev(displayRules.end());
}

void DisplayController::removeDisplayRule(DisplayController::DisplayRules::iterator it)
{
  displayRules.erase(it);
  displayRulesObservable.notify();
}