#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <set>
#include <list>
#include <string>

#include <utils/color/ColorStrategy.h>

#include "Observable.h"
#include "display/DisplayRule.h"

class DisplayController
{
public:
  using DisplayRules = std::list<std::shared_ptr<DisplayRule>>;
  using DisplayProperty = std::pair<bool, std::shared_ptr<ColorStrategy>>;

  DisplayController();

  void toggleParticles();
  void setDisplayParticles(bool value);
  void setDisplayParticles(std::shared_ptr<ColorStrategy> colorStrategy);

  void toggleVector(std::string property);
  void setDisplayVector(std::string property, bool value);
  void setDisplayVector(std::string property, std::shared_ptr<ColorStrategy> colorStrategy);

  DisplayProperty getDisplayParticles() const;
  DisplayProperty getDisplayVector(std::string property) const;
  std::map<std::string, DisplayProperty> getDisplayVectors() const;

  DisplayRules getDisplayRules() const;
  DisplayRules &getDisplayRules();

  void setBackgroundColor(QColor color);
  QColor getBackgroundColor() const;

  DisplayRules::iterator addDisplayRule(std::shared_ptr<DisplayRule> displayRule);
  void replaceDisplayRule(DisplayRules::iterator it, std::shared_ptr<DisplayRule> displayRule);
  void removeDisplayRule(DisplayRules::iterator it);
  void clearDisplayRules();

  Observable<DisplayProperty> displayParticlesObservable = displayParticles;
  Observable<std::map<std::string, DisplayProperty>> displayVectorsObservable = displayVectors;

  BaseObservable<void> displayRulesObservable;
  Observable<QColor> backgroundColorObservable = backgroundColor;

private:
  /** Particle display boolean and color rules */
  DisplayProperty displayParticles;
  /** Map of properties display boolean and color rules */
  std::map<std::string, DisplayProperty> displayVectors;

  DisplayRules displayRules;

  QColor backgroundColor = {0, 0, 0};
};

#endif