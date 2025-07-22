#ifndef ANIMATION_TIME_CONTROLS_H
#define ANIMATION_TIME_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** Animation time controls */
class AnimationTimeControls : public Section
{
public:
  /** Creates the animation time controls */
  AnimationTimeControls(AppContext &appContext, QWidget *parent = nullptr);
  ~AnimationTimeControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif