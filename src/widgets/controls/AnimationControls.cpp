#include "AnimationControls.h"

#include <QtWidgets/QVBoxLayout>

#include "TimeAnimationControls.h"
#include "AnimationSpeedControls.h"
#include "AnimationStrategyControls.h"

AnimationControls::AnimationControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Animación", parent}
{
  auto timeControls = new TimeAnimationControls{appContext, this};
  auto speedControls = new AnimationSpeedControls{appContext, this};
  auto strategyControls = new AnimationStrategyControls{appContext, this};

  auto layout = new QVBoxLayout{content};
  layout->addWidget(timeControls);
  layout->addWidget(speedControls);
  layout->addWidget(strategyControls);
  layout->setContentsMargins(0, 0, 0, 0);
}
