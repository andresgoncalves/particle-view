#ifndef ANIMATION_STRATEGY_CONTROLS_H
#define ANIMATION_STRATEGY_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** Animation strategy controls */
class AnimationStrategyControls : public Section
{
public:
  /** Creates the animation strategy controls */
  AnimationStrategyControls(AppContext &appContext, QWidget *parent = nullptr);
  ~AnimationStrategyControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif