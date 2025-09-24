#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <list>
#include <memory>
#include <string>

#include <utils/color/ColorStrategy.h>

#include <controllers/display/DisplayRule.h>
#include <controllers/Observable.h>

class DisplayController
{
public:
  using VectorRules = std::map<std::string, DisplayRule>;
  using CustomRules = std::list<std::shared_ptr<DisplayRule>>;

  /** Set particle rule */
  void setParticleRule(DisplayRule rule);
  /** Set vector rule for property */
  void setVectorRule(std::string property, DisplayRule rule);

  /** Add a display rule */
  CustomRules::iterator addCustomRule(CustomRules::value_type value);
  /** Replace a display rule */
  void replaceCustomRule(CustomRules::iterator it, CustomRules::value_type value);
  /** Remove a display rule */
  void removeCustomRule(CustomRules::iterator it);
  /** Clear a display rule */
  void clearCustomRules();
  /** Set background color */
  void setBackgroundColor(QColor color);

  /** Get particle rule */
  DisplayRule &getParticleRule();
  /** Get vector rule for property */
  DisplayRule getVectorRule(std::string property);
  /** Get all  vector rules */
  VectorRules &getVectorRules();
  /** Get display rules */
  CustomRules &getCustomRules();
  /** Get background color */
  QColor getBackgroundColor() const;

  /** Get matching display rule for particle */
  DisplayRule getMatchingParticleRule(const Particle &particle);
  /** Get matching display rule for vector */
  DisplayRule getMatchingVectorRule(const Particle &particle, std::string property);

  /** Particle rule observable */
  BaseObservable<DisplayRule &> particleRuleObservable;
  /** Vector rules observable */
  BaseObservable<VectorRules &> vectorRulesObservable;
  /** Custom rules observable */
  BaseObservable<CustomRules> customRulesObservable;
  /** Background color observable */
  Observable<QColor> backgroundColorObservable = backgroundColor;

private:
  /** Get matching display rule */
  std::optional<DisplayRule> getMatchingCustomRule(const Particle &particle);

  /** Particle rule */
  DisplayRule particleRule;
  /** Vector rules */
  VectorRules vectorRules;
  /** Custom rules */
  CustomRules customRules;
  /** Background color */
  QColor backgroundColor = {0, 0, 0};
};

#endif