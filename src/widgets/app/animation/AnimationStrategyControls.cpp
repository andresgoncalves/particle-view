#include "AnimationStrategyControls.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>

#include <widgets/shared/controls/Control.h>
#include <controllers/animation/LinearAnimationStrategy.h>
#include <controllers/animation/StepAnimationStrategy.h>

AnimationStrategyControls::AnimationStrategyControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Modo de animación", parent}
{
  // Animation strategy control
  auto animationStrategyComboBox = new QComboBox{this};
  animationStrategyComboBox->addItems({"Normal", "Interpolación lineal"});
  connect(animationStrategyComboBox, &QComboBox::currentIndexChanged, this, [&appContext](int index)
          {
    switch (index)
    {
      case 0:
      appContext.animationController.setAnimationStrategy(std::make_unique<StepAnimationStrategy>());
      break;
      case 1:
      appContext.animationController.setAnimationStrategy(std::make_unique<LinearAnimationStrategy>());
      break;
    } });
  auto animationStrategyControl = new Control{animationStrategyComboBox, this};

  // Build layout
  auto layout = new QVBoxLayout{content};
  layout->addWidget(animationStrategyControl);
  layout->setContentsMargins({});

  // Add animation strategy listener
  auto animationStrategyCallback = [=](AnimationStrategy *value)
  {
    if (dynamic_cast<StepAnimationStrategy *>(value))
      animationStrategyComboBox->setCurrentIndex(0);
    else if (dynamic_cast<LinearAnimationStrategy *>(value))
      animationStrategyComboBox->setCurrentIndex(1);
  };
  animationStrategyCallback(appContext.animationController.getAnimationStrategy());
  appContext.animationController.animationStrategyObservable.subscribe(this, animationStrategyCallback);
}

AnimationStrategyControls::~AnimationStrategyControls()
{
  appContext.animationController.animationStrategyObservable.unsubscribe(this);
}