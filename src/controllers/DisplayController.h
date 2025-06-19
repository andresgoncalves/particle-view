#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <set>
#include <list>
#include <string>

#include "Observable.h"
#include "display/DisplayRule.h"

class DisplayController
{
public:
  using DisplayRules = std::list<std::shared_ptr<DisplayRule>>;

  DisplayController();

  void toggleParticles();
  void setDisplayParticles(bool value);

  void toggleVector(std::string property);
  void setDisplayVector(std::string property, bool value);

  bool getDisplayParticles() const;
  bool getDisplayVector(std::string property) const;
  std::set<std::string> getDisplayedVectors() const;
  DisplayRules getDisplayRules() const;
  DisplayRules &getDisplayRules();

  void setDefaultColor(QColor color);
  void setBackgroundColor(QColor color);

  QColor getDefaultColor() const;
  QColor getBackgroundColor() const;

  DisplayRules::iterator addDisplayRule(std::shared_ptr<DisplayRule> displayRule);
  void replaceDisplayRule(DisplayRules::iterator it, std::shared_ptr<DisplayRule> displayRule);
  void removeDisplayRule(DisplayRules::iterator it);
  void clearDisplayRules();

  Observable<bool> displayParticlesObservable = displayParticles;
  Observable<std::set<std::string>> displayedVectorsObservable = displayedVectors;
  BaseObservable<void> displayRulesObservable;

  Observable<QColor> defaultColorObservable = defaultColor;
  Observable<QColor> backgroundColorObservable = backgroundColor;

private:
  bool displayParticles = true;
  std::set<std::string> displayedVectors;
  DisplayRules displayRules;

  QColor defaultColor = {255, 255, 255};
  QColor backgroundColor = {0, 0, 0};
};

#endif