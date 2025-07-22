#include "ViewTab.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/app/transform/TransformControls.h>
#include <widgets/app/view/ViewOriginControls.h>
#include <widgets/app/view/ViewTranslationControls.h>
#include <widgets/app/view/ViewRotationControls.h>
#include <widgets/app/view/ViewScaleControls.h>

ViewTab::ViewTab(AppContext &appContext, QWidget *parent) : appContext{appContext}, QScrollArea{parent}
{
  auto transformControls = new TransformControls{appContext, this};
  auto viewOriginControls = new ViewOriginControls{appContext, this};
  auto viewTranslationControls = new ViewTranslationControls{appContext, this};
  auto viewRotationControls = new ViewRotationControls{appContext, this};
  auto viewScaleControls = new ViewScaleControls{appContext, this};

  auto widget = new QWidget{this};
  setWidget(widget);
  setWidgetResizable(true);

  auto layout = new QVBoxLayout{widget};
  layout->setAlignment(Qt::AlignTop);
  layout->addWidget(transformControls);
  layout->addWidget(viewOriginControls);
  layout->addWidget(viewTranslationControls);
  layout->addWidget(viewRotationControls);
  layout->addWidget(viewScaleControls);
  layout->setContentsMargins(0, 8, 0, 8);
}