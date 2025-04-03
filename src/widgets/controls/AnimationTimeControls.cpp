#include "AnimationTimeControls.h"

#include <QtWidgets/QHBoxLayout>

AnimationTimeControls::AnimationTimeControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Tiempo actual", parent}
{

  timeControl = new NumericControl{"Tiempo", this};
  timeControl->onChange<float>([&](float value)
                               { appContext.animationController.setTime(value); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(timeControl);
  layout->setContentsMargins({});

  auto timeCallback = [&](double value)
  {
    timeControl->setValue(value);
  };

  auto playingCallback = [&](bool value)
  {
    timeControl->getLineEdit()->setDisabled(value);
  };

  timeCallback(appContext.animationController.timeObservable.get());
  playingCallback(appContext.animationController.playingObservable.get());

  appContext.animationController.timeObservable.subscribe(this, timeCallback);
  appContext.animationController.playingObservable.subscribe(this, playingCallback);
}

AnimationTimeControls::~AnimationTimeControls()
{
  appContext.animationController.timeObservable.unsubscribe(this);
  appContext.animationController.playingObservable.unsubscribe(this);
}