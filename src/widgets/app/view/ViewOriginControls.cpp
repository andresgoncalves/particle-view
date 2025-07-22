#include "ViewOriginControls.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/NumericControl.h>

ViewOriginControls::ViewOriginControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Origen", parent}
{
  // Origin X control
  auto xOriginControl = new NumericControl{"x:", this};
  xOriginControl->onChange<float>([&appContext](float value)
                                  { appContext.viewController.setOriginX(value); });

  // Origin Y control
  auto yOriginControl = new NumericControl{"y:", this};
  yOriginControl->onChange<float>([&appContext](float value)
                                  { appContext.viewController.setOriginY(value); });

  // Origin Z control
  auto zOriginControl = new NumericControl{"z:", this};
  zOriginControl->onChange<float>([&appContext](float value)
                                  { appContext.viewController.setOriginZ(value); });

  // Reset button
  auto resetButton = new QPushButton{"Centrar", this};
  connect(resetButton, &QPushButton::clicked, this, [&appContext]
          { appContext.viewController.setOrigin(appContext.animationController.getStory().getOrigin()); });

  // Build layout
  auto controlLayout = new QHBoxLayout{};
  controlLayout->addWidget(xOriginControl);
  controlLayout->addWidget(yOriginControl);
  controlLayout->addWidget(zOriginControl);
  controlLayout->setContentsMargins({});

  auto layout = new QVBoxLayout{content};
  layout->addLayout(controlLayout);
  layout->addWidget(resetButton);
  layout->setAlignment(resetButton, Qt::AlignLeft);
  layout->setContentsMargins({});

  // Add origin listener
  auto originCallback = [=](QVector3D value)
  {
    xOriginControl->setValue(value.x());
    yOriginControl->setValue(value.y());
    zOriginControl->setValue(value.z());
  };
  appContext.viewController.originObservable.subscribe(this, originCallback, true);
}

ViewOriginControls::~ViewOriginControls()
{
  appContext.viewController.originObservable.unsubscribe(this);
}