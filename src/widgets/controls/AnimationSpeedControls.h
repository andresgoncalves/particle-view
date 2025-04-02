#ifndef ANIMATION_SPEED_CONTROLS_H
#define ANIMATION_SPEED_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class AnimationSpeedControls : public ControlSection
{
public:
  AnimationSpeedControls(AppContext &appContext, QWidget *parent = nullptr);
  ~AnimationSpeedControls();

private:
  NumericControl *animationSpeedControl;

  AppContext &appContext;
};

#endif