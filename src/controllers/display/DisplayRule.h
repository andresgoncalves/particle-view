#ifndef DISPLAY_RULE_H
#define DISPLAY_RULE_H

#include <sstream>
#include <memory>

#include <QtGui/QColor>

#include <controllers/Observable.h>
#include <controllers/matchers/ParticleMatcher.h>
#include <models/Particle.h>
#include <models/Property.h>

class DisplayRule
{
public:
  /** Set particle matcher */
  void setMatcher(std::unique_ptr<ParticleMatcher> matcher)
  {
    this->matcher = std::move(matcher);
    matcherObservable.notify(this->matcher.get());
  }
  /** Set color */
  void setColor(QColor color)
  {
    this->color = color;
    colorObservable.notify();
  }
  /** Set enabled */
  void setEnabled(bool enabled)
  {
    this->enabled = enabled;
    enabledObservable.notify();
  }

  /** Get particle matcher */
  ParticleMatcher *getMatcher() const
  {
    return matcher.get();
  }
  /** Get color */
  QColor getColor() const
  {
    return color;
  }
  /** Get enabled */
  bool isEnabled() const
  {
    return enabled;
  }

  BaseObservable<ParticleMatcher *> matcherObservable;
  Observable<QColor> colorObservable = color;
  Observable<bool> enabledObservable = enabled;

private:
  std::unique_ptr<ParticleMatcher> matcher;
  QColor color;
  bool enabled = true;
};

#endif