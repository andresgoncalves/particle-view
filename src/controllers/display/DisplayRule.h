#ifndef DISPLAY_RULE_H
#define DISPLAY_RULE_H

#include <memory>

#include <QtGui/QColor>

#include <controllers/Observable.h>
#include <controllers/matchers/ParticleMatcher.h>
#include <controllers/matchers/AnyParticleMatcher.h>
#include <utils/color/ColorStrategy.h>
#include <utils/color/SolidColorStrategy.h>
#include <models/Particle.h>
#include <models/Property.h>

class DisplayRule
{
public:
  /** Set particle matcher */
  void setMatcher(std::shared_ptr<ParticleMatcher> matcher)
  {
    this->matcher = matcher;
  }
  /** Set color strategy */
  void setColorStrategy(std::shared_ptr<ColorStrategy> colorStrategy)
  {
    this->colorStrategy = colorStrategy;
  }
  /** Set visible */
  void setVisible(bool visible)
  {
    this->visible = visible;
  }
  /** Set enabled */
  void setEnabled(bool enabled)
  {
    this->enabled = enabled;
  }

  /** Get particle matcher */
  std::shared_ptr<ParticleMatcher> getMatcher() const
  {
    return matcher;
  }
  /** Get color strategy */
  std::shared_ptr<ColorStrategy> getColorStrategy() const
  {
    return colorStrategy;
  }
  /** Get visible */
  bool isVisible() const
  {
    return visible;
  }
  /** Get enabled */
  bool isEnabled() const
  {
    return enabled;
  }

private:
  std::shared_ptr<ParticleMatcher> matcher = std::make_shared<AnyParticleMatcher>();
  std::shared_ptr<ColorStrategy> colorStrategy = std::make_shared<SolidColorStrategy>(QColor{255, 255, 255});
  bool enabled = true;
  bool visible = true;
};

#endif