#include "ViewOriginControls.h"

#include <QtWidgets/QHBoxLayout>

ViewOriginControls::ViewOriginControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Origen", parent}
{

  xOriginControl = new NumericControl{"x:", this};
  xOriginControl->onChange<float>([&](float value)
                                  { appContext.viewController.setOriginX(value); });
  yOriginControl = new NumericControl{"y:", this};
  yOriginControl->onChange<float>([&](float value)
                                  { appContext.viewController.setOriginY(value); });
  zOriginControl = new NumericControl{"z:", this};
  zOriginControl->onChange<float>([&](float value)
                                  { appContext.viewController.setOriginZ(value); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(xOriginControl);
  layout->addWidget(yOriginControl);
  layout->addWidget(zOriginControl);
  layout->setContentsMargins({});

  auto originCallback = [&](QVector3D value)
  {
    xOriginControl->setValue(value.x());
    yOriginControl->setValue(value.y());
    zOriginControl->setValue(value.z());
  };

  originCallback(appContext.viewController.originObservable.get());

  appContext.viewController.originObservable.subscribe(this, originCallback);
}

ViewOriginControls::~ViewOriginControls()
{
  appContext.viewController.originObservable.unsubscribe(this);
}