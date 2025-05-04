#include "ViewRotationControls.h"

#include <QtWidgets/QHBoxLayout>

ViewRotationControls::ViewRotationControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Rotación", parent}
{

  xRotationControl = new NumericControl{"x:", this};
  xRotationControl->onChange<float>([&](float value)
                                    { appContext.viewController.setRotationX(value); });
  yRotationControl = new NumericControl{"y':", this};
  yRotationControl->onChange<float>([&](float value)
                                    { appContext.viewController.setRotationY(value); });
  zRotationControl = new NumericControl{"z\":", this};
  zRotationControl->onChange<float>([&](float value)
                                    { appContext.viewController.setRotationZ(value); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(xRotationControl);
  layout->addWidget(yRotationControl);
  layout->addWidget(zRotationControl);
  layout->setContentsMargins({});

  auto rotationCallback = [&](QVector3D value)
  {
    xRotationControl->setValue(value.x());
    yRotationControl->setValue(value.y());
    zRotationControl->setValue(value.z());
  };

  rotationCallback(appContext.viewController.rotationObservable.get());

  appContext.viewController.rotationObservable.subscribe(this, rotationCallback);
}

ViewRotationControls::~ViewRotationControls()
{
  appContext.viewController.rotationObservable.unsubscribe(this);
}