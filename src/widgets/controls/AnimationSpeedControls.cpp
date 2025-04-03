#include "AnimationSpeedControls.h"

#include <QtWidgets/QHBoxLayout>

AnimationSpeedControls::AnimationSpeedControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Velocidad de reproducción", parent}
{
  animationSpeedControl = new NumericControl{this};
  animationSpeedControl->onChange<double>([&](double value)
                                          { appContext.animationController.setAnimationSpeed(value); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(animationSpeedControl);
  layout->setContentsMargins({});

  auto animationSpeedCallback = [&](double value)
  {
    animationSpeedControl->setValue(value);
  };

  animationSpeedCallback(appContext.animationController.animationSpeedObservable.get());

  appContext.animationController.animationSpeedObservable.subscribe(this, animationSpeedCallback);
}

AnimationSpeedControls::~AnimationSpeedControls()
{
  appContext.animationController.animationSpeedObservable.unsubscribe(this);
}