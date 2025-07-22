#include "BottomPanel.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/app/animation/AnimationTimeSlider.h>
#include <widgets/app/animation/AnimationPlayControls.h>

BottomPanel::BottomPanel(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  // Animation time slider
  auto animationTimeSlider = new AnimationTimeSlider{appContext, this};
  // Animation play controls
  auto animationPlayControls = new AnimationPlayControls{appContext, this};

  // Build layout
  auto layout = new QVBoxLayout{this};
  layout->addWidget(animationTimeSlider);
  layout->addWidget(animationPlayControls);
  layout->setAlignment(Qt::AlignTop);
  layout->setContentsMargins(0, 8, 0, 8);
}