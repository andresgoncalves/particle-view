#include "AnimationSpeedControls.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/NumericControl.h>

AnimationSpeedControls::AnimationSpeedControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Velocidad de reproducción", parent}
{
  // Animation speed control
  auto animationSpeedControl = new NumericControl{"Unidades por segundo:", this};
  animationSpeedControl->onChange<double>([&appContext](double value)
                                          { appContext.animationController.setAnimationSpeed(value); });

  // Build layout
  auto layout = new QVBoxLayout{content};
  layout->addWidget(animationSpeedControl);
  layout->setContentsMargins({});

  // Add animation speed listener
  auto speedCallback = [=](double value)
  {
    animationSpeedControl->setValue(value);
  };
  appContext.animationController.animationSpeedObservable.subscribe(this, speedCallback, true);
}

AnimationSpeedControls::~AnimationSpeedControls()
{
  appContext.animationController.animationSpeedObservable.unsubscribe(this);
}