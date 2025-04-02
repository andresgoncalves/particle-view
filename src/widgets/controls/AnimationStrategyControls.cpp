#include "AnimationStrategyControls.h"

#include <QtWidgets/QHBoxLayout>

#include "../../controllers/animation/StepAnimationStrategy.h"
#include "../../controllers/animation/LinearAnimationStrategy.h"

AnimationStrategyControls::AnimationStrategyControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Modo de animación", parent}
{
  animationStrategyControl = new QComboBox{this};
  animationStrategyControl->addItems({"Normal", "Interpolación lineal"});

  auto currentIndexChangedCallback = [&](int index)
  {
    switch (index)
    {
    case 0:
      appContext.animationController.setAnimationStrategy(std::make_unique<StepAnimationStrategy>());
      break;
    case 1:
      appContext.animationController.setAnimationStrategy(std::make_unique<LinearAnimationStrategy>());
      break;
    }
  };

  connect(animationStrategyControl, &QComboBox::currentIndexChanged, this, currentIndexChangedCallback);

  auto layout = new QHBoxLayout{content};
  layout->addWidget(animationStrategyControl);
  layout->setContentsMargins({});
}