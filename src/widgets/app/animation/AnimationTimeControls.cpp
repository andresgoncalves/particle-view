#include "AnimationTimeControls.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/NumericControl.h>

AnimationTimeControls::AnimationTimeControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Tiempo actual", parent}
{
  // Time unit control
  auto timeControl = new NumericControl{"Tiempo de simulación:", this};
  timeControl->onChange<double>([&appContext](double value)
                                { appContext.animationController.setTime(value); });

  // Build layout
  auto layout = new QVBoxLayout{content};
  layout->addWidget(timeControl);
  layout->setContentsMargins({});

  // Add time unit listener
  auto timeCallback = [=](double value)
  {
    timeControl->setValue(value);
  };
  appContext.animationController.timeObservable.subscribe(this, timeCallback, true);
}

AnimationTimeControls::~AnimationTimeControls()
{
  appContext.animationController.timeObservable.unsubscribe(this);
}