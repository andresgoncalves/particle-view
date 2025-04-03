#ifndef ANIMATION_TIME_CONTROLS_H
#define ANIMATION_TIME_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class AnimationTimeControls : public ControlSection
{
public:
  AnimationTimeControls(AppContext &appContext, QWidget *parent = nullptr);
  ~AnimationTimeControls();

private:
  NumericControl *timeControl;
  NumericControl *frameControl;

  AppContext &appContext;
};

#endif