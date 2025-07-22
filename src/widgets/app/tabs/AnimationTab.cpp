#include "AnimationTab.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/app/animation/AnimationTimeControls.h>
#include <widgets/app/animation/AnimationSpeedControls.h>
#include <widgets/app/animation/AnimationStrategyControls.h>

AnimationTab::AnimationTab(AppContext &appContext, QWidget *parent) : appContext{appContext}, QScrollArea{parent}
{
  // Create time controls
  auto animationTimeControls = new AnimationTimeControls{appContext, this};
  // Create speed controls
  auto animationSpeedControls = new AnimationSpeedControls{appContext, this};
  // Create animation strategy controls
  auto animationStrategyControls = new AnimationStrategyControls{appContext, this};

  // Set content widget
  auto widget = new QWidget{this};
  setWidget(widget);
  setWidgetResizable(true);

  // Build layout
  auto layout = new QVBoxLayout{widget};
  layout->setAlignment(Qt::AlignTop);
  layout->addWidget(animationTimeControls);
  layout->addWidget(animationSpeedControls);
  layout->addWidget(animationStrategyControls);
  layout->setContentsMargins(0, 8, 0, 8);
}