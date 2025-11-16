#include "ViewOriginControls.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/VectorControl.h>

ViewOriginControls::ViewOriginControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Origen", parent}
{

  // Origin control
  auto originControl = new VectorControl{{"x:", "y:", "z:"}, this};
  originControl->onChange([&appContext](QVector3D value)
                          { appContext.viewController.setOrigin(value); });
  // Set dimensionality
  auto dimensionalityCallback = [=](ViewController::Dimensionality dimensionality)
  {
    if (dimensionality == ViewController::Dimensionality::Dimension2D)
    {
      originControl->setVisibleComponents({true, true, false});
    }
    else
    {
      originControl->setVisibleComponents({true, true, true});
    }
  };
  appContext.viewController.dimensionalityObservable.subscribe(this, dimensionalityCallback, true);

  // Reset button
  auto resetButton = new QPushButton{"Centrar", this};
  connect(resetButton, &QPushButton::clicked, this, [&appContext]
          { appContext.viewController.setOrigin(appContext.animationController.getStory().getOrigin()); });

  auto layout = new QVBoxLayout{content};
  layout->addWidget(originControl);
  layout->addWidget(resetButton);
  layout->setAlignment(resetButton, Qt::AlignLeft);
  layout->setContentsMargins({});

  // Add origin listener
  auto originCallback = [=](QVector3D value)
  {
    originControl->setValue(value);
  };
  appContext.viewController.originObservable.subscribe(this, originCallback, true);
}

ViewOriginControls::~ViewOriginControls()
{
  appContext.viewController.originObservable.unsubscribe(this);
}