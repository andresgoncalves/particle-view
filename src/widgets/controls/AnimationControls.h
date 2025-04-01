#ifndef ANIMATION_CONTROLS_H
#define ANIMATION_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class AnimationControls : public ControlSection
{
public:
  AnimationControls(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;
};

#endif