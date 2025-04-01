#ifndef TIME_ANIMATION_CONTROLS_H
#define TIME_ANIMATION_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class TimeAnimationControls : public ControlSection
{
public:
  TimeAnimationControls(AppContext &appContext, QWidget *parent = nullptr);
  ~TimeAnimationControls();

private:
  NumericControl *timeControl;
  NumericControl *frameControl;

  AppContext &appContext;
};

#endif