#ifndef ANIMATION_SPEED_CONTROLS_H
#define ANIMATION_SPEED_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** Animation speed controls */
class AnimationSpeedControls : public Section
{
public:
  /** Creates the animation speed controls */
  AnimationSpeedControls(AppContext &appContext, QWidget *parent = nullptr);
  ~AnimationSpeedControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif