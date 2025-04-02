#ifndef ANIMATION_STRATEGY_CONTROLS_H
#define ANIMATION_STRATEGY_CONTROLS_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include "ControlSection.h"
#include "../../controllers/AppContext.h"

class AnimationStrategyControls : public ControlSection
{
public:
  AnimationStrategyControls(AppContext &appContext, QWidget *parent = nullptr);

private:
  QComboBox *animationStrategyControl;

  AppContext &appContext;
};

#endif