#include "ViewControls.h"

#include <QtWidgets/QVBoxLayout>

#include "ViewOriginControls.h"
#include "ViewTranslationControls.h"
#include "ViewRotationControls.h"
#include "ViewScaleControls.h"

ViewControls::ViewControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Vista", parent}
{
  auto originControls = new ViewOriginControls{appContext, this};
  auto translationControls = new ViewTranslationControls{appContext, this};
  auto rotationControls = new ViewRotationControls{appContext, this};
  auto scaleControls = new ViewScaleControls{appContext, this};

  auto layout = new QVBoxLayout{content};
  layout->addWidget(originControls);
  layout->addWidget(translationControls);
  layout->addWidget(rotationControls);
  layout->addWidget(scaleControls);
  layout->setContentsMargins(0, 0, 0, 0);
}
