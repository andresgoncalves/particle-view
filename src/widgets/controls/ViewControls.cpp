#include "ViewControls.h"

#include <QtWidgets/QVBoxLayout>

#include "OriginViewControls.h"
#include "TranslationViewControls.h"
#include "RotationViewControls.h"
#include "ScaleViewControls.h"

ViewControls::ViewControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Vista", parent}
{
  auto originControls = new OriginViewControls{appContext, this};
  auto translationControls = new TranslationViewControls{appContext, this};
  auto rotationControls = new RotationViewControls{appContext, this};
  auto scaleControls = new ScaleViewControls{appContext, this};

  auto layout = new QVBoxLayout{content};
  layout->addWidget(originControls);
  layout->addWidget(translationControls);
  layout->addWidget(rotationControls);
  layout->addWidget(scaleControls);
  layout->setContentsMargins(0, 0, 0, 0);
}
